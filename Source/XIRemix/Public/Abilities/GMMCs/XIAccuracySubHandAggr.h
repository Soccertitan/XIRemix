// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "XIAccuracySubHandAggr.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIAccuracySubHandAggr : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:

	UXIAccuracySubHandAggr();

	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

	FGameplayEffectAttributeCaptureDefinition DexDef;

	FGameplayEffectAttributeCaptureDefinition AxeDef;
	FGameplayEffectAttributeCaptureDefinition AxeMaxDef;

	FGameplayEffectAttributeCaptureDefinition ClubDef;
	FGameplayEffectAttributeCaptureDefinition ClubMaxDef;

	FGameplayEffectAttributeCaptureDefinition DaggerDef;
	FGameplayEffectAttributeCaptureDefinition DaggerMaxDef;

	FGameplayEffectAttributeCaptureDefinition KatanaDef;
	FGameplayEffectAttributeCaptureDefinition KatanaMaxDef;
	
	FGameplayEffectAttributeCaptureDefinition SwordDef;
	FGameplayEffectAttributeCaptureDefinition SwordMaxDef;	
};
