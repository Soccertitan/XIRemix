// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "XICharacterStats.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXICharacterStats : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UXICharacterStats();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;	
};
