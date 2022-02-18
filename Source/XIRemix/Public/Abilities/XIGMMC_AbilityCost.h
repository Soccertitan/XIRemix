// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "XIGMMC_AbilityCost.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIGMMC_AbilityCost : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:

	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
