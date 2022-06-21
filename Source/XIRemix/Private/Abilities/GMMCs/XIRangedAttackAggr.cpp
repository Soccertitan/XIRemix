// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GMMCs/XIRangedAttackAggr.h"
#include "Abilities/AttributeSetGlobal.h"

UXIRangedAttackAggr::UXIRangedAttackAggr()
{
    STRDef.AttributeToCapture = UAttributeSetGlobal::GetStrengthAttribute();
    STRDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    STRDef.bSnapshot = false;

    ArcheryDef.AttributeToCapture = UAttributeSetGlobal::GetArcherySkillAttribute();
    ArcheryDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    ArcheryDef.bSnapshot = false;
    ArcheryMaxDef.AttributeToCapture = UAttributeSetGlobal::GetArcherySkillMaxAttribute();
    ArcheryMaxDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    ArcheryMaxDef.bSnapshot = false;

    MarksmanshipDef.AttributeToCapture = UAttributeSetGlobal::GetMarksmanshipSkillAttribute();
    MarksmanshipDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    MarksmanshipDef.bSnapshot = false;
    MarksmanshipMaxDef.AttributeToCapture = UAttributeSetGlobal::GetMarksmanshipSkillMaxAttribute();
    MarksmanshipMaxDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    MarksmanshipMaxDef.bSnapshot = false;

    ThrowingDef.AttributeToCapture = UAttributeSetGlobal::GetThrowingSkillAttribute();
    ThrowingDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    ThrowingDef.bSnapshot = false;
    ThrowingMaxDef.AttributeToCapture = UAttributeSetGlobal::GetThrowingSkillMaxAttribute();
    ThrowingMaxDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    ThrowingMaxDef.bSnapshot = false;

    RelevantAttributesToCapture.Add(STRDef);

	RelevantAttributesToCapture.Add(ArcheryDef);
	RelevantAttributesToCapture.Add(ArcheryMaxDef);

	RelevantAttributesToCapture.Add(MarksmanshipDef);
	RelevantAttributesToCapture.Add(MarksmanshipMaxDef);

	RelevantAttributesToCapture.Add(ThrowingDef);
	RelevantAttributesToCapture.Add(ThrowingMaxDef);
}

float UXIRangedAttackAggr::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    FAggregatorEvaluateParameters EvaluationParameters;

    float CurrentSkillLevel = 0.f;
    float MaxSkillLevel = 0.f;
    float Strength = 0.f;
    float cStrength = 0.f;

    GetCapturedAttributeMagnitude(STRDef, Spec, EvaluationParameters, Strength);
    cStrength = FMath::Floor(Strength * .75f);

    FGameplayTagContainer Tags = Spec.CapturedTargetTags.GetActorTags();

    if (Tags.HasTag(FGameplayTag::RequestGameplayTag("Weapon.Ranged.Archery")))
    {
        GetCapturedAttributeMagnitude(ArcheryDef, Spec, EvaluationParameters, CurrentSkillLevel);
        GetCapturedAttributeMagnitude(ArcheryMaxDef, Spec, EvaluationParameters, MaxSkillLevel);
    }
    else if (Tags.HasTag(FGameplayTag::RequestGameplayTag("Weapon.Ranged.Marksmanship")))
    {
        GetCapturedAttributeMagnitude(MarksmanshipDef, Spec, EvaluationParameters, CurrentSkillLevel);
        GetCapturedAttributeMagnitude(MarksmanshipMaxDef, Spec, EvaluationParameters, MaxSkillLevel);
    }
    else
    {
        GetCapturedAttributeMagnitude(ThrowingDef, Spec, EvaluationParameters, CurrentSkillLevel);
        GetCapturedAttributeMagnitude(ThrowingMaxDef, Spec, EvaluationParameters, MaxSkillLevel);
    }

    return 8.f + FMath::Min(CurrentSkillLevel, MaxSkillLevel) + cStrength;
}