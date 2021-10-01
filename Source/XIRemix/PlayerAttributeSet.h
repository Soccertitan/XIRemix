// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PlayerAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class XIREMIX_API UPlayerAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()
	
public:

	UPlayerAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

#pragma region WarriorJob

	UPROPERTY(BlueprintReadOnly, Category = "JobWarrior", ReplicatedUsing = OnRep_WarriorCurrentLevel)
	FGameplayAttributeData WarriorCurrentLevel;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, WarriorCurrentLevel);
	UFUNCTION()
	virtual void OnRep_WarriorCurrentLevel(const FGameplayAttributeData& OldWarriorCurrentLevel);

	UPROPERTY(BlueprintReadOnly, Category = "JobWarrior", ReplicatedUsing = OnRep_WarriorMaxLevel)
	FGameplayAttributeData WarriorMaxLevel;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, WarriorMaxLevel);
	UFUNCTION()
	virtual void OnRep_WarriorMaxLevel(const FGameplayAttributeData& OldWarriorMaxLevel);

#pragma endregion

#pragma region MonkJob

	UPROPERTY(BlueprintReadOnly, Category = "JobMonk", ReplicatedUsing = OnRep_MonkCurrentLevel)
	FGameplayAttributeData MonkCurrentLevel;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MonkCurrentLevel);
	UFUNCTION()
	virtual void OnRep_MonkCurrentLevel(const FGameplayAttributeData& OldMonkCurrentLevel);

	UPROPERTY(BlueprintReadOnly, Category = "JobMonk", ReplicatedUsing = OnRep_MonkMaxLevel)
	FGameplayAttributeData MonkMaxLevel;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MonkMaxLevel);
	UFUNCTION()
	virtual void OnRep_MonkMaxLevel(const FGameplayAttributeData& OldMonkMaxLevel);

#pragma endregion

#pragma region ThiefJob

	UPROPERTY(BlueprintReadOnly, Category = "JobThief", ReplicatedUsing = OnRep_ThiefCurrentLevel)
	FGameplayAttributeData ThiefCurrentLevel;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, ThiefCurrentLevel);
	UFUNCTION()
	virtual void OnRep_ThiefCurrentLevel(const FGameplayAttributeData& OldThiefCurrentLevel);

	UPROPERTY(BlueprintReadOnly, Category = "JobThief", ReplicatedUsing = OnRep_ThiefMaxLevel)
	FGameplayAttributeData ThiefMaxLevel;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, ThiefMaxLevel);
	UFUNCTION()
	virtual void OnRep_ThiefMaxLevel(const FGameplayAttributeData& OldThiefMaxLevel);

#pragma endregion

#pragma region RedMageJob

	UPROPERTY(BlueprintReadOnly, Category = "JobRedMage", ReplicatedUsing = OnRep_RedMageCurrentLevel)
	FGameplayAttributeData RedMageCurrentLevel;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, RedMageCurrentLevel);
	UFUNCTION()
	virtual void OnRep_RedMageCurrentLevel(const FGameplayAttributeData& OldRedMageCurrentLevel);

	UPROPERTY(BlueprintReadOnly, Category = "JobRedMage", ReplicatedUsing = OnRep_RedMageMaxLevel)
	FGameplayAttributeData RedMageMaxLevel;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, RedMageMaxLevel);
	UFUNCTION()
	virtual void OnRep_RedMageMaxLevel(const FGameplayAttributeData& OldRedMageMaxLevel);

#pragma endregion

#pragma region WhiteMageJob

	UPROPERTY(BlueprintReadOnly, Category = "JobWhiteMage", ReplicatedUsing = OnRep_WhiteMageCurrentLevel)
	FGameplayAttributeData WhiteMageCurrentLevel;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, WhiteMageCurrentLevel);
	UFUNCTION()
	virtual void OnRep_WhiteMageCurrentLevel(const FGameplayAttributeData& OldWhiteMageCurrentLevel);

	UPROPERTY(BlueprintReadOnly, Category = "JobWhiteMage", ReplicatedUsing = OnRep_WhiteMageMaxLevel)
	FGameplayAttributeData WhiteMageMaxLevel;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, WhiteMageMaxLevel);
	UFUNCTION()
	virtual void OnRep_WhiteMageMaxLevel(const FGameplayAttributeData& OldWhiteMageMaxLevel);

#pragma endregion

#pragma region BlackMageJob

	UPROPERTY(BlueprintReadOnly, Category = "JobBlackMage", ReplicatedUsing = OnRep_BlackMageCurrentLevel)
	FGameplayAttributeData BlackMageCurrentLevel;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, BlackMageCurrentLevel);
	UFUNCTION()
	virtual void OnRep_BlackMageCurrentLevel(const FGameplayAttributeData& OldBlackMageCurrentLevel);

	UPROPERTY(BlueprintReadOnly, Category = "JobBlackMage", ReplicatedUsing = OnRep_BlackMageMaxLevel)
	FGameplayAttributeData BlackMageMaxLevel;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, BlackMageMaxLevel);
	UFUNCTION()
	virtual void OnRep_BlackMageMaxLevel(const FGameplayAttributeData& OldBlackMageMaxLevel);

#pragma endregion

#pragma region Currencies

	UPROPERTY(BlueprintReadOnly, Category = "Currencies", ReplicatedUsing = OnRep_Gil)
	FGameplayAttributeData Gil;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Gil);
	UFUNCTION()
	virtual void OnRep_Gil(const FGameplayAttributeData& OldGil);

#pragma endregion

};
