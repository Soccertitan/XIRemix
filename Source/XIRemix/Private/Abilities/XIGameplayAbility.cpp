// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/XIGameplayAbility.h"
#include "FunctionLibrary/XIGameplayFunctionLibrary.h"

UXIGameplayAbility::UXIGameplayAbility()
{
    // Default to instance per Actor
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

bool UXIGameplayAbility::IsTargetValid(AActor* SourceActorLocation, AActor* InTargetActor, float InRange, float InAngle, EXITeamAttitude InTargetAttitude) const
{
    bool bIsInRange = UXIGameplayFunctionLibrary::CheckTargetWithinRange(SourceActorLocation, InTargetActor, InAngle, (InRange+CapsuleRadius));
    bool bEqualAttitudes = (UXIGameplayFunctionLibrary::GetAttitudeTowardsActor(GetAvatarActorFromActorInfo(), InTargetActor) == InTargetAttitude);

    if ((bIsInRange == true) && (bEqualAttitudes == true))
    {
        return true;
    }
    else
    {
        return false;
    }
}

TArray <AActor* > UXIGameplayAbility::GetSphereAreaEffectTargets(AActor* InActorSource, float InRange)
{
    TArray <AActor* > Actors;
    TArray <FHitResult> OutHits;

    Actors.Empty();
    OutHits.Empty();
    
    if(!InActorSource || !MainTarget || !XIAbilityData)
    {
        return Actors;
    }

    //Sweep Locations
    FVector SweepVector = InActorSource->GetActorLocation();
    FCollisionShape MyColSphere = FCollisionShape::MakeSphere(InRange);

    bool bIsHit = GetWorld()->SweepMultiByObjectType(OutHits, SweepVector, SweepVector, FQuat::Identity, ECC_Pawn, MyColSphere);

    if(!bIsHit)
    {
        return Actors;
    }

    for (FHitResult Hit : OutHits)
    {
        if(IsTargetValid(InActorSource, Hit.GetActor(), InRange, 180.f, XIAbilityData->TargetAttiude))
        {
            Actors.AddUnique(Hit.GetActor());
        }
    }

    //Removes main target to prevent the aoe effect from applying twice.
    Actors.Remove(MainTarget);

    return Actors;
}

const FGameplayTagContainer* UXIGameplayAbility::GetCooldownTags() const
{
    FGameplayTagContainer* MutableTags = const_cast<FGameplayTagContainer*>(&TempCooldownTags);
	MutableTags->Reset(); // MutableTags writes to the TempCooldownTags on the CDO so clear it in case the ability cooldown tags change (moved to a different slot)
	const FGameplayTagContainer* ParentTags = Super::GetCooldownTags();
	if (ParentTags)
	{
		MutableTags->AppendTags(*ParentTags);
	}

    if(XIAbilityData)
    {
	    MutableTags->AppendTags(XIAbilityData->CooldownTags);
    }

	return MutableTags;
}

void UXIGameplayAbility::ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
    UGameplayEffect* CooldownGE = GetCooldownGameplayEffect();
	if (CooldownGE)
	{
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(CooldownGE->GetClass(), GetAbilityLevel());
		
        if(XIAbilityData)
        {
            SpecHandle.Data.Get()->DynamicGrantedTags.AppendTags(XIAbilityData->CooldownTags);
    	    SpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("SetByCaller.Cooldown")), XIAbilityData->Cooldown);
        }

		ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
	}
}

void UXIGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
    Super::OnAvatarSet(ActorInfo, Spec);

	if (XIAbilityData)
	{
        if(XIAbilityData->bPassiveAbility)
        {
		    bool ActivatedAbility = ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
        }
	}
}

