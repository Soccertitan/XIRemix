// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AttributeSetGlobal.generated.h"

// Macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class XIREMIX_API UAttributeSetGlobal : public UAttributeSet
{
	GENERATED_BODY()

public:

	UAttributeSetGlobal();

	// AttributeSet Overrides
	// virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

#pragma region ResourceAttributes // Defines HP, MP, TP resources

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Resource", ReplicatedUsing = OnRep_HitPoints)
	FGameplayAttributeData HitPoints;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, HitPoints);
	UFUNCTION()
	virtual void OnRep_HitPoints(const FGameplayAttributeData& OldHitPoints);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Resource", ReplicatedUsing = OnRep_HitPointsMax)
	FGameplayAttributeData HitPointsMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, HitPointsMax);
	UFUNCTION()
	virtual void OnRep_HitPointsMax(const FGameplayAttributeData& OldHitPointsMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Resource", ReplicatedUsing = OnRep_ManaPoints)
	FGameplayAttributeData ManaPoints;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, ManaPoints);
	UFUNCTION()
	virtual void OnRep_ManaPoints(const FGameplayAttributeData& OldManaPoints);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Resource", ReplicatedUsing = OnRep_ManaPointsMax)
	FGameplayAttributeData ManaPointsMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, ManaPointsMax);
	UFUNCTION()
	virtual void OnRep_ManaPointsMax(const FGameplayAttributeData& OldManaPointsMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Resource", ReplicatedUsing = OnRep_TacticalPoints)
	FGameplayAttributeData TacticalPoints;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, TacticalPoints);
	UFUNCTION()
	virtual void OnRep_TacticalPoints(const FGameplayAttributeData& OldTacticalPoints);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Resource", ReplicatedUsing = OnRep_TacticalPointsMax)
	FGameplayAttributeData TacticalPointsMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, TacticalPointsMax);
	UFUNCTION()
	virtual void OnRep_TacticalPointsMax(const FGameplayAttributeData& OldTacticalPointsMax);

#pragma endregion ResourceAttributes

#pragma region MainAttributes //Defines the main attributes Str, Dex, Agi, Vit, Int, Mnd, Chr

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Basic", ReplicatedUsing = OnRep_Strength)
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Strength);
	UFUNCTION()
	virtual void OnRep_Strength(const FGameplayAttributeData& OldStrength);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Basic", ReplicatedUsing = OnRep_Dexterity)
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Dexterity);
	UFUNCTION()
	virtual void OnRep_Dexterity(const FGameplayAttributeData& OldDexterity);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Basic", ReplicatedUsing = OnRep_Vitality)
	FGameplayAttributeData Vitality;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Vitality);
	UFUNCTION()
	virtual void OnRep_Vitality(const FGameplayAttributeData& OldVitality);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Basic", ReplicatedUsing = OnRep_Agility)
	FGameplayAttributeData Agility;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Agility);
	UFUNCTION()
	virtual void OnRep_Agility(const FGameplayAttributeData& OldAgility);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Basic", ReplicatedUsing = OnRep_Intelligence)
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Intelligence);
	UFUNCTION()
	virtual void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Basic", ReplicatedUsing = OnRep_Mind)
	FGameplayAttributeData Mind;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Mind);
	UFUNCTION()
	virtual void OnRep_Mind(const FGameplayAttributeData& OldMind);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Basic", ReplicatedUsing = OnRep_Charisma)
	FGameplayAttributeData Charisma;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Charisma);
	UFUNCTION()
	virtual void OnRep_Charisma(const FGameplayAttributeData& OldCharisma);

#pragma endregion MainAttributes
	
