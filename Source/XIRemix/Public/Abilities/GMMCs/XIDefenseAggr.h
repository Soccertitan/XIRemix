// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "XIDefenseAggr.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIDefenseAggr : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:

	UXIDefenseAggr();

	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

	FGameplayEffectAttributeCaptureDefinition VitalityDef;
};
