// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/XIGameplayAbilityMagicBase.h"
#include "FunctionLibrary/XIGameplayFunctionLibrary.h"
#include "DataAssets/XICharacterAnimMontages.h"

UXIGameplayAbilityMagicBase::UXIGameplayAbilityMagicBase()
{
}

UAnimMontage* UXIGameplayAbilityMagicBase::GetCastingAnimMontage()
{
    UXICharacterAnimMontages* AnimMontages = UXIGameplayFunctionLibrary::GetXICharacterAnimMontages(AvatarActor);
    if(!AnimMontages)
    {
        return nullptr;
    }

    return AnimMontages->GetMagicMontage(XIMagicType);
}