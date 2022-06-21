// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "XIAttackAggr.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIAttackAggr : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:

	UXIAttackAggr();

	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

	FGameplayEffectAttributeCaptureDefinition STRDef;

	FGameplayEffectAttributeCaptureDefinition AxeDef;
	FGameplayEffectAttributeCaptureDefinition AxeMaxDef;

	FGameplayEffectAttributeCaptureDefinition GreatAxeDef;
	FGameplayEffectAttributeCaptureDefinition GreatAxeMaxDef;

	FGameplayEffectAttributeCaptureDefinition ClubDef;
	FGameplayEffectAttributeCaptureDefinition ClubMaxDef;

	FGameplayEffectAttributeCaptureDefinition DaggerDef;
	FGameplayEffectAttributeCaptureDefinition DaggerMaxDef;

	FGameplayEffectAttributeCaptureDefinition HandToHandDef;
	FGameplayEffectAttributeCaptureDefinition HandToHandMaxDef;

	FGameplayEffectAttributeCaptureDefinition KatanaDef;
	FGameplayEffectAttributeCaptureDefinition KatanaMaxDef;

	FGameplayEffectAttributeCaptureDefinition GreatKatanaDef;
	FGameplayEffectAttributeCaptureDefinition GreatKatanaMaxDef;

	FGameplayEffectAttributeCaptureDefinition PolearmDef;
	FGameplayEffectAttributeCaptureDefinition PolearmMaxDef;

	FGameplayEffectAttributeCaptureDefinition ScytheDef;
	FGameplayEffectAttributeCaptureDefinition ScytheMaxDef;

	FGameplayEffectAttributeCaptureDefinition StaffDef;
	FGameplayEffectAttributeCaptureDefinition StaffMaxDef;

	FGameplayEffectAttributeCaptureDefinition SwordDef;
	FGameplayEffectAttributeCaptureDefinition SwordMaxDef;

	FGameplayEffectAttributeCaptureDefinition GreatSwordDef;
	FGameplayEffectAttributeCaptureDefinition GreatSwordMaxDef;
};
