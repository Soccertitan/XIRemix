// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/XIGameplayAbilityMagicBase.h"
#include "FunctionLibrary/CombatFunctionLibrary.h"
#include "DataAssets/XICharacterAnimMontages.h"

UXIGameplayAbilityMagicBase::UXIGameplayAbilityMagicBase()
{
}

UAnimMontage* UXIGameplayAbilityMagicBase::GetCastingAnimMontage()
{
    UXICharacterAnimMontages* AnimMontages = UCombatFunctionLibrary::GetXICharacterAnimMontages(AvatarActor);
    if(!AnimMontages)
    {
        return nullptr;
    }

    return AnimMontages->GetMagicMontage(XIMagicType);
}