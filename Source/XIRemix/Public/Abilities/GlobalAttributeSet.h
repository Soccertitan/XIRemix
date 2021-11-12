// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GlobalAttributeSet.generated.h"

// Macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class XIREMIX_API UGlobalAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:

	UGlobalAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

#pragma region ResourceAttributes // Defines HP, MP, TP resources

	UPROPERTY(BlueprintReadOnly, Category = "ResourceAttributes", ReplicatedUsing = OnRep_HitPoints)
	FGameplayAttributeData HitPoints;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, HitPoints);
	UFUNCTION()
	virtual void OnRep_HitPoints(const FGameplayAttributeData& OldHitPoints);

	UPROPERTY(BlueprintReadOnly, Category = "ResourceAttributes", ReplicatedUsing = OnRep_HitPointsMax)
	FGameplayAttributeData HitPointsMax;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, HitPointsMax);
	UFUNCTION()
	virtual void OnRep_HitPointsMax(const FGameplayAttributeData& OldHitPointsMax);

	UPROPERTY(BlueprintReadOnly, Category = "ResourceAttributes", ReplicatedUsing = OnRep_ManaPoints)
	FGameplayAttributeData ManaPoints;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, ManaPoints);
	UFUNCTION()
	virtual void OnRep_ManaPoints(const FGameplayAttributeData& OldManaPoints);

	UPROPERTY(BlueprintReadOnly, Category = "ResourceAttributes", ReplicatedUsing = OnRep_ManaPointsMax)
	FGameplayAttributeData ManaPointsMax;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, ManaPointsMax);
	UFUNCTION()
	virtual void OnRep_ManaPointsMax(const FGameplayAttributeData& OldManaPointsMax);

	UPROPERTY(BlueprintReadOnly, Category = "ResourceAttributes", ReplicatedUsing = OnRep_TacticalPoints)
	FGameplayAttributeData TacticalPoints;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, TacticalPoints);
	UFUNCTION()
	virtual void OnRep_TacticalPoints(const FGameplayAttributeData& OldTacticalPoints);

	UPROPERTY(BlueprintReadOnly, Category = "ResourceAttributes", ReplicatedUsing = OnRep_TacticalPointsMax)
	FGameplayAttributeData TacticalPointsMax;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, TacticalPointsMax);
	UFUNCTION()
	virtual void OnRep_TacticalPointsMax(const FGameplayAttributeData& OldTacticalPointsMax);

#pragma endregion ResourceAttributes

#pragma region MainAttributes //Defines the main attributes Str, Dex, Agi, Vit, Int, Mnd, Chr

	UPROPERTY(BlueprintReadOnly, Category = "MainAttributes", ReplicatedUsing = OnRep_Strength)
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, Strength);
	UFUNCTION()
	virtual void OnRep_Strength(const FGameplayAttributeData& OldStrength);

	UPROPERTY(BlueprintReadOnly, Category = "MainAttributes", ReplicatedUsing = OnRep_Dexterity)
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, Dexterity);
	UFUNCTION()
	virtual void OnRep_Dexterity(const FGameplayAttributeData& OldDexterity);

	UPROPERTY(BlueprintReadOnly, Category = "MainAttributes", ReplicatedUsing = OnRep_Vitality)
	FGameplayAttributeData Vitality;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, Vitality);
	UFUNCTION()
	virtual void OnRep_Vitality(const FGameplayAttributeData& OldVitality);

	UPROPERTY(BlueprintReadOnly, Category = "MainAttributes", ReplicatedUsing = OnRep_Agility)
	FGameplayAttributeData Agility;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, Agility);
	UFUNCTION()
	virtual void OnRep_Agility(const FGameplayAttributeData& OldAgility);

	UPROPERTY(BlueprintReadOnly, Category = "MainAttributes", ReplicatedUsing = OnRep_Intelligence)
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, Intelligence);
	UFUNCTION()
	virtual void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence);

	UPROPERTY(BlueprintReadOnly, Category = "MainAttributes", ReplicatedUsing = OnRep_Mind)
	FGameplayAttributeData Mind;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, Mind);
	UFUNCTION()
	virtual void OnRep_Mind(const FGameplayAttributeData& OldMind);

	UPROPERTY(BlueprintReadOnly, Category = "MainAttributes", ReplicatedUsing = OnRep_Charisma)
	FGameplayAttributeData Charisma;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, Charisma);
	UFUNCTION()
	virtual void OnRep_Charisma(const FGameplayAttributeData& OldCharisma);

#pragma endregion MainAttributes
	
