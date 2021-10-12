// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GlobalAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "HeroAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class XIREMIX_API UHeroAttributeSet : public UGlobalAttributeSet
{
	GENERATED_BODY()

public:

	UHeroAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	#pragma region WarriorJob

	UPROPERTY(BlueprintReadOnly, Category = "JobWarrior", ReplicatedUsing = OnRep_WarriorLevel)
	FGameplayAttributeData WarriorLevel;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, WarriorLevel);
	UFUNCTION()
	virtual void OnRep_WarriorLevel(const FGameplayAttributeData& OldWarriorLevel);

	UPROPERTY(BlueprintReadOnly, Category = "JobWarrior", ReplicatedUsing = OnRep_WarriorMaxLevel)
	FGameplayAttributeData WarriorMaxLevel;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, WarriorMaxLevel);
	UFUNCTION()
	virtual void OnRep_WarriorMaxLevel(const FGameplayAttributeData& OldWarriorMaxLevel);

	UPROPERTY(BlueprintReadOnly, Category = "JobWarrior", ReplicatedUsing = OnRep_WarriorEXP)
	FGameplayAttributeData WarriorEXP;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, WarriorEXP);
	UFUNCTION()
	virtual void OnRep_WarriorEXP(const FGameplayAttributeData& OldWarriorEXP);

	UPROPERTY(BlueprintReadOnly, Category = "JobWarrior", ReplicatedUsing = OnRep_WarriorEXPRequired)
	FGameplayAttributeData WarriorEXPRequired;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, WarriorEXPRequired);
	UFUNCTION()
	virtual void OnRep_WarriorEXPRequired(const FGameplayAttributeData& OldWarriorEXPRequired);

#pragma endregion

#pragma region MonkJob

	UPROPERTY(BlueprintReadOnly, Category = "JobMonk", ReplicatedUsing = OnRep_MonkLevel)
	FGameplayAttributeData MonkLevel;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, MonkLevel);
	UFUNCTION()
	virtual void OnRep_MonkLevel(const FGameplayAttributeData& OldMonkLevel);

	UPROPERTY(BlueprintReadOnly, Category = "JobMonk", ReplicatedUsing = OnRep_MonkMaxLevel)
	FGameplayAttributeData MonkMaxLevel;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, MonkMaxLevel);
	UFUNCTION()
	virtual void OnRep_MonkMaxLevel(const FGameplayAttributeData& OldMonkMaxLevel);

	UPROPERTY(BlueprintReadOnly, Category = "JobMonk", ReplicatedUsing = OnRep_MonkEXP)
	FGameplayAttributeData MonkEXP;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, MonkEXP);
	UFUNCTION()
	virtual void OnRep_MonkEXP(const FGameplayAttributeData& OldMonkEXP);

	UPROPERTY(BlueprintReadOnly, Category = "JobMonk", ReplicatedUsing = OnRep_MonkEXPRequired)
	FGameplayAttributeData MonkEXPRequired;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, MonkEXPRequired);
	UFUNCTION()
	virtual void OnRep_MonkEXPRequired(const FGameplayAttributeData& OldMonkEXPRequired);

#pragma endregion

#pragma region ThiefJob

	UPROPERTY(BlueprintReadOnly, Category = "JobThief", ReplicatedUsing = OnRep_ThiefLevel)
	FGameplayAttributeData ThiefLevel;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, ThiefLevel);
	UFUNCTION()
	virtual void OnRep_ThiefLevel(const FGameplayAttributeData& OldThiefLevel);

	UPROPERTY(BlueprintReadOnly, Category = "JobThief", ReplicatedUsing = OnRep_ThiefMaxLevel)
	FGameplayAttributeData ThiefMaxLevel;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, ThiefMaxLevel);
	UFUNCTION()
	virtual void OnRep_ThiefMaxLevel(const FGameplayAttributeData& OldThiefMaxLevel);

	UPROPERTY(BlueprintReadOnly, Category = "JobThief", ReplicatedUsing = OnRep_ThiefEXP)
	FGameplayAttributeData ThiefEXP;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, ThiefEXP);
	UFUNCTION()
	virtual void OnRep_ThiefEXP(const FGameplayAttributeData& OldThiefEXP);

	UPROPERTY(BlueprintReadOnly, Category = "JobThief", ReplicatedUsing = OnRep_ThiefEXPRequired)
	FGameplayAttributeData ThiefEXPRequired;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, ThiefEXPRequired);
	UFUNCTION()
	virtual void OnRep_ThiefEXPRequired(const FGameplayAttributeData& OldThiefEXPRequired);

#pragma endregion

