// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AbilityTasks/XIAT_SingleTargetActor.h"
#include "AbilitySystemComponent.h"
#include "Interfaces/XICharacterInterface.h"
#include "FunctionLibrary/CombatFunctionLibrary.h"

bool FGameplayAbilityMeleeTarget::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
    Ar << TargetActor;
    Ar << AttackMontage;
    Ar << UniqueID;
    bOutSuccess = true;
    return true;
}

AXIAT_SingleTargetActor::AXIAT_SingleTargetActor()
{
    MaxRange = 250.0f;
    Angle = 30.0f;
}

void AXIAT_SingleTargetActor::StartTargeting(UGameplayAbility* Ability)
{
    OwningAbility = Ability;
    SourceActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();
}

void AXIAT_SingleTargetActor::ConfirmTargetingAndContinue()
{
    FGameplayAbilityMeleeTarget *ReturnData = new FGameplayAbilityMeleeTarget();

    IXICharacterInterface* IXICharInt = Cast<IXICharacterInterface>(SourceActor);
    if (IXICharInt)
    {
        bool bInRange = UCombatFunctionLibrary::CheckTargetWithinRange(SourceActor, IXICharInt->Execute_GetMainTarget(SourceActor), Angle, MaxRange);
    
        if (bInRange)
        {
            ReturnData->TargetActor = IXICharInt->Execute_GetMainTarget(SourceActor);
        }
        else
        {
            ReturnData->TargetActor = nullptr;
        }
    }
    ReturnData->AttackMontage = nullptr;
    if (ReturnData->TargetActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("Targeted Actor: %s"), *ReturnData->TargetActor->GetName());
    }
    
    FGameplayAbilityTargetDataHandle Handle(ReturnData);
    TargetDataReadyDelegate.Broadcast(Handle);
}