// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "XIAbilityCost.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIAbilityCost : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
