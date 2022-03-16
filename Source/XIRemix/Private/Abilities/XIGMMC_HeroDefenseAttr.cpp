// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/XIGMMC_HeroDefenseAttr.h"
#include "Abilities/AttributeSetGlobal.h"

UXIGMMC_HeroDefenseAttr::UXIGMMC_HeroDefenseAttr()
{
    VitalityDef.AttributeToCapture = UAttributeSetGlobal::GetVitalityAttribute();
    VitalityDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    VitalityDef.bSnapshot = false;

    RelevantAttributesToCapture.Add(VitalityDef);
}

float UXIGMMC_HeroDefenseAttr::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    FAggregatorEvaluateParameters EvaluationParameters;

    float Vitality = 0.f;
    GetCapturedAttributeMagnitude(VitalityDef, Spec, EvaluationParameters, Vitality);
    
    float Defense = 0.f;

    float Level = 1.f;

    Defense = Defense + FMath::Floor(FMath::Max((Vitality / 2.f) + 8 + Level + FMath::Clamp(Level - 50.f, 0.f, 10.f), 0.f));

    return Defense;
}