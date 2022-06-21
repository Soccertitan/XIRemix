// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "XIAttackSubHandAggr.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIAttackSubHandAggr : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:

	UXIAttackSubHandAggr();

	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

	FGameplayEffectAttributeCaptureDefinition STRDef;

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