bool UXIGameplayAbility::DoesAbilitySatisfyTagRequirements(const UAbilitySystemComponent& AbilitySystemComponent, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
    bool bBlocked = false;
    bool bMissing = false;
 
    const UAbilitySystemGlobals& AbilitySystemGlobals = UAbilitySystemGlobals::Get();
    const FGameplayTag& BlockedTag = AbilitySystemGlobals.ActivateFailTagsBlockedTag;
    const FGameplayTag& MissingTag = AbilitySystemGlobals.ActivateFailTagsMissingTag;
 
    // Check if any of this ability's tags are currently blocked
    if (AbilitySystemComponent.AreAbilityTagsBlocked(AbilityTags))
    {
        bBlocked = true;
    }
 
    /*
     * Relationship related code
     */
     
    const UXIAbilitySystemComponent* XIASC = Cast<UXIAbilitySystemComponent>(&AbilitySystemComponent);
    static FGameplayTagContainer AbilityRequiredTags;
    AbilityRequiredTags = ActivationRequiredTags;
     
    static FGameplayTagContainer AbilityBlockedTags; 
    AbilityBlockedTags = ActivationBlockedTags;
 
    // This gets the additional tags from the ASC's relationship mapping for the abilities tags.
    if (XIASC)
    {
        XIASC->GetRelationshipActivationTagRequirements(AbilityTags, AbilityRequiredTags, AbilityBlockedTags);
    }
 
    /*
     * End of relationship code
     */
 
    // Check to see the required/blocked tags for this ability
    if (AbilityBlockedTags.Num() || AbilityRequiredTags.Num())
    {
        static FGameplayTagContainer AbilitySystemComponentTags;
         
        AbilitySystemComponentTags.Reset();
        AbilitySystemComponent.GetOwnedGameplayTags(AbilitySystemComponentTags);
 
        if (AbilitySystemComponentTags.HasAny(AbilityBlockedTags))
        {
            bBlocked = true;
        }
 
        if (!AbilitySystemComponentTags.HasAll(AbilityRequiredTags))
        {
            bMissing = true;
        }
    }
 
    if (SourceTags != nullptr)
    {
        if (SourceBlockedTags.Num() || SourceRequiredTags.Num())
        {
            if (SourceTags->HasAny(SourceBlockedTags))
            {
                bBlocked = true;
            }
 
            if (!SourceTags->HasAll(SourceRequiredTags))
            {
                bMissing = true;
            }
        }
    }
 
    if (TargetTags != nullptr)
    {
        if (TargetBlockedTags.Num() || TargetRequiredTags.Num())
        {
            if (TargetTags->HasAny(TargetBlockedTags))
            {
                bBlocked = true;
            }
 
            if (!TargetTags->HasAll(TargetRequiredTags))
            {
                bMissing = true;
            }
        }
    }
 
    if (bBlocked)
    {
        if (OptionalRelevantTags && BlockedTag.IsValid())
        {
            OptionalRelevantTags->AddTag(BlockedTag);
        }
        return false;
    }
    if (bMissing)
    {
        if (OptionalRelevantTags && MissingTag.IsValid())
        {
            OptionalRelevantTags->AddTag(MissingTag);
        }
        return false;
    }
 
    return true;
}

float UXIGameplayAbility::GetCost() const
{
    if(XIAbilityData)
    {
        return XIAbilityData->Cost;
    }
    return 0.f;
}

float UXIGameplayAbility::GetPotency() const
{
    if(XIAbilityData)
    {
        return XIAbilityData->Potency;
    }
    return 0.f;
}

bool UXIGameplayAbility::GetEnmity(float OutCumulativeEnmity, float OutVolatileEnmity) const
{
    if(XIAbilityData)
    {
        if(XIAbilityData->bFixedEnmity)
        {
            OutCumulativeEnmity = XIAbilityData->CumulativeEnmity;
            OutVolatileEnmity = XIAbilityData->VolatileEnmity;
            return true;
        }
    }
    return false;
}

void UXIGameplayAbility::InitializeAbilityData()
{
    AvatarActor = GetAvatarActorFromActorInfo();
    CapsuleRadius = UXIGameplayFunctionLibrary::GetCapsuleRadius(AvatarActor);
}

void UXIGameplayAbility::GiveXIGameplayAbility(UAbilitySystemComponent* AbilitySystemComponent, TSubclassOf<UXIGameplayAbility> XIGameplayAbility, AActor* SourceActor)
{
    if (!K2_HasAuthority() || !AbilitySystemComponent || !XIGameplayAbility)
    {
        return;
    }
        AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(XIGameplayAbility, 1, static_cast<int32>(XIGameplayAbility.GetDefaultObject()->AbilityInputID), SourceActor));
}

void UXIGameplayAbility::RemoveXIGameplayAbilities(UAbilitySystemComponent* AbilitySystemComponent, TArray<TSubclassOf<UXIGameplayAbility>> XIGameplayAbilities)
{
    if (!K2_HasAuthority() || !AbilitySystemComponent || !XIGameplayAbilities.IsValidIndex(0))
    {
        return;
    }

    // Adds specified abilities to an array for removal.
	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
	for (const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if (XIGameplayAbilities.Contains(Spec.Ability->GetClass()))
		{
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}

	// Do in two passes so the removal happens after we have the full list
	for (int32 i = 0; i < AbilitiesToRemove.Num(); i++)
	{
		AbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);
	}
}