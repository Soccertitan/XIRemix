// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/XIGameplayAbilityHeroJobBase.h"
#include "Characters/XICharacterBaseHero.h"

UXIGameplayAbilityHeroJobBase::UXIGameplayAbilityHeroJobBase()
{
    bRetriggerInstancedAbility = true;
}

void UXIGameplayAbilityHeroJobBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    if(!XIJobAbilityData || !AttributeGE)
    {
        UE_LOG(LogTemp, Error, TEXT("XIJob Ability Data or AttributeGE is null."));
        EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
        return;
    }

    if(LevelAdjustmentGE)
    {
        FGameplayEffectSpecHandle Spec = MakeOutgoingGameplayEffectSpec(LevelAdjustmentGE);
        LevelAdjustmentHandle = ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, Spec);
    }

    FGameplayEffectSpecHandle AttributeSpec = MakeOutgoingGameplayEffectSpec(AttributeGE);
    ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, AttributeSpec);

    float Level = GetCharacterLevel();

    for(const FXIJobAbilityDataItem& Item : XIJobAbilityData->XIJobAbilityDataItem)
    {
        if(Item.XIAbility->Ability && (Item.Level <= Level))
        {
            //TODO: Add check if character is appropriate level to gain ability + proper override starting attributes.
            UE_LOG(LogTemp, Warning, TEXT("Adding Ability: %s"), *Item.XIAbility->Ability->GetName());
            GiveXIGameplayAbility(GetAbilitySystemComponentFromActorInfo(), Item.XIAbility->Ability, GetAvatarActorFromActorInfo());
        }
    }
}

void UXIGameplayAbilityHeroJobBase::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    if(XIJobAbilityData)
    {
        UE_LOG(LogTemp, Warning, TEXT("Removing Abilities"));

        TArray<TSubclassOf<UXIGameplayAbility>> XIGameplayAbilities;

        for(const FXIJobAbilityDataItem& Item : XIJobAbilityData->XIJobAbilityDataItem)
        {
            if(Item.XIAbility->Ability)
            {
                XIGameplayAbilities.Add(Item.XIAbility->Ability);
            }
        }

        RemoveXIGameplayAbilities(GetAbilitySystemComponentFromActorInfo(), XIGameplayAbilities);
    }

    BP_RemoveGameplayEffectFromOwnerWithHandle(LevelAdjustmentHandle);

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

float UXIGameplayAbilityHeroJobBase::GetCharacterLevel()
{
    AXICharacterBaseHero* XIHero = Cast<AXICharacterBaseHero>(GetAvatarActorFromActorInfo());

    if (XIHero)
    {
        FXICharacterHeroActiveJobsLevels HeroCharacterJobs;
        HeroCharacterJobs = XIHero->GetCharacterActiveJobsAndLevels();

        if (AbilityTags.HasTagExact(HeroCharacterJobs.MainJobTag))
        {
            return HeroCharacterJobs.MainJobLevel;
        }

        if (AbilityTags.HasTagExact(HeroCharacterJobs.SubJobTag))
        {
            return HeroCharacterJobs.SubJobLevel;
        }
    }

    return 0.f;
}