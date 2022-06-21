// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "XIEnemyStats.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIEnemyStats : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UXIEnemyStats();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;	

protected:

	float GetSkillRankValue(UCurveTable* CurveTable, float Level, FName RowName) const;
};