#pragma region RedMageJob

	UPROPERTY(BlueprintReadOnly, Category = "JobRedMage", ReplicatedUsing = OnRep_RedMageLevel)
	FGameplayAttributeData RedMageLevel;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, RedMageLevel);
	UFUNCTION()
	virtual void OnRep_RedMageLevel(const FGameplayAttributeData& OldRedMageLevel);

	UPROPERTY(BlueprintReadOnly, Category = "JobRedMage", ReplicatedUsing = OnRep_RedMageMaxLevel)
	FGameplayAttributeData RedMageMaxLevel;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, RedMageMaxLevel);
	UFUNCTION()
	virtual void OnRep_RedMageMaxLevel(const FGameplayAttributeData& OldRedMageMaxLevel);

	UPROPERTY(BlueprintReadOnly, Category = "JobRedMage", ReplicatedUsing = OnRep_RedMageEXP)
	FGameplayAttributeData RedMageEXP;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, RedMageEXP);
	UFUNCTION()
	virtual void OnRep_RedMageEXP(const FGameplayAttributeData& OldRedMageEXP);

	UPROPERTY(BlueprintReadOnly, Category = "JobRedMage", ReplicatedUsing = OnRep_RedMageEXPRequired)
	FGameplayAttributeData RedMageEXPRequired;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, RedMageEXPRequired);
	UFUNCTION()
	virtual void OnRep_RedMageEXPRequired(const FGameplayAttributeData& OldRedMageEXPRequired);

#pragma endregion

#pragma region WhiteMageJob

	UPROPERTY(BlueprintReadOnly, Category = "JobWhiteMage", ReplicatedUsing = OnRep_WhiteMageLevel)
	FGameplayAttributeData WhiteMageLevel;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, WhiteMageLevel);
	UFUNCTION()
	virtual void OnRep_WhiteMageLevel(const FGameplayAttributeData& OldWhiteMageLevel);

	UPROPERTY(BlueprintReadOnly, Category = "JobWhiteMage", ReplicatedUsing = OnRep_WhiteMageMaxLevel)
	FGameplayAttributeData WhiteMageMaxLevel;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, WhiteMageMaxLevel);
	UFUNCTION()
	virtual void OnRep_WhiteMageMaxLevel(const FGameplayAttributeData& OldWhiteMageMaxLevel);

	UPROPERTY(BlueprintReadOnly, Category = "JobWhiteMage", ReplicatedUsing = OnRep_WhiteMageEXP)
	FGameplayAttributeData WhiteMageEXP;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, WhiteMageEXP);
	UFUNCTION()
	virtual void OnRep_WhiteMageEXP(const FGameplayAttributeData& OldWhiteMageEXP);

	UPROPERTY(BlueprintReadOnly, Category = "JobWhiteMage", ReplicatedUsing = OnRep_WhiteMageEXPRequired)
	FGameplayAttributeData WhiteMageEXPRequired;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, WhiteMageEXPRequired);
	UFUNCTION()
	virtual void OnRep_WhiteMageEXPRequired(const FGameplayAttributeData& OldWhiteMageEXPRequired);

#pragma endregion

#pragma region BlackMageJob

	UPROPERTY(BlueprintReadOnly, Category = "JobBlackMage", ReplicatedUsing = OnRep_BlackMageLevel)
	FGameplayAttributeData BlackMageLevel;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, BlackMageLevel);
	UFUNCTION()
	virtual void OnRep_BlackMageLevel(const FGameplayAttributeData& OldBlackMageLevel);

	UPROPERTY(BlueprintReadOnly, Category = "JobBlackMage", ReplicatedUsing = OnRep_BlackMageMaxLevel)
	FGameplayAttributeData BlackMageMaxLevel;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, BlackMageMaxLevel);
	UFUNCTION()
	virtual void OnRep_BlackMageMaxLevel(const FGameplayAttributeData& OldBlackMageMaxLevel);

	UPROPERTY(BlueprintReadOnly, Category = "JobBlackMage", ReplicatedUsing = OnRep_BlackMageEXP)
	FGameplayAttributeData BlackMageEXP;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, BlackMageEXP);
	UFUNCTION()
	virtual void OnRep_BlackMageEXP(const FGameplayAttributeData& OldBlackMageEXP);

	UPROPERTY(BlueprintReadOnly, Category = "JobBlackMage", ReplicatedUsing = OnRep_BlackMageEXPRequired)
	FGameplayAttributeData BlackMageEXPRequired;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, BlackMageEXPRequired);
	UFUNCTION()
	virtual void OnRep_BlackMageEXPRequired(const FGameplayAttributeData& OldBlackMageEXPRequired);

#pragma endregion

#pragma region Currencies

	UPROPERTY(BlueprintReadOnly, Category = "Currencies", ReplicatedUsing = OnRep_Gil)
	FGameplayAttributeData Gil;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, Gil);
	UFUNCTION()
	virtual void OnRep_Gil(const FGameplayAttributeData& OldGil);

#pragma endregion

};
