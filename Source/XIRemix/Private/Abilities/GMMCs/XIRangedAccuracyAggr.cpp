// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GMMCs/XIRangedAccuracyAggr.h"
#include "Abilities/AttributeSetGlobal.h"

UXIRangedAccuracyAggr::UXIRangedAccuracyAggr()
{
    AGIDef.AttributeToCapture = UAttributeSetGlobal::GetAgilityAttribute();
    AGIDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    AGIDef.bSnapshot = false;

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

    RelevantAttributesToCapture.Add(AGIDef);

	RelevantAttributesToCapture.Add(ArcheryDef);
	RelevantAttributesToCapture.Add(ArcheryMaxDef);

	RelevantAttributesToCapture.Add(MarksmanshipDef);
	RelevantAttributesToCapture.Add(MarksmanshipMaxDef);

	RelevantAttributesToCapture.Add(ThrowingDef);
	RelevantAttributesToCapture.Add(ThrowingMaxDef);
}

float UXIRangedAccuracyAggr::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    FAggregatorEvaluateParameters EvaluationParameters;

    float CurrentSkillLevel = 0.f;
    float MaxSkillLevel = 0.f;
    float Agility = 0.f;
    float cAgility = 0.f;

    GetCapturedAttributeMagnitude(AGIDef, Spec, EvaluationParameters, Agility);
    cAgility = FMath::Floor(Agility * .75f);

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

    float cSkillLevel = FMath::Min(CurrentSkillLevel, MaxSkillLevel);
    float AccFromSkill = FMath::Min(cSkillLevel, 200.f) + FMath::Floor(FMath::Max(cSkillLevel - 200.f, 0) * 0.9f) + FMath::Floor(FMath::Max(cSkillLevel - 400.f, 0) * 0.8f) + FMath::Floor(FMath::Max(cSkillLevel - 600.f, 0) * 0.9f);

    return AccFromSkill + cAgility;
}