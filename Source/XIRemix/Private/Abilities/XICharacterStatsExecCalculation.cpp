// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/XICharacterStatsExecCalculation.h"
#include "Abilities/XIAbilitySystemComponent.h"
#include "Abilities/AttributeSetGlobal.h"

struct XIBaseAttributesStatics
{
    DECLARE_ATTRIBUTE_CAPTUREDEF(HitPoints);
    DECLARE_ATTRIBUTE_CAPTUREDEF(HitPointsMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(ManaPoints);
    DECLARE_ATTRIBUTE_CAPTUREDEF(ManaPointsMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Strength);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Dexterity);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Vitality);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Agility);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Intelligence);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Mind);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Charisma);

    XIBaseAttributesStatics()
    {
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, HitPoints, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, HitPointsMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, ManaPoints, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, ManaPointsMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Strength, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Dexterity, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Vitality, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Agility, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Intelligence, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Mind, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Charisma, Target, false);
    }
};

static const XIBaseAttributesStatics& BaseAttributesStatics()
{
    static XIBaseAttributesStatics AStatics;
    return AStatics;
}

UXICharacterStatsExecCalculation::UXICharacterStatsExecCalculation()
{
    RelevantAttributesToCapture.Add(XIBaseAttributesStatics().HitPointsDef);
    RelevantAttributesToCapture.Add(XIBaseAttributesStatics().HitPointsMaxDef);
    RelevantAttributesToCapture.Add(XIBaseAttributesStatics().ManaPointsDef);
    RelevantAttributesToCapture.Add(XIBaseAttributesStatics().ManaPointsMaxDef);
    RelevantAttributesToCapture.Add(XIBaseAttributesStatics().StrengthDef);
    RelevantAttributesToCapture.Add(XIBaseAttributesStatics().DexterityDef);
    RelevantAttributesToCapture.Add(XIBaseAttributesStatics().VitalityDef);
    RelevantAttributesToCapture.Add(XIBaseAttributesStatics().AgilityDef);
    RelevantAttributesToCapture.Add(XIBaseAttributesStatics().IntelligenceDef);
    RelevantAttributesToCapture.Add(XIBaseAttributesStatics().MindDef);
    RelevantAttributesToCapture.Add(XIBaseAttributesStatics().CharismaDef);
}

void UXICharacterStatsExecCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
    AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

    // Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.TargetTags = TargetTags;

    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(BaseAttributesStatics().HitPointsMaxProperty, EGameplayModOp::Override, 50.0f));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(BaseAttributesStatics().HitPointsProperty, EGameplayModOp::Override, 48.0f));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(BaseAttributesStatics().ManaPointsMaxProperty, EGameplayModOp::Override, 25.0f));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(BaseAttributesStatics().ManaPointsProperty, EGameplayModOp::Override, 30.0f));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(BaseAttributesStatics().StrengthProperty, EGameplayModOp::Override, 30.0f));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(BaseAttributesStatics().DexterityProperty, EGameplayModOp::Override, 7.0f));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(BaseAttributesStatics().VitalityProperty, EGameplayModOp::Override, 6.0f));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(BaseAttributesStatics().AgilityProperty, EGameplayModOp::Override, 8.0f));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(BaseAttributesStatics().IntelligenceProperty, EGameplayModOp::Override, 3.0f));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(BaseAttributesStatics().MindProperty, EGameplayModOp::Override, 4.0f));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(BaseAttributesStatics().CharismaProperty, EGameplayModOp::Override, 4.0f));
}