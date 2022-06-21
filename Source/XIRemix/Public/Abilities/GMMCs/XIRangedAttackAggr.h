// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "XIRangedAttackAggr.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIRangedAttackAggr : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:

	UXIRangedAttackAggr();

	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

	FGameplayEffectAttributeCaptureDefinition STRDef;

	FGameplayEffectAttributeCaptureDefinition ArcheryDef;
	FGameplayEffectAttributeCaptureDefinition ArcheryMaxDef;

	FGameplayEffectAttributeCaptureDefinition MarksmanshipDef;
	FGameplayEffectAttributeCaptureDefinition MarksmanshipMaxDef;

	FGameplayEffectAttributeCaptureDefinition ThrowingDef;
	FGameplayEffectAttributeCaptureDefinition ThrowingMaxDef;
};
