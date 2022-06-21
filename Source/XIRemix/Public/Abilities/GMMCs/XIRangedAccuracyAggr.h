// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "XIRangedAccuracyAggr.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIRangedAccuracyAggr : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:

	UXIRangedAccuracyAggr();

	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

	FGameplayEffectAttributeCaptureDefinition AGIDef;

	FGameplayEffectAttributeCaptureDefinition ArcheryDef;
	FGameplayEffectAttributeCaptureDefinition ArcheryMaxDef;

	FGameplayEffectAttributeCaptureDefinition MarksmanshipDef;
	FGameplayEffectAttributeCaptureDefinition MarksmanshipMaxDef;

	FGameplayEffectAttributeCaptureDefinition ThrowingDef;
	FGameplayEffectAttributeCaptureDefinition ThrowingMaxDef;	
};