#pragma region PhysicalSubAttributes //Defines Attack, Accuracy, Defense, Evasion, Crits, and Movement

	UPROPERTY(BlueprintReadOnly, Category = "SubAttributesPhysical", ReplicatedUsing = OnRep_Attack)
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, Attack);
	UFUNCTION()
	virtual void OnRep_Attack(const FGameplayAttributeData& OldAttack);

	UPROPERTY(BlueprintReadOnly, Category = "SubAttributesPhysical", ReplicatedUsing = OnRep_RangedAttack)
	FGameplayAttributeData RangedAttack;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, RangedAttack);
	UFUNCTION()
	virtual void OnRep_RangedAttack(const FGameplayAttributeData& OldRangedAttack);

	UPROPERTY(BlueprintReadOnly, Category = "SubAttributesPhysical", ReplicatedUsing = OnRep_Defense)
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, Defense);
	UFUNCTION()
	virtual void OnRep_Defense(const FGameplayAttributeData& OldDefense);

	UPROPERTY(BlueprintReadOnly, Category = "SubAttributesPhysical", ReplicatedUsing = OnRep_Accuracy)
	FGameplayAttributeData Accuracy;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, Accuracy);
	UFUNCTION()
	virtual void OnRep_Accuracy(const FGameplayAttributeData& OldAccuracy);

	UPROPERTY(BlueprintReadOnly, Category = "SubAttributesPhysical", ReplicatedUsing = OnRep_Evasion)
	FGameplayAttributeData Evasion;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, Evasion);
	UFUNCTION()
	virtual void OnRep_Evasion(const FGameplayAttributeData& OldEvasion);

	UPROPERTY(BlueprintReadOnly, Category = "SubAttributesPhysical", ReplicatedUsing = OnRep_CriticalHitRate)
	FGameplayAttributeData CriticalHitRate;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, CriticalHitRate);
	UFUNCTION()
	virtual void OnRep_CriticalHitRate(const FGameplayAttributeData& OldCriticalHitRate);

	UPROPERTY(BlueprintReadOnly, Category = "SubAttributesPhysical", ReplicatedUsing = OnRep_CriticalHitBonus)
	FGameplayAttributeData CriticalHitBonus;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, CriticalHitBonus);
	UFUNCTION()
	virtual void OnRep_CriticalHitBonus(const FGameplayAttributeData& OldCriticalHitBonus);

	UPROPERTY(BlueprintReadOnly, Category = "SubAttributesPhysical", ReplicatedUsing = OnRep_RangedCriticalHitRate)
	FGameplayAttributeData RangedCriticalHitRate;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, RangedCriticalHitRate);
	UFUNCTION()
	virtual void OnRep_RangedCriticalHitRate(const FGameplayAttributeData& OldRangedCriticalHitRate);

	UPROPERTY(BlueprintReadOnly, Category = "SubAttributesPhysical", ReplicatedUsing = OnRep_RangedCriticalHitBonus)
	FGameplayAttributeData RangedCriticalHitBonus;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, RangedCriticalHitBonus);
	UFUNCTION()
	virtual void OnRep_RangedCriticalHitBonus(const FGameplayAttributeData& OldRangedCriticalHitBonus);

	UPROPERTY(BlueprintReadOnly, Category = "SubAttributesMagical", ReplicatedUsing = OnRep_AttackSpeed)
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, AttackSpeed);
	UFUNCTION()
	virtual void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed);

	UPROPERTY(BlueprintReadOnly, Category = "SubAttributesMagical", ReplicatedUsing = OnRep_RangedAttackSpeed)
	FGameplayAttributeData RangedAttackSpeed;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, RangedAttackSpeed);
	UFUNCTION()
	virtual void OnRep_RangedAttackSpeed(const FGameplayAttributeData& OldRangedAttackSpeed);

	UPROPERTY(BlueprintReadOnly, Category = "MoveSpeed", ReplicatedUsing = OnRep_MoveSpeed)
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, MoveSpeed);
	UFUNCTION()
	virtual void OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed);

#pragma endregion MeleeSubAttributes

