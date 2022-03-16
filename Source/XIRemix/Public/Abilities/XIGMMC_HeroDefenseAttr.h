// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "XIGMMC_HeroDefenseAttr.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIGMMC_HeroDefenseAttr : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:

	UXIGMMC_HeroDefenseAttr();

	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

	FGameplayEffectAttributeCaptureDefinition VitalityDef;
};
