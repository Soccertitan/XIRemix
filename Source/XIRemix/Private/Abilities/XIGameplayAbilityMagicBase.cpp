// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/XIGameplayAbilityMagicBase.h"
#include "FunctionLibrary/CombatFunctionLibrary.h"
#include "DataAssets/XICharacterCombatMontages.h"

UXIGameplayAbilityMagicBase::UXIGameplayAbilityMagicBase()
{
    CastTime = 2.0f;
    bAreaEffectCircle = false;
    AreaEffectBasePower = BasePower;
    AreaEffectRange = 200.0f;
}

UAnimMontage* UXIGameplayAbilityMagicBase::GetCastingAnimMontage()
{
    UXICharacterCombatMontages* CombatMontages = UCombatFunctionLibrary::GetXICharacterCombatMontages(AvatarActor);
    if(!CombatMontages)
    {
        return nullptr;
    }

    switch(XIMagicType)
    {
        case EXIMagicType::Black:
        return CombatMontages->BlackMagic;

        case EXIMagicType::Blue:
        return CombatMontages->BlueMagic;

        case EXIMagicType::Geomancy:
        return CombatMontages->GeoMagic;

        case EXIMagicType::Ninjitsu:
        return CombatMontages->NinjitsuMagic;

        case EXIMagicType::Summoner:
        return CombatMontages->SummonerMagic;

        case EXIMagicType::HandBell:
        return CombatMontages->HandbellMagic;

        default:
        return CombatMontages->WhiteMagic;
    }
}