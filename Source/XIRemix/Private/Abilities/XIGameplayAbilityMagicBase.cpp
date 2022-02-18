// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/XIGameplayAbilityMagicBase.h"
#include "FunctionLibrary/CombatFunctionLibrary.h"

UXIGameplayAbilityMagicBase::UXIGameplayAbilityMagicBase()
{
    CastTime = 2.0f;
    bAreaEffectCircle = false;
    AreaEffectBasePower = BasePower;
    AreaEffectRange = 200.0f;
}

UAnimMontage* UXIGameplayAbilityMagicBase::GetCastingAnimMontage()
{
    switch(XIMagicType)
    {
        case EXIMagicType::Black:
        return UCombatFunctionLibrary::GetBlackMagicMontage(AvatarActor);

        case EXIMagicType::Blue:
        return UCombatFunctionLibrary::GetBlueMagicMontage(AvatarActor);

        case EXIMagicType::Geo:
        return UCombatFunctionLibrary::GetGeoMagicMontage(AvatarActor);

        case EXIMagicType::Ninjitsu:
        return UCombatFunctionLibrary::GetNinjitsuMagicMontage(AvatarActor);

        case EXIMagicType::Summoner:
        return UCombatFunctionLibrary::GetSummonerMagicMontage(AvatarActor);

        default:
        return UCombatFunctionLibrary::GetWhiteMagicMontage(AvatarActor);
    }
}