// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GMMCs/XIEvasionAggr.h"
#include "Abilities/AttributeSetGlobal.h"

UXIEvasionAggr::UXIEvasionAggr()
{
    EvasionDef.AttributeToCapture = UAttributeSetGlobal::GetEvasionSkillAttribute();
    EvasionDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    EvasionDef.bSnapshot = false;

    EvasionMaxDef.AttributeToCapture = UAttributeSetGlobal::GetEvasionSkillMaxAttribute();
    EvasionMaxDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    EvasionMaxDef.bSnapshot = false;

    AgiDef.AttributeToCapture = UAttributeSetGlobal::GetAgilityAttribute();
    AgiDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    AgiDef.bSnapshot = false;

    RelevantAttributesToCapture.Add(EvasionDef);
    RelevantAttributesToCapture.Add(EvasionMaxDef);
    RelevantAttributesToCapture.Add(AgiDef);
}

float UXIEvasionAggr::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    FAggregatorEvaluateParameters EvaluationParameters;

    float EvasionSkill;
    float EvasionSkillMax;
    float Agility;
    GetCapturedAttributeMagnitude(EvasionDef, Spec, EvaluationParameters, EvasionSkill);
    GetCapturedAttributeMagnitude(EvasionMaxDef, Spec, EvaluationParameters, EvasionSkillMax);
    GetCapturedAttributeMagnitude(AgiDef, Spec, EvaluationParameters, Agility);

    float cEvasionSkill = FMath::Min(EvasionSkill, EvasionSkillMax);

    return FMath::Floor(Agility / 2.f) + FMath::Min(cEvasionSkill, 200.f) + FMath::Floor(FMath::Max((cEvasionSkill - 200), 0.f) * 0.9f);
}