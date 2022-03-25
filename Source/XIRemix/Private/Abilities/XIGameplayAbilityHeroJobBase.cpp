// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/XIGameplayAbilityHeroJobBase.h"

void UXIGameplayAbilityHeroJobBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    if(!XIJobAbilityData)
    {
        UE_LOG(LogTemp, Warning, TEXT("XIJob Ability Data is Null"));
        EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
        return;
    }
    
    for(const FXIJobAbilityDataItem& Item : XIJobAbilityData->XIJobAbilityDataItem)
    {
        if(Item.XIAbility->Ability)
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

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}