// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "XIJobExp.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIJobExp : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UXIJobExp();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
