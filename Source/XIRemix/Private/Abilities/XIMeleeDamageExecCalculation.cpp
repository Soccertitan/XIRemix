// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/XIMeleeDamageExecCalculation.h"
#include "Abilities/XIAbilitySystemComponent.h"
#include "Abilities/AttributeSetGlobal.h"
#include "Interfaces/XIThreatTableInterface.h"
#include "AIController.h"
#include "Components/XIThreatTableComponent.h"

struct XIMeleeStatics
{
    DECLARE_ATTRIBUTE_CAPTUREDEF(Attack);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Defense);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Accuracy);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Evasion);

    XIMeleeStatics()
    {
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Attack, Source, true);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Accuracy, Source, true);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Defense, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Evasion, Target, false);
    }
};

static const XIMeleeStatics& MeleeStatics()
{
    static XIMeleeStatics MStatics;
    return MStatics;
}

UXIMeleeDamageExecCalculation::UXIMeleeDamageExecCalculation()
{
    RelevantAttributesToCapture.Add(MeleeStatics().AccuracyDef);
    RelevantAttributesToCapture.Add(MeleeStatics().AttackDef);
    RelevantAttributesToCapture.Add(MeleeStatics().DefenseDef);
    RelevantAttributesToCapture.Add(MeleeStatics().EvasionDef);
}

void UXIMeleeDamageExecCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->GetAvatarActor() : nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

    APawn* AsPawn = Cast<APawn>(TargetActor);
    
    const IXIThreatTableInterface* XIThreatInt = Cast<IXIThreatTableInterface>(Cast<AAIController>(AsPawn->GetController()));

    if(XIThreatInt)
    {
        UE_LOG(LogTemp, Warning, TEXT("XIMeleeDamageExecCalc. Valid ThreatComponent"));
        UXIThreatTableComponent* ThreatTableComponent = XIThreatInt->GetXIThreatTableComponent();
        ThreatTableComponent->ApplyDamageEnmity(SourceActor, 1.0f, 3.0f, 1.0f);
    }
}