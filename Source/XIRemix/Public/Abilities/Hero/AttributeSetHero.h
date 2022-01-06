// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AttributeSetGlobal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSetHero.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class XIREMIX_API UAttributeSetHero : public UAttributeSetGlobal
{
	GENERATED_BODY()

public:

	UAttributeSetHero();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	#pragma region WarriorJob

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Job|Warrior", ReplicatedUsing = OnRep_WarriorLevel)
	FGameplayAttributeData WarriorLevel;
	ATTRIBUTE_ACCESSORS(UAttributeSetHero, WarriorLevel);
	UFUNCTION()
	virtual void OnRep_WarriorLevel(const FGameplayAttributeData& OldWarriorLevel);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Job|Warrior", ReplicatedUsing = OnRep_WarriorMaxLevel)
	FGameplayAttributeData WarriorMaxLevel;
	ATTRIBUTE_ACCESSORS(UAttributeSetHero, WarriorMaxLevel);
	UFUNCTION()
	virtual void OnRep_WarriorMaxLevel(const FGameplayAttributeData& OldWarriorMaxLevel);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Job|Warrior", ReplicatedUsing = OnRep_WarriorEXP)
	FGameplayAttributeData WarriorEXP;
	ATTRIBUTE_ACCESSORS(UAttributeSetHero, WarriorEXP);
	UFUNCTION()
	virtual void OnRep_WarriorEXP(const FGameplayAttributeData& OldWarriorEXP);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Job|Warrior", ReplicatedUsing = OnRep_WarriorEXPRequired)
	FGameplayAttributeData WarriorEXPRequired;
	ATTRIBUTE_ACCESSORS(UAttributeSetHero, WarriorEXPRequired);
	UFUNCTION()
	virtual void OnRep_WarriorEXPRequired(const FGameplayAttributeData& OldWarriorEXPRequired);

#pragma endregion

#pragma region MonkJob

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Job|Monk", ReplicatedUsing = OnRep_MonkLevel)
	FGameplayAttributeData MonkLevel;
	ATTRIBUTE_ACCESSORS(UAttributeSetHero, MonkLevel);
	UFUNCTION()
	virtual void OnRep_MonkLevel(const FGameplayAttributeData& OldMonkLevel);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Job|Monk", ReplicatedUsing = OnRep_MonkMaxLevel)
	FGameplayAttributeData MonkMaxLevel;
	ATTRIBUTE_ACCESSORS(UAttributeSetHero, MonkMaxLevel);
	UFUNCTION()
	virtual void OnRep_MonkMaxLevel(const FGameplayAttributeData& OldMonkMaxLevel);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Job|Monk", ReplicatedUsing = OnRep_MonkEXP)
	FGameplayAttributeData MonkEXP;
	ATTRIBUTE_ACCESSORS(UAttributeSetHero, MonkEXP);
	UFUNCTION()
	virtual void OnRep_MonkEXP(const FGameplayAttributeData& OldMonkEXP);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Job|Monk", ReplicatedUsing = OnRep_MonkEXPRequired)
	FGameplayAttributeData MonkEXPRequired;
	ATTRIBUTE_ACCESSORS(UAttributeSetHero, MonkEXPRequired);
	UFUNCTION()
	virtual void OnRep_MonkEXPRequired(const FGameplayAttributeData& OldMonkEXPRequired);

#pragma endregion

#pragma region ThiefJob

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Job|Thief", ReplicatedUsing = OnRep_ThiefLevel)
	FGameplayAttributeData ThiefLevel;
	ATTRIBUTE_ACCESSORS(UAttributeSetHero, ThiefLevel);
	UFUNCTION()
	virtual void OnRep_ThiefLevel(const FGameplayAttributeData& OldThiefLevel);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Job|Thief", ReplicatedUsing = OnRep_ThiefMaxLevel)
	FGameplayAttributeData ThiefMaxLevel;
	ATTRIBUTE_ACCESSORS(UAttributeSetHero, ThiefMaxLevel);
	UFUNCTION()
	virtual void OnRep_ThiefMaxLevel(const FGameplayAttributeData& OldThiefMaxLevel);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Job|Thief", ReplicatedUsing = OnRep_ThiefEXP)
	FGameplayAttributeData ThiefEXP;
	ATTRIBUTE_ACCESSORS(UAttributeSetHero, ThiefEXP);
	UFUNCTION()
	virtual void OnRep_ThiefEXP(const FGameplayAttributeData& OldThiefEXP);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Job|Thief", ReplicatedUsing = OnRep_ThiefEXPRequired)
	FGameplayAttributeData ThiefEXPRequired;
	ATTRIBUTE_ACCESSORS(UAttributeSetHero, ThiefEXPRequired);
	UFUNCTION()
	virtual void OnRep_ThiefEXPRequired(const FGameplayAttributeData& OldThiefEXPRequired);

#pragma endregion

#pragma region RedMageJob

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Job|RedMage", ReplicatedUsing = OnRep_RedMageLevel)
	FGameplayAttributeData RedMageLevel;
	ATTRIBUTE_ACCESSORS(UAttributeSetHero, RedMageLevel);
	UFUNCTION()
	virtual void OnRep_RedMageLevel(const FGameplayAttributeData& OldRedMageLevel);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Job|RedMage", ReplicatedUsing = OnRep_RedMageMaxLevel)
	FGameplayAttributeData RedMageMaxLevel;
	ATTRIBUTE_ACCESSORS(UAttributeSetHero, RedMageMaxLevel);
	UFUNCTION()
	virtual void OnRep_RedMageMaxLevel(const FGameplayAttributeData& OldRedMageMaxLevel);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Job|RedMage", ReplicatedUsing = OnRep_RedMageEXP)
	FGameplayAttributeData RedMageEXP;
	ATTRIBUTE_ACCESSORS(UAttributeSetHero, RedMageEXP);
	UFUNCTION()
	virtual void OnRep_RedMageEXP(const FGameplayAttributeData& OldRedMageEXP);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Job|RedMage", ReplicatedUsing = OnRep_RedMageEXPRequired)
	FGameplayAttributeData RedMageEXPRequired;
	ATTRIBUTE_ACCESSORS(UAttributeSetHero, RedMageEXPRequired);
	UFUNCTION()
	virtual void OnRep_RedMageEXPRequired(const FGameplayAttributeData& OldRedMageEXPRequired);

#pragma endregion

#pragma region WhiteMageJob

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Job|WhiteMage", ReplicatedUsing = OnRep_WhiteMageLevel)
	FGameplayAttributeData WhiteMageLevel;
	ATTRIBUTE_ACCESSORS(UAttributeSetHero, WhiteMageLevel);
	UFUNCTION()
	virtual void OnRep_WhiteMageLevel(const FGameplayAttributeData& OldWhiteMageLevel);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Job|WhiteMage", ReplicatedUsing = OnRep_WhiteMageMaxLevel)
	FGameplayAttributeData WhiteMageMaxLevel;
	ATTRIBUTE_ACCESSORS(UAttributeSetHero, WhiteMageMaxLevel);
	UFUNCTION()
	virtual void OnRep_WhiteMageMaxLevel(const FGameplayAttributeData& OldWhiteMageMaxLevel);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Job|WhiteMage", ReplicatedUsing = OnRep_WhiteMageEXP)
	FGameplayAttributeData WhiteMageEXP;
	ATTRIBUTE_ACCESSORS(UAttributeSetHero, WhiteMageEXP);
	UFUNCTION()
	virtual void OnRep_WhiteMageEXP(const FGameplayAttributeData& OldWhiteMageEXP);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Job|WhiteMage", ReplicatedUsing = OnRep_WhiteMageEXPRequired)
	FGameplayAttributeData WhiteMageEXPRequired;
	ATTRIBUTE_ACCESSORS(UAttributeSetHero, WhiteMageEXPRequired);
	UFUNCTION()
	virtual void OnRep_WhiteMageEXPRequired(const FGameplayAttributeData& OldWhiteMageEXPRequired);

#pragma endregion

#pragma region BlackMageJob

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Job|BlackMage", ReplicatedUsing = OnRep_BlackMageLevel)
	FGameplayAttributeData BlackMageLevel;
	ATTRIBUTE_ACCESSORS(UAttributeSetHero, BlackMageLevel);
	UFUNCTION()
	virtual void OnRep_BlackMageLevel(const FGameplayAttributeData& OldBlackMageLevel);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Job|BlackMage", ReplicatedUsing = OnRep_BlackMageMaxLevel)
	FGameplayAttributeData BlackMageMaxLevel;
	ATTRIBUTE_ACCESSORS(UAttributeSetHero, BlackMageMaxLevel);
	UFUNCTION()
	virtual void OnRep_BlackMageMaxLevel(const FGameplayAttributeData& OldBlackMageMaxLevel);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Job|BlackMage", ReplicatedUsing = OnRep_BlackMageEXP)
	FGameplayAttributeData BlackMageEXP;
	ATTRIBUTE_ACCESSORS(UAttributeSetHero, BlackMageEXP);
	UFUNCTION()
	virtual void OnRep_BlackMageEXP(const FGameplayAttributeData& OldBlackMageEXP);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Job|BlackMage", ReplicatedUsing = OnRep_BlackMageEXPRequired)
	FGameplayAttributeData BlackMageEXPRequired;
	ATTRIBUTE_ACCESSORS(UAttributeSetHero, BlackMageEXPRequired);
	UFUNCTION()
	virtual void OnRep_BlackMageEXPRequired(const FGameplayAttributeData& OldBlackMageEXPRequired);

#pragma endregion

#pragma region Currencies

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Currencies", ReplicatedUsing = OnRep_Gil)
	FGameplayAttributeData Gil;
	ATTRIBUTE_ACCESSORS(UAttributeSetHero, Gil);
	UFUNCTION()
	virtual void OnRep_Gil(const FGameplayAttributeData& OldGil);

#pragma endregion

};