// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "XIMeleeDamage.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIMeleeDamage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UXIMeleeDamage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

	float GetWeaponBaseDamage(AActor* Actor, FGameplayTag OutWeaponTag) const;
};
