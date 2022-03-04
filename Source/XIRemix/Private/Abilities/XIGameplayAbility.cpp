// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/XIGameplayAbility.h"
#include "FunctionLibrary/CombatFunctionLibrary.h"

UXIGameplayAbility::UXIGameplayAbility()
{
    // Default to instance per Actor
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    static ConstructorHelpers::FObjectFinder<UDataTable> XIAbilityDataObject(TEXT("DataTable'/Game/XIRemix/DataTables/DT_XIAbilityData.DT_XIAbilityData'"));
    if(XIAbilityDataObject.Succeeded())
    {
        XIAbilityDataHandle.DataTable = XIAbilityDataObject.Object;
    }
}

bool UXIGameplayAbility::IsTargetValid(AActor* SourceActorLocation, AActor* InTargetActor, float InRange, float InAngle, EXITeamAttitude InTargetAttitude) const
{
    bool bIsInRange = UCombatFunctionLibrary::CheckTargetWithinRange(SourceActorLocation, InTargetActor, InAngle, (InRange+CapsuleRadius));
    bool bEqualAttitudes = (UCombatFunctionLibrary::GetAttitudeTowardsActor(GetAvatarActorFromActorInfo(), InTargetActor) == InTargetAttitude);

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
    
    if(!InActorSource || !MainTarget)
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
        if(IsTargetValid(InActorSource, Hit.GetActor(), InRange, 180.f, TargetAttitude))
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
	MutableTags->AppendTags(CooldownTags);
	return MutableTags;
}

void UXIGameplayAbility::ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
    UGameplayEffect* CooldownGE = GetCooldownGameplayEffect();
	if (CooldownGE)
	{
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(CooldownGE->GetClass(), GetAbilityLevel());
		SpecHandle.Data.Get()->DynamicGrantedTags.AppendTags(CooldownTags);
		SpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Cooldown")), Cooldown);
		ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
	}
}

void UXIGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
    Super::OnAvatarSet(ActorInfo, Spec);

	if (bActivateAbilityOnGranted)
	{
		bool ActivatedAbility = ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}

float UXIGameplayAbility::GetCost() const
{
    return Cost;
}

void UXIGameplayAbility::InitializeAbilityData()
{
    static const FString ContextString(TEXT("XIGameplay Ability Initialize Parameters"));
    FXIAbilityData* XIAbilityData = XIAbilityDataHandle.DataTable->FindRow<FXIAbilityData>(XIAbilityDataHandle.RowName, ContextString, true);

    if(XIAbilityData)
    {
        Angle = XIAbilityData->Angle;
        AreaEffectRange = XIAbilityData->AreaEffectRange;
        bAreaEffect = XIAbilityData->bAreaEffect;
        BasePower = XIAbilityData->BasePower;
        bFixedEnmity = XIAbilityData->bFixedEnmity;
        CastTime = XIAbilityData->CastTime;
        Cooldown = XIAbilityData->Cooldown;
        Cost = XIAbilityData->Cost;
        CumulativeEnmity = XIAbilityData->CumulativeEnmity;
        Duration = XIAbilityData->Duration;
        Range = XIAbilityData->Range;
        VolatileEnmity = XIAbilityData->VolatileEnmity;
    }

    AvatarActor = GetAvatarActorFromActorInfo();
    CapsuleRadius = UCombatFunctionLibrary::GetCapsuleRadius(AvatarActor);
}