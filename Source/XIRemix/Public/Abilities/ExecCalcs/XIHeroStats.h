// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "XIEnums.h"
#include "XIHeroStats.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIHeroStats : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UXIHeroStats();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;	

protected:

	float CalculateHPAttribute(float MainJobLevel, float SubJobLevel, float RaceHPScale, float RaceHPBase, float RaceHPMultiplier, float MJHPScale, float MJHPBase, float MJHPMulitiplier, float SJHPScale, float SJHPBase) const;
	float CalculateMPAttribute(float MainJobLevel, float SubJobLevel, float RaceMPScale, float RaceMPBase, float MJMPScale, float MJMPBase, float SJMPScale, float SJMPBase) const;
	float CalculateBasicAttribute(float MainJobLevel, float SubJobLevel, float RaceScale, float RaceBase, float MJScale, float MJBase, float SJScale, float SJBase) const;
	float GetSkillRankValue(UCurveTable* CurveTable, float Level, FName RowName) const;

	static const TMap<EXISkillRank, FName> SkillRankNameMap;
};
