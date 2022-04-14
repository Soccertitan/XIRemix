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

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

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

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData BluntResistance;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, BluntResistance)

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData PierceResistance;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, PierceResistance)

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData SlashResistance;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, SlashResistance)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Physical", ReplicatedUsing = OnRep_Evasion)
	FGameplayAttributeData Evasion;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, Evasion);
	UFUNCTION()
	virtual void OnRep_Evasion(const FGameplayAttributeData& OldEvasion);

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
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_AxeSkill)
	FGameplayAttributeData AxeSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, AxeSkill);
	UFUNCTION()
	virtual void OnRep_AxeSkill(const FGameplayAttributeData& OldAxeSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_AxeSkillMax)
	FGameplayAttributeData AxeSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, AxeSkillMax);
	UFUNCTION()
	virtual void OnRep_AxeSkillMax(const FGameplayAttributeData& OldAxeSkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_GreatAxeSkill)
	FGameplayAttributeData GreatAxeSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, GreatAxeSkill);
	UFUNCTION()
	virtual void OnRep_GreatAxeSkill(const FGameplayAttributeData& OldGreatAxeSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_GreatAxeSkillMax)
	FGameplayAttributeData GreatAxeSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, GreatAxeSkillMax);
	UFUNCTION()
	virtual void OnRep_GreatAxeSkillMax(const FGameplayAttributeData& OldGreatAxeSkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_ClubSkill)
	FGameplayAttributeData ClubSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, ClubSkill);
	UFUNCTION()
	virtual void OnRep_ClubSkill(const FGameplayAttributeData& OldClubSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_ClubSkillMax)
	FGameplayAttributeData ClubSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, ClubSkillMax);
	UFUNCTION()
	virtual void OnRep_ClubSkillMax(const FGameplayAttributeData& OldClubSkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_DaggerSkill)
	FGameplayAttributeData DaggerSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, DaggerSkill);
	UFUNCTION()
	virtual void OnRep_DaggerSkill(const FGameplayAttributeData& OldDaggerSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_DaggerSkillMax)
	FGameplayAttributeData DaggerSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, DaggerSkillMax);
	UFUNCTION()
	virtual void OnRep_DaggerSkillMax(const FGameplayAttributeData& OldDaggerSkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_HandToHandSkill)
	FGameplayAttributeData HandToHandSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, HandToHandSkill);
	UFUNCTION()
	virtual void OnRep_HandToHandSkill(const FGameplayAttributeData& OldHandToHandSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_HandToHandSkillMax)
	FGameplayAttributeData HandToHandSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, HandToHandSkillMax);
	UFUNCTION()
	virtual void OnRep_HandToHandSkillMax(const FGameplayAttributeData& OldHandToHandSkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_KatanaSkill)
	FGameplayAttributeData KatanaSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, KatanaSkill);
	UFUNCTION()
	virtual void OnRep_KatanaSkill(const FGameplayAttributeData& OldKatanaSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_KatanaSkillMax)
	FGameplayAttributeData KatanaSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, KatanaSkillMax);
	UFUNCTION()
	virtual void OnRep_KatanaSkillMax(const FGameplayAttributeData& OldKatanaSkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_GreatKatanaSkill)
	FGameplayAttributeData GreatKatanaSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, GreatKatanaSkill);
	UFUNCTION()
	virtual void OnRep_GreatKatanaSkill(const FGameplayAttributeData& OldGreatKatanaSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_GreatKatanaSkillMax)
	FGameplayAttributeData GreatKatanaSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, GreatKatanaSkillMax);
	UFUNCTION()
	virtual void OnRep_GreatKatanaSkillMax(const FGameplayAttributeData& OldGreatKatanaSkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_PolearmSkill)
	FGameplayAttributeData PolearmSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, PolearmSkill);
	UFUNCTION()
	virtual void OnRep_PolearmSkill(const FGameplayAttributeData& OldPolearmSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_PolearmSkillMax)
	FGameplayAttributeData PolearmSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, PolearmSkillMax);
	UFUNCTION()
	virtual void OnRep_PolearmSkillMax(const FGameplayAttributeData& OldPolearmSkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_ScytheSkill)
	FGameplayAttributeData ScytheSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, ScytheSkill);
	UFUNCTION()
	virtual void OnRep_ScytheSkill(const FGameplayAttributeData& OldScytheSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_ScytheSkillMax)
	FGameplayAttributeData ScytheSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, ScytheSkillMax);
	UFUNCTION()
	virtual void OnRep_ScytheSkillMax(const FGameplayAttributeData& OldScytheSkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_StaffSkill)
	FGameplayAttributeData StaffSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, StaffSkill);
	UFUNCTION()
	virtual void OnRep_StaffSkill(const FGameplayAttributeData& OldStaffSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_StaffSkillMax)
	FGameplayAttributeData StaffSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, StaffSkillMax);
	UFUNCTION()
	virtual void OnRep_StaffSkillMax(const FGameplayAttributeData& OldStaffSkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_SwordSkill)
	FGameplayAttributeData SwordSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, SwordSkill);
	UFUNCTION()
	virtual void OnRep_SwordSkill(const FGameplayAttributeData& OldSwordSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_SwordSkillMax)
	FGameplayAttributeData SwordSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, SwordSkillMax);
	UFUNCTION()
	virtual void OnRep_SwordSkillMax(const FGameplayAttributeData& OldSwordSkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_GreatSwordSkill)
	FGameplayAttributeData GreatSwordSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, GreatSwordSkill);
	UFUNCTION()
	virtual void OnRep_GreatSwordSkill(const FGameplayAttributeData& OldGreatSwordSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Melee", ReplicatedUsing = OnRep_GreatSwordSkillMax)
	FGameplayAttributeData GreatSwordSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, GreatSwordSkillMax);
	UFUNCTION()
	virtual void OnRep_GreatSwordSkillMax(const FGameplayAttributeData& OldGreatSwordSkillMax);

	//**
	//Ranged Skills
	//**

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Range", ReplicatedUsing = OnRep_ArcherySkill)
	FGameplayAttributeData ArcherySkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, ArcherySkill);
	UFUNCTION()
	virtual void OnRep_ArcherySkill(const FGameplayAttributeData& OldArcherySkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Range", ReplicatedUsing = OnRep_ArcherySkillMax)
	FGameplayAttributeData ArcherySkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, ArcherySkillMax);
	UFUNCTION()
	virtual void OnRep_ArcherySkillMax(const FGameplayAttributeData& OldArcherySkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Range", ReplicatedUsing = OnRep_MarksmanshipSkill)
	FGameplayAttributeData MarksmanshipSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, MarksmanshipSkill);
	UFUNCTION()
	virtual void OnRep_MarksmanshipSkill(const FGameplayAttributeData& OldMarksmanshipSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Range", ReplicatedUsing = OnRep_MarksmanshipSkillMax)
	FGameplayAttributeData MarksmanshipSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, MarksmanshipSkillMax);
	UFUNCTION()
	virtual void OnRep_MarksmanshipSkillMax(const FGameplayAttributeData& OldMarksmanshipSkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Range", ReplicatedUsing = OnRep_ThrowingSkill)
	FGameplayAttributeData ThrowingSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, ThrowingSkill);
	UFUNCTION()
	virtual void OnRep_ThrowingSkill(const FGameplayAttributeData& OldThrowingSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Range", ReplicatedUsing = OnRep_ThrowingSkillMax)
	FGameplayAttributeData ThrowingSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, ThrowingSkillMax);
	UFUNCTION()
	virtual void OnRep_ThrowingSkillMax(const FGameplayAttributeData& OldThrowingSkillMax);

	//**
	// Defensive Skills
	//**

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Defense", ReplicatedUsing = OnRep_EvasionSkill)
	FGameplayAttributeData EvasionSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, EvasionSkill);
	UFUNCTION()
	virtual void OnRep_EvasionSkill(const FGameplayAttributeData& OldEvasionSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Defense", ReplicatedUsing = OnRep_EvasionSkillMax)
	FGameplayAttributeData EvasionSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, EvasionSkillMax);
	UFUNCTION()
	virtual void OnRep_EvasionSkillMax(const FGameplayAttributeData& OldEvasionSkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Defense", ReplicatedUsing = OnRep_GuardSkill)
	FGameplayAttributeData GuardSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, GuardSkill);
	UFUNCTION()
	virtual void OnRep_GuardSkill(const FGameplayAttributeData& OldGuardSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Defense", ReplicatedUsing = OnRep_GuardSkillMax)
	FGameplayAttributeData GuardSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, GuardSkillMax);
	UFUNCTION()
	virtual void OnRep_GuardSkillMax(const FGameplayAttributeData& OldGuardSkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Defense", ReplicatedUsing = OnRep_ParrySkill)
	FGameplayAttributeData ParrySkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, ParrySkill);
	UFUNCTION()
	virtual void OnRep_ParrySkill(const FGameplayAttributeData& OldParrySkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Defense", ReplicatedUsing = OnRep_ParrySkillMax)
	FGameplayAttributeData ParrySkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, ParrySkillMax);
	UFUNCTION()
	virtual void OnRep_ParrySkillMax(const FGameplayAttributeData& OldParrySkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Defense", ReplicatedUsing = OnRep_ShieldSkill)
	FGameplayAttributeData ShieldSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, ShieldSkill);
	UFUNCTION()
	virtual void OnRep_ShieldSkill(const FGameplayAttributeData& OldShieldSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Defense", ReplicatedUsing = OnRep_ShieldSkillMax)
	FGameplayAttributeData ShieldSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, ShieldSkillMax);
	UFUNCTION()
	virtual void OnRep_ShieldSkillMax(const FGameplayAttributeData& OldShieldSkillMax);

	//**
	//Special Skills
	//**

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_BlueMagicSkill)
	FGameplayAttributeData BlueMagicSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, BlueMagicSkill);
	UFUNCTION()
	virtual void OnRep_BlueMagicSkill(const FGameplayAttributeData& OldBlueMagicSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_BlueMagicSkillMax)
	FGameplayAttributeData BlueMagicSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, BlueMagicSkillMax);
	UFUNCTION()
	virtual void OnRep_BlueMagicSkillMax(const FGameplayAttributeData& OldBlueMagicSkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_DarkMagicSkill)
	FGameplayAttributeData DarkMagicSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, DarkMagicSkill);
	UFUNCTION()
	virtual void OnRep_DarkMagicSkill(const FGameplayAttributeData& OldDarkMagicSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_DarkMagicSkillMax)
	FGameplayAttributeData DarkMagicSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, DarkMagicSkillMax);
	UFUNCTION()
	virtual void OnRep_DarkMagicSkillMax(const FGameplayAttributeData& OldDarkMagicSkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_DivineMagicSkill)
	FGameplayAttributeData DivineMagicSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, DivineMagicSkill);
	UFUNCTION()
	virtual void OnRep_DivineMagicSkill(const FGameplayAttributeData& OldDivineMagicSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_DivineMagicSkillMax)
	FGameplayAttributeData DivineMagicSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, DivineMagicSkillMax);
	UFUNCTION()
	virtual void OnRep_DivineMagicSkillMax(const FGameplayAttributeData& OldDivineMagicSkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_ElementalMagicSkill)
	FGameplayAttributeData ElementalMagicSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, ElementalMagicSkill);
	UFUNCTION()
	virtual void OnRep_ElementalMagicSkill(const FGameplayAttributeData& OldElementalMagicSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_ElementalMagicSkillMax)
	FGameplayAttributeData ElementalMagicSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, ElementalMagicSkillMax);
	UFUNCTION()
	virtual void OnRep_ElementalMagicSkillMax(const FGameplayAttributeData& OldElementalMagicSkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_EnfeeblingMagicSkill)
	FGameplayAttributeData EnfeeblingMagicSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, EnfeeblingMagicSkill);
	UFUNCTION()
	virtual void OnRep_EnfeeblingMagicSkill(const FGameplayAttributeData& OldEnfeeblingMagicSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_EnfeeblingMagicSkillMax)
	FGameplayAttributeData EnfeeblingMagicSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, EnfeeblingMagicSkillMax);
	UFUNCTION()
	virtual void OnRep_EnfeeblingMagicSkillMax(const FGameplayAttributeData& OldEnfeeblingMagicSkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_EnhancingMagicSkill)
	FGameplayAttributeData EnhancingMagicSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, EnhancingMagicSkill);
	UFUNCTION()
	virtual void OnRep_EnhancingMagicSkill(const FGameplayAttributeData& OldEnhancingMagicSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_EnhancingMagicSkillMax)
	FGameplayAttributeData EnhancingMagicSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, EnhancingMagicSkillMax);
	UFUNCTION()
	virtual void OnRep_EnhancingMagicSkillMax(const FGameplayAttributeData& OldEnhancingMagicSkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_HealingMagicSkill)
	FGameplayAttributeData HealingMagicSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, HealingMagicSkill);
	UFUNCTION()
	virtual void OnRep_HealingMagicSkill(const FGameplayAttributeData& OldHealingMagicSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_HealingMagicSkillMax)
	FGameplayAttributeData HealingMagicSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, HealingMagicSkillMax);
	UFUNCTION()
	virtual void OnRep_HealingMagicSkillMax(const FGameplayAttributeData& OldHealingMagicSkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_SummoningMagicSkill)
	FGameplayAttributeData SummoningMagicSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, SummoningMagicSkill);
	UFUNCTION()
	virtual void OnRep_SummoningMagicSkill(const FGameplayAttributeData& OldSummoningMagicSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_SummoningMagicSkillMax)
	FGameplayAttributeData SummoningMagicSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, SummoningMagicSkillMax);
	UFUNCTION()
	virtual void OnRep_SummoningMagicSkillMax(const FGameplayAttributeData& OldSummoningMagicSkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_NinjutsuSkill)
	FGameplayAttributeData NinjutsuSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, NinjutsuSkill);
	UFUNCTION()
	virtual void OnRep_NinjutsuSkill(const FGameplayAttributeData& OldNinjutsuSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_NinjutsuSkillMax)
	FGameplayAttributeData NinjutsuSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, NinjutsuSkillMax);
	UFUNCTION()
	virtual void OnRep_NinjutsuSkillMax(const FGameplayAttributeData& OldNinjutsuSkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_SingingSkill)
	FGameplayAttributeData SingingSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, SingingSkill);
	UFUNCTION()
	virtual void OnRep_SingingSkill(const FGameplayAttributeData& OldSingingSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_SingingSkillMax)
	FGameplayAttributeData SingingSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, SingingSkillMax);
	UFUNCTION()
	virtual void OnRep_SingingSkillMax(const FGameplayAttributeData& OldSingingSkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_StringSkill)
	FGameplayAttributeData StringSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, StringSkill);
	UFUNCTION()
	virtual void OnRep_StringSkill(const FGameplayAttributeData& OldStringSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_StringSkillMax)
	FGameplayAttributeData StringSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, StringSkillMax);
	UFUNCTION()
	virtual void OnRep_StringSkillMax(const FGameplayAttributeData& OldStringSkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_WindSkill)
	FGameplayAttributeData WindSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, WindSkill);
	UFUNCTION()
	virtual void OnRep_WindSkill(const FGameplayAttributeData& OldWindSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_WindSkillMax)
	FGameplayAttributeData WindSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, WindSkillMax);
	UFUNCTION()
	virtual void OnRep_WindSkillMax(const FGameplayAttributeData& OldWindSkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_GeomancySkill)
	FGameplayAttributeData GeomancySkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, GeomancySkill);
	UFUNCTION()
	virtual void OnRep_GeomancySkill(const FGameplayAttributeData& OldGeomancySkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_GeomancySkillMax)
	FGameplayAttributeData GeomancySkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, GeomancySkillMax);
	UFUNCTION()
	virtual void OnRep_GeomancySkillMax(const FGameplayAttributeData& OldGeomancySkillMax);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_HandbellSkill)
	FGameplayAttributeData HandbellSkill;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, HandbellSkill);
	UFUNCTION()
	virtual void OnRep_HandbellSkill(const FGameplayAttributeData& OldHandbellSkill);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Skills|Special", ReplicatedUsing = OnRep_HandbellSkillMax)
	FGameplayAttributeData HandbellSkillMax;
	ATTRIBUTE_ACCESSORS(UAttributeSetGlobal, HandbellSkillMax);
	UFUNCTION()
	virtual void OnRep_HandbellSkillMax(const FGameplayAttributeData& OldHandbellSkillMax);

#pragma endregion CombatSkills

};
