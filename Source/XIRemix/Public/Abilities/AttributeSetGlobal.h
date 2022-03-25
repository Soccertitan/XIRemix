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

#pragma region MetaAttributes

	/* 
	This regions meta attributes are used by the different exec calculations which modify the corresponding attributes.
	Temporary value that only exists on the Server. Not replicated.
	*/

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData DamageHP;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, DamageHP)

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData DamageMP;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, DamageMP)

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData DamageTP;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, DamageTP)

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData RecoverHP;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, RecoverHP)

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData RecoverMP;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, RecoverMP)

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData RecoverTP;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, RecoverTP)

#pragma endregion MetaAttributes

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
	
#pragma region PhysicalSubAttributes //Defines Attack, Accuracy, Defense, Crits

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

#pragma region MagicSubAttributes //Defines Magic Attack, Accuracy, Evasion, and Crits

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

#pragma region CombatSkills

//**
// Melee Skills
//**
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_Axe)
	FGameplayAttributeData Axe;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Axe);
	UFUNCTION()
	virtual void OnRep_Axe(const FGameplayAttributeData& OldAxe);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_AxeMax)
	FGameplayAttributeData AxeMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, AxeMax);
	UFUNCTION()
	virtual void OnRep_AxeMax(const FGameplayAttributeData& OldAxeMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_GreatAxe)
	FGameplayAttributeData GreatAxe;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, GreatAxe);
	UFUNCTION()
	virtual void OnRep_GreatAxe(const FGameplayAttributeData& OldGreatAxe);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_GreatAxeMax)
	FGameplayAttributeData GreatAxeMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, GreatAxeMax);
	UFUNCTION()
	virtual void OnRep_GreatAxeMax(const FGameplayAttributeData& OldGreatAxeMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_Club)
	FGameplayAttributeData Club;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Club);
	UFUNCTION()
	virtual void OnRep_Club(const FGameplayAttributeData& OldClub);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_ClubMax)
	FGameplayAttributeData ClubMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, ClubMax);
	UFUNCTION()
	virtual void OnRep_ClubMax(const FGameplayAttributeData& OldClubMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_Dagger)
	FGameplayAttributeData Dagger;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Dagger);
	UFUNCTION()
	virtual void OnRep_Dagger(const FGameplayAttributeData& OldDagger);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_DaggerMax)
	FGameplayAttributeData DaggerMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, DaggerMax);
	UFUNCTION()
	virtual void OnRep_DaggerMax(const FGameplayAttributeData& OldDaggerMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_HandToHand)
	FGameplayAttributeData HandToHand;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, HandToHand);
	UFUNCTION()
	virtual void OnRep_HandToHand(const FGameplayAttributeData& OldHandToHand);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_HandToHandMax)
	FGameplayAttributeData HandToHandMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, HandToHandMax);
	UFUNCTION()
	virtual void OnRep_HandToHandMax(const FGameplayAttributeData& OldHandToHandMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_Katana)
	FGameplayAttributeData Katana;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Katana);
	UFUNCTION()
	virtual void OnRep_Katana(const FGameplayAttributeData& OldKatana);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_KatanaMax)
	FGameplayAttributeData KatanaMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, KatanaMax);
	UFUNCTION()
	virtual void OnRep_KatanaMax(const FGameplayAttributeData& OldKatanaMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_GreatKatana)
	FGameplayAttributeData GreatKatana;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, GreatKatana);
	UFUNCTION()
	virtual void OnRep_GreatKatana(const FGameplayAttributeData& OldGreatKatana);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_GreatKatanaMax)
	FGameplayAttributeData GreatKatanaMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, GreatKatanaMax);
	UFUNCTION()
	virtual void OnRep_GreatKatanaMax(const FGameplayAttributeData& OldGreatKatanaMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_Polearm)
	FGameplayAttributeData Polearm;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Polearm);
	UFUNCTION()
	virtual void OnRep_Polearm(const FGameplayAttributeData& OldPolearm);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_PolearmMax)
	FGameplayAttributeData PolearmMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, PolearmMax);
	UFUNCTION()
	virtual void OnRep_PolearmMax(const FGameplayAttributeData& OldPolearmMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_Scythe)
	FGameplayAttributeData Scythe;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Scythe);
	UFUNCTION()
	virtual void OnRep_Scythe(const FGameplayAttributeData& OldScythe);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_ScytheMax)
	FGameplayAttributeData ScytheMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, ScytheMax);
	UFUNCTION()
	virtual void OnRep_ScytheMax(const FGameplayAttributeData& OldScytheMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_Staff)
	FGameplayAttributeData Staff;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Staff);
	UFUNCTION()
	virtual void OnRep_Staff(const FGameplayAttributeData& OldStaff);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_StaffMax)
	FGameplayAttributeData StaffMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, StaffMax);
	UFUNCTION()
	virtual void OnRep_StaffMax(const FGameplayAttributeData& OldStaffMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_Sword)
	FGameplayAttributeData Sword;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Sword);
	UFUNCTION()
	virtual void OnRep_Sword(const FGameplayAttributeData& OldSword);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_SwordMax)
	FGameplayAttributeData SwordMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, SwordMax);
	UFUNCTION()
	virtual void OnRep_SwordMax(const FGameplayAttributeData& OldSwordMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_GreatSword)
	FGameplayAttributeData GreatSword;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, GreatSword);
	UFUNCTION()
	virtual void OnRep_GreatSword(const FGameplayAttributeData& OldGreatSword);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_GreatSwordMax)
	FGameplayAttributeData GreatSwordMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, GreatSwordMax);
	UFUNCTION()
	virtual void OnRep_GreatSwordMax(const FGameplayAttributeData& OldGreatSwordMax);

	//**
	//Ranged Skills
	//**

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Range", ReplicatedUsing = OnRep_Archery)
	FGameplayAttributeData Archery;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Archery);
	UFUNCTION()
	virtual void OnRep_Archery(const FGameplayAttributeData& OldArchery);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Range", ReplicatedUsing = OnRep_ArcheryMax)
	FGameplayAttributeData ArcheryMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, ArcheryMax);
	UFUNCTION()
	virtual void OnRep_ArcheryMax(const FGameplayAttributeData& OldArcheryMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Range", ReplicatedUsing = OnRep_Marksmanship)
	FGameplayAttributeData Marksmanship;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Marksmanship);
	UFUNCTION()
	virtual void OnRep_Marksmanship(const FGameplayAttributeData& OldMarksmanship);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Range", ReplicatedUsing = OnRep_MarksmanshipMax)
	FGameplayAttributeData MarksmanshipMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, MarksmanshipMax);
	UFUNCTION()
	virtual void OnRep_MarksmanshipMax(const FGameplayAttributeData& OldMarksmanshipMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Range", ReplicatedUsing = OnRep_Throwing)
	FGameplayAttributeData Throwing;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Throwing);
	UFUNCTION()
	virtual void OnRep_Throwing(const FGameplayAttributeData& OldThrowing);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Range", ReplicatedUsing = OnRep_ThrowingMax)
	FGameplayAttributeData ThrowingMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, ThrowingMax);
	UFUNCTION()
	virtual void OnRep_ThrowingMax(const FGameplayAttributeData& OldThrowingMax);

	//**
	// Defensive Skills
	//**

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Defense", ReplicatedUsing = OnRep_Evasion)
	FGameplayAttributeData Evasion;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Evasion);
	UFUNCTION()
	virtual void OnRep_Evasion(const FGameplayAttributeData& OldEvasion);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Defense", ReplicatedUsing = OnRep_EvasionMax)
	FGameplayAttributeData EvasionMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, EvasionMax);
	UFUNCTION()
	virtual void OnRep_EvasionMax(const FGameplayAttributeData& OldEvasionMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Defense", ReplicatedUsing = OnRep_Guard)
	FGameplayAttributeData Guard;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Guard);
	UFUNCTION()
	virtual void OnRep_Guard(const FGameplayAttributeData& OldGuard);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Defense", ReplicatedUsing = OnRep_GuardMax)
	FGameplayAttributeData GuardMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, GuardMax);
	UFUNCTION()
	virtual void OnRep_GuardMax(const FGameplayAttributeData& OldGuardMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Defense", ReplicatedUsing = OnRep_Parry)
	FGameplayAttributeData Parry;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Parry);
	UFUNCTION()
	virtual void OnRep_Parry(const FGameplayAttributeData& OldParry);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Defense", ReplicatedUsing = OnRep_ParryMax)
	FGameplayAttributeData ParryMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, ParryMax);
	UFUNCTION()
	virtual void OnRep_ParryMax(const FGameplayAttributeData& OldParryMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Defense", ReplicatedUsing = OnRep_Shield)
	FGameplayAttributeData Shield;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Shield);
	UFUNCTION()
	virtual void OnRep_Shield(const FGameplayAttributeData& OldShield);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Defense", ReplicatedUsing = OnRep_ShieldMax)
	FGameplayAttributeData ShieldMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, ShieldMax);
	UFUNCTION()
	virtual void OnRep_ShieldMax(const FGameplayAttributeData& OldShieldMax);

	//**
	//Special Skills
	//**

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_Blue)
	FGameplayAttributeData Blue;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Blue);
	UFUNCTION()
	virtual void OnRep_Blue(const FGameplayAttributeData& OldBlue);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_BlueMax)
	FGameplayAttributeData BlueMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, BlueMax);
	UFUNCTION()
	virtual void OnRep_BlueMax(const FGameplayAttributeData& OldBlueMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_Dark)
	FGameplayAttributeData Dark;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Dark);
	UFUNCTION()
	virtual void OnRep_Dark(const FGameplayAttributeData& OldDark);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_DarkMax)
	FGameplayAttributeData DarkMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, DarkMax);
	UFUNCTION()
	virtual void OnRep_DarkMax(const FGameplayAttributeData& OldDarkMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_Divine)
	FGameplayAttributeData Divine;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Divine);
	UFUNCTION()
	virtual void OnRep_Divine(const FGameplayAttributeData& OldDivine);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_DivineMax)
	FGameplayAttributeData DivineMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, DivineMax);
	UFUNCTION()
	virtual void OnRep_DivineMax(const FGameplayAttributeData& OldDivineMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_Elemental)
	FGameplayAttributeData Elemental;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Elemental);
	UFUNCTION()
	virtual void OnRep_Elemental(const FGameplayAttributeData& OldElemental);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_ElementalMax)
	FGameplayAttributeData ElementalMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, ElementalMax);
	UFUNCTION()
	virtual void OnRep_ElementalMax(const FGameplayAttributeData& OldElementalMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_Enfeebling)
	FGameplayAttributeData Enfeebling;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Enfeebling);
	UFUNCTION()
	virtual void OnRep_Enfeebling(const FGameplayAttributeData& OldEnfeebling);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_EnfeeblingMax)
	FGameplayAttributeData EnfeeblingMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, EnfeeblingMax);
	UFUNCTION()
	virtual void OnRep_EnfeeblingMax(const FGameplayAttributeData& OldEnfeeblingMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_Enhancing)
	FGameplayAttributeData Enhancing;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Enhancing);
	UFUNCTION()
	virtual void OnRep_Enhancing(const FGameplayAttributeData& OldEnhancing);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_EnhancingMax)
	FGameplayAttributeData EnhancingMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, EnhancingMax);
	UFUNCTION()
	virtual void OnRep_EnhancingMax(const FGameplayAttributeData& OldEnhancingMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_Healing)
	FGameplayAttributeData Healing;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Healing);
	UFUNCTION()
	virtual void OnRep_Healing(const FGameplayAttributeData& OldHealing);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_HealingMax)
	FGameplayAttributeData HealingMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, HealingMax);
	UFUNCTION()
	virtual void OnRep_HealingMax(const FGameplayAttributeData& OldHealingMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_Summoning)
	FGameplayAttributeData Summoning;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Summoning);
	UFUNCTION()
	virtual void OnRep_Summoning(const FGameplayAttributeData& OldSummoning);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_SummoningMax)
	FGameplayAttributeData SummoningMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, SummoningMax);
	UFUNCTION()
	virtual void OnRep_SummoningMax(const FGameplayAttributeData& OldSummoningMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_Ninjutsu)
	FGameplayAttributeData Ninjutsu;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Ninjutsu);
	UFUNCTION()
	virtual void OnRep_Ninjutsu(const FGameplayAttributeData& OldNinjutsu);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_NinjutsuMax)
	FGameplayAttributeData NinjutsuMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, NinjutsuMax);
	UFUNCTION()
	virtual void OnRep_NinjutsuMax(const FGameplayAttributeData& OldNinjutsuMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_Singing)
	FGameplayAttributeData Singing;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Singing);
	UFUNCTION()
	virtual void OnRep_Singing(const FGameplayAttributeData& OldSinging);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_SingingMax)
	FGameplayAttributeData SingingMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, SingingMax);
	UFUNCTION()
	virtual void OnRep_SingingMax(const FGameplayAttributeData& OldSingingMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_String)
	FGameplayAttributeData String;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, String);
	UFUNCTION()
	virtual void OnRep_String(const FGameplayAttributeData& OldString);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_StringMax)
	FGameplayAttributeData StringMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, StringMax);
	UFUNCTION()
	virtual void OnRep_StringMax(const FGameplayAttributeData& OldStringMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_Wind)
	FGameplayAttributeData Wind;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Wind);
	UFUNCTION()
	virtual void OnRep_Wind(const FGameplayAttributeData& OldWind);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_WindMax)
	FGameplayAttributeData WindMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, WindMax);
	UFUNCTION()
	virtual void OnRep_WindMax(const FGameplayAttributeData& OldWindMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_Geomancy)
	FGameplayAttributeData Geomancy;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Geomancy);
	UFUNCTION()
	virtual void OnRep_Geomancy(const FGameplayAttributeData& OldGeomancy);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_GeomancyMax)
	FGameplayAttributeData GeomancyMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, GeomancyMax);
	UFUNCTION()
	virtual void OnRep_GeomancyMax(const FGameplayAttributeData& OldGeomancyMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_Handbell)
	FGameplayAttributeData Handbell;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Handbell);
	UFUNCTION()
	virtual void OnRep_Handbell(const FGameplayAttributeData& OldHandbell);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_HandbellMax)
	FGameplayAttributeData HandbellMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, HandbellMax);
	UFUNCTION()
	virtual void OnRep_HandbellMax(const FGameplayAttributeData& OldHandbellMax);

#pragma endregion CombatSkills

};
