// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "XIEnums.h"
#include "XIStatsGrowthData.generated.h"

/*
 * Defines the relationship between different rankings.
 */
USTRUCT()
struct FXIStatsGrowthDataItem
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	EXISkillRank StatGrowthRank = EXISkillRank::A;

	UPROPERTY(EditAnywhere)
	float HitPointsScale;
	UPROPERTY(EditAnywhere)
	float HitPointsBase;
	UPROPERTY(EditAnywhere)
	float HitPointsMultiplier;

	UPROPERTY(EditAnywhere)
	float ManaPointsScale;
	UPROPERTY(EditAnywhere)
	float ManaPointsBase;

	UPROPERTY(EditAnywhere)
	float AttributeScale;
	UPROPERTY(EditAnywhere)
	float AttributeBase;
};

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIStatsGrowthData : public UDataAsset
{
	GENERATED_BODY()
	
public:

	void GetHitPointsGrowth(EXISkillRank GrowthRank, float& OutHitPointsScale, float& OutHitPointsBase, float& OutHitPointsMultiplier) const;
	void GetManaPointsGrowth(EXISkillRank GrowthRank, float& OutManaPointsScale, float& OutManaPointsBase) const;
	void GetAttributeGrowth(EXISkillRank GrowthRank, float& OutAttributeScale, float& OutAttributeBase) const;

private:

	UPROPERTY(EditAnywhere)
	TArray<FXIStatsGrowthDataItem> XIStatsGrowthData;
};
