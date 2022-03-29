// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "XIEnums.h"
#include "XIStatsGrowthRank.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIStatsGrowthRank : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank HitPoints = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank ManaPoints = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Strength = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Dexterity = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Vitality = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Agility = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Intelligence = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Mind = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Charisma = EXISkillRank::H;
};