#pragma region PhysicalSubAttributes //Defines Attack, Accuracy, Defense, Evasion, Crits, and Movement

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Physical", ReplicatedUsing = OnRep_Attack)
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Attack);
	UFUNCTION()
	virtual void OnRep_Attack(const FGameplayAttributeData& OldAttack);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Physical", ReplicatedUsing = OnRep_RangedAttack)
	FGameplayAttributeData RangedAttack;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, RangedAttack);
	UFUNCTION()
	virtual void OnRep_RangedAttack(const FGameplayAttributeData& OldRangedAttack);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Physical", ReplicatedUsing = OnRep_Defense)
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Defense);
	UFUNCTION()
	virtual void OnRep_Defense(const FGameplayAttributeData& OldDefense);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Physical", ReplicatedUsing = OnRep_Accuracy)
	FGameplayAttributeData Accuracy;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Accuracy);
	UFUNCTION()
	virtual void OnRep_Accuracy(const FGameplayAttributeData& OldAccuracy);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Physical", ReplicatedUsing = OnRep_RangedAccuracy)
	FGameplayAttributeData RangedAccuracy;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, RangedAccuracy);
	UFUNCTION()
	virtual void OnRep_RangedAccuracy(const FGameplayAttributeData& OldRangedAccuracy);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Physical", ReplicatedUsing = OnRep_Evasion)
	FGameplayAttributeData Evasion;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Evasion);
	UFUNCTION()
	virtual void OnRep_Evasion(const FGameplayAttributeData& OldEvasion);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Physical", ReplicatedUsing = OnRep_CriticalHitRate)
	FGameplayAttributeData CriticalHitRate;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, CriticalHitRate);
	UFUNCTION()
	virtual void OnRep_CriticalHitRate(const FGameplayAttributeData& OldCriticalHitRate);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Physical", ReplicatedUsing = OnRep_CriticalHitBonus)
	FGameplayAttributeData CriticalHitBonus;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, CriticalHitBonus);
	UFUNCTION()
	virtual void OnRep_CriticalHitBonus(const FGameplayAttributeData& OldCriticalHitBonus);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Physical", ReplicatedUsing = OnRep_RangedCriticalHitRate)
	FGameplayAttributeData RangedCriticalHitRate;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, RangedCriticalHitRate);
	UFUNCTION()
	virtual void OnRep_RangedCriticalHitRate(const FGameplayAttributeData& OldRangedCriticalHitRate);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Physical", ReplicatedUsing = OnRep_RangedCriticalHitBonus)
	FGameplayAttributeData RangedCriticalHitBonus;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, RangedCriticalHitBonus);
	UFUNCTION()
	virtual void OnRep_RangedCriticalHitBonus(const FGameplayAttributeData& OldRangedCriticalHitBonus);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Physical", ReplicatedUsing = OnRep_AttackDelay)
	FGameplayAttributeData AttackDelay;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, AttackDelay);
	UFUNCTION()
	virtual void OnRep_AttackDelay(const FGameplayAttributeData& OldAttackDelay);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Physical", ReplicatedUsing = OnRep_AttackSpeed)
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, AttackSpeed);
	UFUNCTION()
	virtual void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Physical", ReplicatedUsing = OnRep_RangedAttackDelay)
	FGameplayAttributeData RangedAttackDelay;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, RangedAttackDelay);
	UFUNCTION()
	virtual void OnRep_RangedAttackDelay(const FGameplayAttributeData& OldRangedAttackDelay);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Physical", ReplicatedUsing = OnRep_RangedAttackSpeed)
	FGameplayAttributeData RangedAttackSpeed;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, RangedAttackSpeed);
	UFUNCTION()
	virtual void OnRep_RangedAttackSpeed(const FGameplayAttributeData& OldRangedAttackSpeed);

#pragma endregion MeleeSubAttributes

