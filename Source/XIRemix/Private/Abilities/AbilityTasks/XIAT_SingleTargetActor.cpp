// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AbilityTasks/XIAT_SingleTargetActor.h"
#include "AbilitySystemComponent.h"
#include "Abilities/XIAbilityTypes.h"

AXIAT_SingleTargetActor::AXIAT_SingleTargetActor()
{
    
}

void AXIAT_SingleTargetActor::StartTargeting(UGameplayAbility* Ability)
{
    OwningAbility = Ability;
    SourceActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();
}

void AXIAT_SingleTargetActor::ConfirmTargetingAndContinue()
{    
    FGameplayAbilitySingleTargetData *ReturnData = new FGameplayAbilitySingleTargetData();
    ReturnData->UniqueID = OwningAbility->GetUniqueID();

    ReturnData->TargetActor = TargetedActor;
    ReturnData->AttackMontage = AnimMontage;
    
    FGameplayAbilityTargetDataHandle Handle(ReturnData);
    TargetDataReadyDelegate.Broadcast(Handle);
}
