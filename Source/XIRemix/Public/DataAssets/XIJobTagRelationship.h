// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AttributeSet.h"
#include "DataAssets/XIJobAbilityData.h"
#include "DataAssets/XICombatSkillsRank.h"
#include "DataAssets/XIStatsGrowthRank.h"
#include "Engine/DataAsset.h"
#include "XIJobTagRelationship.generated.h"

/*
 * Defines the relationship between Tags and the Hero Attribute Job set
 */
USTRUCT(BlueprintType)
struct FXIJobTagRelationshipItem
{
    GENERATED_BODY()
 
    /* The tag that this relationship is about. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Job)
    FGameplayTagContainer JobTags;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Job)
	FGameplayAttribute JobLevelAttribute;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Job)
	FGameplayAttribute JobLevelMaxAttribute;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Job)
	FGameplayAttribute JobExpAttribute;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Job)
	FGameplayAttribute JobExpRequiredAttribute;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Job)
	UXIJobAbilityData* JobAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Job)
	UXICombatSkillsRank* CombatSkillsRank;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Job)
	UXIStatsGrowthRank* StatsGrowthRank;
};

/**
 * 
 */
UCLASS(BlueprintType)
class XIREMIX_API UXIJobTagRelationship : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "XIJobTagRelationship")
	bool GetXIJobTagRelationship(FGameplayTag InJobTag, FXIJobTagRelationshipItem& JobTagRelationship);

private:
	// The relationship between Job Tags and their attributes
	UPROPERTY(EditAnywhere)
	TArray<FXIJobTagRelationshipItem> JobTagRelationships;
};