#pragma region MagicSubAttributes //Defines Magic Attack, Accuracy, Defense, Evasion, and Crits

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Magical", ReplicatedUsing = OnRep_MagicAttack)
	FGameplayAttributeData MagicAttack;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, MagicAttack);
	UFUNCTION()
	virtual void OnRep_MagicAttack(const FGameplayAttributeData& OldMagicAttack);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Magical", ReplicatedUsing = OnRep_MagicAccuracy)
	FGameplayAttributeData MagicAccuracy;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, MagicAccuracy);
	UFUNCTION()
	virtual void OnRep_MagicAccuracy(const FGameplayAttributeData& OldMagicAccuracy);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Magical", ReplicatedUsing = OnRep_MagicEvasion)
	FGameplayAttributeData MagicEvasion;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, MagicEvasion);
	UFUNCTION()
	virtual void OnRep_MagicEvasion(const FGameplayAttributeData& OldMagicEvasion);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Magical", ReplicatedUsing = OnRep_MagicCriticalHitRate)
	FGameplayAttributeData MagicCriticalHitRate;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, MagicCriticalHitRate);
	UFUNCTION()
	virtual void OnRep_MagicCriticalHitRate(const FGameplayAttributeData& OldMagicCriticalHitRate);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Magical", ReplicatedUsing = OnRep_MagicCriticalHitBonus)
	FGameplayAttributeData MagicCriticalHitBonus;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, MagicCriticalHitBonus);
	UFUNCTION()
	virtual void OnRep_MagicCriticalHitBonus(const FGameplayAttributeData& OldMagicCriticalHitBonus);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Magical", ReplicatedUsing = OnRep_CastSpeed)
	FGameplayAttributeData CastSpeed;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, CastSpeed);
	UFUNCTION()
	virtual void OnRep_CastSpeed(const FGameplayAttributeData& OldCastSpeed);

#pragma endregion MagicSubAttributes

#pragma region ElementalResistances //Defines Fire, Ice, Lightning, Water, Earth, Wind, Dark, and Light Resistance

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Elemental", ReplicatedUsing = OnRep_FireResistance)
	FGameplayAttributeData FireResistance;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, FireResistance);
	UFUNCTION()
	virtual void OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Elemental", ReplicatedUsing = OnRep_IceResistance)
	FGameplayAttributeData IceResistance;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, IceResistance);
	UFUNCTION()
	virtual void OnRep_IceResistance(const FGameplayAttributeData& OldIceResistance);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Elemental", ReplicatedUsing = OnRep_WindResistance)
	FGameplayAttributeData WindResistance;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, WindResistance);
	UFUNCTION()
	virtual void OnRep_WindResistance(const FGameplayAttributeData& OldWindResistance);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Elemental", ReplicatedUsing = OnRep_LightningResistance)
	FGameplayAttributeData LightningResistance;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, LightningResistance);
	UFUNCTION()
	virtual void OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Elemental", ReplicatedUsing = OnRep_EarthResistance)
	FGameplayAttributeData EarthResistance;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, EarthResistance);
	UFUNCTION()
	virtual void OnRep_EarthResistance(const FGameplayAttributeData& OldEarthResistance);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Elemental", ReplicatedUsing = OnRep_WaterResistance)
	FGameplayAttributeData WaterResistance;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, WaterResistance);
	UFUNCTION()
	virtual void OnRep_WaterResistance(const FGameplayAttributeData& OldWaterResistance);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Elemental", ReplicatedUsing = OnRep_LightResistance)
	FGameplayAttributeData LightResistance;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, LightResistance);
	UFUNCTION()
	virtual void OnRep_LightResistance(const FGameplayAttributeData& OldLightResistance);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Elemental", ReplicatedUsing = OnRep_DarkResistance)
	FGameplayAttributeData DarkResistance;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, DarkResistance);
	UFUNCTION()
	virtual void OnRep_DarkResistance(const FGameplayAttributeData& OldDarkResistance);

#pragma endregion ElementalResistances

