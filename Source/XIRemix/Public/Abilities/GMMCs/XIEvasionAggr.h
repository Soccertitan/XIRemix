// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "XIEvasionAggr.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIEvasionAggr : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:

	UXIEvasionAggr();

	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

	FGameplayEffectAttributeCaptureDefinition EvasionDef;
	FGameplayEffectAttributeCaptureDefinition AgiDef;
};