#pragma region MagicSubAttributes //Defines Magic Attack, Accuracy, Defense, Evasion, and Crits

	UPROPERTY(BlueprintReadOnly, Category = "SubAttributesMagical", ReplicatedUsing = OnRep_MagicAttack)
	FGameplayAttributeData MagicAttack;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, MagicAttack);
	UFUNCTION()
	virtual void OnRep_MagicAttack(const FGameplayAttributeData& OldMagicAttack);

	UPROPERTY(BlueprintReadOnly, Category = "SubAttributesMagical", ReplicatedUsing = OnRep_MagicDefense)
	FGameplayAttributeData MagicDefense;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, MagicDefense);
	UFUNCTION()
	virtual void OnRep_MagicDefense(const FGameplayAttributeData& OldMagicDefense);

	UPROPERTY(BlueprintReadOnly, Category = "SubAttributesMagical", ReplicatedUsing = OnRep_MagicAccuracy)
	FGameplayAttributeData MagicAccuracy;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, MagicAccuracy);
	UFUNCTION()
	virtual void OnRep_MagicAccuracy(const FGameplayAttributeData& OldMagicAccuracy);

	UPROPERTY(BlueprintReadOnly, Category = "SubAttributesMagical", ReplicatedUsing = OnRep_MagicEvasion)
	FGameplayAttributeData MagicEvasion;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, MagicEvasion);
	UFUNCTION()
	virtual void OnRep_MagicEvasion(const FGameplayAttributeData& OldMagicEvasion);

	UPROPERTY(BlueprintReadOnly, Category = "SubAttributesMagical", ReplicatedUsing = OnRep_MagicCriticalHitRate)
	FGameplayAttributeData MagicCriticalHitRate;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, MagicCriticalHitRate);
	UFUNCTION()
	virtual void OnRep_MagicCriticalHitRate(const FGameplayAttributeData& OldMagicCriticalHitRate);

	UPROPERTY(BlueprintReadOnly, Category = "SubAttributesMagical", ReplicatedUsing = OnRep_MagicCriticalHitBonus)
	FGameplayAttributeData MagicCriticalHitBonus;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, MagicCriticalHitBonus);
	UFUNCTION()
	virtual void OnRep_MagicCriticalHitBonus(const FGameplayAttributeData& OldMagicCriticalHitBonus);

	UPROPERTY(BlueprintReadOnly, Category = "SubAttributesMagical", ReplicatedUsing = OnRep_CastSpeed)
	FGameplayAttributeData CastSpeed;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, CastSpeed);
	UFUNCTION()
	virtual void OnRep_CastSpeed(const FGameplayAttributeData& OldCastSpeed);

#pragma endregion MagicSubAttributes

#pragma region ElementalResistances //Defines Fire, Ice, Lightning, Water, Earth, Wind, Dark, and Light Resistance

	UPROPERTY(BlueprintReadOnly, Category = "ElementalAttributes", ReplicatedUsing = OnRep_FireResistance)
	FGameplayAttributeData FireResistance;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, FireResistance);
	UFUNCTION()
	virtual void OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance);

	UPROPERTY(BlueprintReadOnly, Category = "ElementalAttributes", ReplicatedUsing = OnRep_IceResistance)
	FGameplayAttributeData IceResistance;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, IceResistance);
	UFUNCTION()
	virtual void OnRep_IceResistance(const FGameplayAttributeData& OldIceResistance);

	UPROPERTY(BlueprintReadOnly, Category = "ElementalAttributes", ReplicatedUsing = OnRep_WindResistance)
	FGameplayAttributeData WindResistance;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, WindResistance);
	UFUNCTION()
	virtual void OnRep_WindResistance(const FGameplayAttributeData& OldWindResistance);

	UPROPERTY(BlueprintReadOnly, Category = "ElementalAttributes", ReplicatedUsing = OnRep_LightningResistance)
	FGameplayAttributeData LightningResistance;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, LightningResistance);
	UFUNCTION()
	virtual void OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance);

	UPROPERTY(BlueprintReadOnly, Category = "ElementalAttributes", ReplicatedUsing = OnRep_EarthResistance)
	FGameplayAttributeData EarthResistance;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, EarthResistance);
	UFUNCTION()
	virtual void OnRep_EarthResistance(const FGameplayAttributeData& OldEarthResistance);

	UPROPERTY(BlueprintReadOnly, Category = "ElementalAttributes", ReplicatedUsing = OnRep_WaterResistance)
	FGameplayAttributeData WaterResistance;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, WaterResistance);
	UFUNCTION()
	virtual void OnRep_WaterResistance(const FGameplayAttributeData& OldWaterResistance);

	UPROPERTY(BlueprintReadOnly, Category = "ElementalAttributes", ReplicatedUsing = OnRep_LightResistance)
	FGameplayAttributeData LightResistance;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, LightResistance);
	UFUNCTION()
	virtual void OnRep_LightResistance(const FGameplayAttributeData& OldLightResistance);

	UPROPERTY(BlueprintReadOnly, Category = "ElementalAttributes", ReplicatedUsing = OnRep_DarkResistance)
	FGameplayAttributeData DarkResistance;
	ATTRIBUTE_ACCESSORS(UGlobalAttributeSet, DarkResistance);
	UFUNCTION()
	virtual void OnRep_DarkResistance(const FGameplayAttributeData& OldDarkResistance);

#pragma endregion ElementalResistances

};