#pragma region ResistStatus //Defines Status resistances

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Status", ReplicatedUsing = OnRep_AmnesiaResistance)
	FGameplayAttributeData AmnesiaResistance;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, AmnesiaResistance);
	UFUNCTION()
	virtual void OnRep_AmnesiaResistance(const FGameplayAttributeData& OldAmnesiaResistance);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Status", ReplicatedUsing = OnRep_BindResistance)
	FGameplayAttributeData BindResistance;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, BindResistance);
	UFUNCTION()
	virtual void OnRep_BindResistance(const FGameplayAttributeData& OldBindResistance);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Status", ReplicatedUsing = OnRep_BlindResistance)
	FGameplayAttributeData BlindResistance;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, BlindResistance);
	UFUNCTION()
	virtual void OnRep_BlindResistance(const FGameplayAttributeData& OldBlindResistance);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Status", ReplicatedUsing = OnRep_GravityResistance)
	FGameplayAttributeData GravityResistance;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, GravityResistance);
	UFUNCTION()
	virtual void OnRep_GravityResistance(const FGameplayAttributeData& OldGravityResistance);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Status", ReplicatedUsing = OnRep_ParalyzeResistance)
	FGameplayAttributeData ParalyzeResistance;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, ParalyzeResistance);
	UFUNCTION()
	virtual void OnRep_ParalyzeResistance(const FGameplayAttributeData& OldParalyzeResistance);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Status", ReplicatedUsing = OnRep_PetrifyResistance)
	FGameplayAttributeData PetrifyResistance;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, PetrifyResistance);
	UFUNCTION()
	virtual void OnRep_PetrifyResistance(const FGameplayAttributeData& OldPetrifyResistance);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Status", ReplicatedUsing = OnRep_PoisonResistance)
	FGameplayAttributeData PoisonResistance;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, PoisonResistance);
	UFUNCTION()
	virtual void OnRep_PoisonResistance(const FGameplayAttributeData& OldPoisonResistance);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Status", ReplicatedUsing = OnRep_SilenceResistance)
	FGameplayAttributeData SilenceResistance;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, SilenceResistance);
	UFUNCTION()
	virtual void OnRep_SilenceResistance(const FGameplayAttributeData& OldSilenceResistance);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Status", ReplicatedUsing = OnRep_SleepResistance)
	FGameplayAttributeData SleepResistance;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, SleepResistance);
	UFUNCTION()
	virtual void OnRep_SleepResistance(const FGameplayAttributeData& OldSleepResistance);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Status", ReplicatedUsing = OnRep_SlowResistance)
	FGameplayAttributeData SlowResistance;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, SlowResistance);
	UFUNCTION()
	virtual void OnRep_SlowResistance(const FGameplayAttributeData& OldSlowResistance);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Status", ReplicatedUsing = OnRep_VirusResistance)
	FGameplayAttributeData VirusResistance;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, VirusResistance);
	UFUNCTION()
	virtual void OnRep_VirusResistance(const FGameplayAttributeData& OldVirusResistance);

#pragma endregion Resist Status

#pragma region OtherAttributes

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Other", ReplicatedUsing = OnRep_MoveSpeed)
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, MoveSpeed);
	UFUNCTION()
	virtual void OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed);
	
	// Affects the effectivenss of heals
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Other", ReplicatedUsing = OnRep_CurePotency)
	FGameplayAttributeData CurePotency;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, CurePotency);
	UFUNCTION()
	virtual void OnRep_CurePotency(const FGameplayAttributeData& OldCurePotency);

	// Affects the effectiveness of receiving healing
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Other", ReplicatedUsing = OnRep_CureReceivedPotency)
	FGameplayAttributeData CureReceivedPotency;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, CureReceivedPotency);
	UFUNCTION()
	virtual void OnRep_CureReceivedPotency(const FGameplayAttributeData& OldCureReceivedPotency);

	// The multiplier in damage received. 1 = default
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Other", ReplicatedUsing = OnRep_DamageResist)
	FGameplayAttributeData DamageResist;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, DamageResist);
	UFUNCTION()
	virtual void OnRep_DamageResist(const FGameplayAttributeData& OldDamageResist);

	// The multiplier in getting interrupted while casting spells. 1 = default
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Other", ReplicatedUsing = OnRep_SpellInterruption)
	FGameplayAttributeData SpellInterruption;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, SpellInterruption);
	UFUNCTION()
	virtual void OnRep_SpellInterruption(const FGameplayAttributeData& OldSpellInterruption);

#pragma endregion OtherAttributes

};
