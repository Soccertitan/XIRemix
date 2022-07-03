// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DataAssets/XIAbilityTagRelationship.h"
#include "DataAssets/XIJobTagRelationship.h"
#include "DataAssets/XIStatsGrowthRank.h"
#include "DataAssets/XIStatsGrowthData.h"
#include "XIAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelUp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FXICycleTarget, float, Direction);

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	UXIAbilitySystemComponent();
	
	bool CharacterAbilitiesGiven = false;
	bool StartupEffectsApplied = false;

	UPROPERTY(BlueprintAssignable)
	FOnLevelUp OnLevelUp;
	UPROPERTY(BlueprintAssignable)
	FXICycleTarget OnXICycleTarget;

	void GetRelationshipActivationTagRequirements(const FGameplayTagContainer& AbilityTags, FGameplayTagContainer& OutActivationRequired, FGameplayTagContainer& OutActivationBlocked) const;
	virtual void ApplyAbilityBlockAndCancelTags(const FGameplayTagContainer& AbilityTags, UGameplayAbility* RequestingAbility, bool bEnableBlockTags, const FGameplayTagContainer& BlockTags, bool bExecuteCancelTags, const FGameplayTagContainer& CancelTags) override;
	
	virtual void GetXIJobTagRelationship(const FGameplayTag JobTag, FXIJobTagRelationshipItem& JobTagRelationshipItem) const;

	UFUNCTION(BlueprintCallable, Category = "GameplayCue", Meta = (AutoCreateRefTerm = "GameplayCueParameters", GameplayTagFilter = "GameplayCue"))
	void ExecuteGameplayCueLocal(const FGameplayTag GameplayCueTag, const FGameplayCueParameters& GameplayCueParameters);

	UFUNCTION(BlueprintCallable, Category = "GameplayCue", Meta = (AutoCreateRefTerm = "GameplayCueParameters", GameplayTagFilter = "GameplayCue"))
	void AddGameplayCueLocal(const FGameplayTag GameplayCueTag, const FGameplayCueParameters& GameplayCueParameters);

	UFUNCTION(BlueprintCallable, Category = "GameplayCue", Meta = (AutoCreateRefTerm = "GameplayCueParameters", GameplayTagFilter = "GameplayCue"))
	void RemoveGameplayCueLocal(const FGameplayTag GameplayCueTag, const FGameplayCueParameters& GameplayCueParameters);

	// Called by ExecCalc XIJobEXP
	void LevelUp();

	//Used for callbacks for Ability Tasks
	virtual void XICycleTarget(float Direction);

	FORCEINLINE UXIStatsGrowthRank* GetXIStatsGrowthRank() const {return StatsGrowthRank;}
	FORCEINLINE UXIStatsGrowthData* GetXIStatsGrowthData() const {return StatsGrowthData;}
	FORCEINLINE UCurveTable* GetAttributesCurveTable() const {return AttributesCurveTable;}
	FORCEINLINE UCurveTable* GetExpToNextLevelCurveTable() const {return ExpToNextLevelCurveTable;}

protected:
    /* Mapping of Ability Tag to block and cancel tags. */
    UPROPERTY(EditDefaultsOnly, Category = "Abilities|GameplayTags")
    UXIAbilityTagRelationship* AbilityTagRelationship;

	/* Mapping of Job Tags to Attributes*/
	UPROPERTY(EditDefaultsOnly, Category = "Abilities|GameplayTags")
	UXIJobTagRelationship* JobTagRelationship;

	//Stats Growth Ranking data to determine stats. Typicall for XICharacterHeros.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities|Stats")
	UXIStatsGrowthRank* StatsGrowthRank;

	//Referenced by StatsGrowthRank to get the value for calculating Stat Growth
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities|Stats")
	UXIStatsGrowthData* StatsGrowthData;

	//For Heros; Maps Skill Rankings to Attribute Values based on Job Level. For Enemies, directly maps attributes to values.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities|Stats")
	UCurveTable* AttributesCurveTable;

	//A lookup curve table to check how much EXP is required to reach the next level.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities|Stats")
	UCurveTable* ExpToNextLevelCurveTable;
};
