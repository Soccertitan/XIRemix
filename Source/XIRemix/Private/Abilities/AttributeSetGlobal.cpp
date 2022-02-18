// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AttributeSetGlobal.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"
#include "Net/UnrealNetwork.h"

UAttributeSetGlobal::UAttributeSetGlobal() 
    : HitPoints(1.f)
    , HitPointsMax(1.f)
    , ManaPoints(0.f)
    , ManaPointsMax(0.f)
    , TacticalPoints(0.f)
    , TacticalPointsMax(1000.f)
{
}

void UAttributeSetGlobal::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetHitPointsAttribute())
	{
		// Handle other health changes.
		// Health loss should go through Damage.
		SetHitPoints(FMath::Clamp(GetHitPoints(), 0.0f, GetHitPointsMax()));
	}
	else if (Data.EvaluatedData.Attribute == GetManaPointsAttribute())
	{
		// Handle mana changes.
		SetManaPoints(FMath::Clamp(GetManaPoints(), 0.0f, GetManaPointsMax()));
	}
	else if (Data.EvaluatedData.Attribute == GetTacticalPointsAttribute())
	{
		// Handle TacticalPoint changes.
		SetTacticalPoints(FMath::Clamp(GetTacticalPoints(), 0.0f, GetTacticalPointsMax()));
	}
}

void UAttributeSetGlobal::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const 
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // Resource Attributes
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, HitPoints, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, HitPointsMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, ManaPoints, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, ManaPointsMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, TacticalPoints, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, TacticalPointsMax, COND_None, REPNOTIFY_Always);

    // Main Attributes
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Strength, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Dexterity, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Agility, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Vitality, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Intelligence, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Mind, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Charisma, COND_None, REPNOTIFY_Always);

    // Physical Sub Attributes
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Attack, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, RangedAttack, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Defense, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Accuracy, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, RangedAccuracy, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Evasion, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, CriticalHitRate, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, CriticalHitBonus, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, RangedCriticalHitRate, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, RangedCriticalHitBonus, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, AttackDelay, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, AttackSpeed, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, RangedAttackDelay, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, RangedAttackSpeed, COND_None, REPNOTIFY_Always);

    // Magical Sub Attributes
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, MagicAttack, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, MagicAccuracy, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, MagicEvasion, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, MagicCriticalHitRate, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, MagicCriticalHitBonus, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, CastSpeed, COND_None, REPNOTIFY_Always);

    // Elemental Resistences
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, FireResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, IceResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, WindResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, LightningResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, EarthResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, WaterResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, LightResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, DarkResistance, COND_None, REPNOTIFY_Always);

    // Resist Status
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, AmnesiaResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, BindResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, BlindResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, GravityResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, ParalyzeResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, PetrifyResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, PoisonResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, SilenceResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, SleepResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, SlowResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, VirusResistance, COND_None, REPNOTIFY_Always);

    // Other Attributes
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, MoveSpeed, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, CurePotency, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, CureReceivedPotency, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, DamageResist, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Enmity, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, SpellInterruption, COND_None, REPNOTIFY_Always);
}

#pragma region ResourceAttributesFunctions

void UAttributeSetGlobal::OnRep_HitPoints(const FGameplayAttributeData& OldHitPoints) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, HitPoints, OldHitPoints);
}

void UAttributeSetGlobal::OnRep_HitPointsMax(const FGameplayAttributeData& OldHitPointsMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, HitPointsMax, OldHitPointsMax);
}

void UAttributeSetGlobal::OnRep_ManaPoints(const FGameplayAttributeData& OldManaPoints) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, ManaPoints, OldManaPoints);
}

void UAttributeSetGlobal::OnRep_ManaPointsMax(const FGameplayAttributeData& OldManaPointsMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, ManaPointsMax, OldManaPointsMax);
}

void UAttributeSetGlobal::OnRep_TacticalPoints(const FGameplayAttributeData& OldTacticalPoints) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, TacticalPoints, OldTacticalPoints);
}

void UAttributeSetGlobal::OnRep_TacticalPointsMax(const FGameplayAttributeData& OldTacticalPointsMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, TacticalPointsMax, OldTacticalPointsMax);
}

#pragma endregion

#pragma region MainAttributes

void UAttributeSetGlobal::OnRep_Strength(const FGameplayAttributeData& OldStrength) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Strength, OldStrength);
}

void UAttributeSetGlobal::OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Dexterity, OldDexterity);
}

void UAttributeSetGlobal::OnRep_Agility(const FGameplayAttributeData& OldAgility) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Agility, OldAgility);
}

void UAttributeSetGlobal::OnRep_Vitality(const FGameplayAttributeData& OldVitality) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Vitality, OldVitality);
}

void UAttributeSetGlobal::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Intelligence, OldIntelligence);
}

void UAttributeSetGlobal::OnRep_Mind(const FGameplayAttributeData& OldMind) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Mind, OldMind);
}

void UAttributeSetGlobal::OnRep_Charisma(const FGameplayAttributeData& OldCharisma) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Charisma, OldCharisma);
}

#pragma endregion

#pragma region PhysicalSubAttributes

void UAttributeSetGlobal::OnRep_Attack(const FGameplayAttributeData& OldAttack) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Attack, OldAttack);
}

void UAttributeSetGlobal::OnRep_RangedAttack(const FGameplayAttributeData& OldRangedAttack) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, RangedAttack, OldRangedAttack);
}

void UAttributeSetGlobal::OnRep_Defense(const FGameplayAttributeData& OldDefense) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Defense, OldDefense);
}

void UAttributeSetGlobal::OnRep_Accuracy(const FGameplayAttributeData& OldAccuracy) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Accuracy, OldAccuracy);
}

void UAttributeSetGlobal::OnRep_RangedAccuracy(const FGameplayAttributeData& OldRangedAccuracy) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, RangedAccuracy, OldRangedAccuracy);
}

void UAttributeSetGlobal::OnRep_Evasion(const FGameplayAttributeData& OldEvasion) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Evasion, OldEvasion);
}

void UAttributeSetGlobal::OnRep_CriticalHitRate(const FGameplayAttributeData& OldCriticalHitRate) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, CriticalHitRate, OldCriticalHitRate);
}

void UAttributeSetGlobal::OnRep_CriticalHitBonus(const FGameplayAttributeData& OldCriticalHitBonus) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, CriticalHitBonus, OldCriticalHitBonus);
}

void UAttributeSetGlobal::OnRep_RangedCriticalHitRate(const FGameplayAttributeData& OldRangedCriticalHitRate) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, RangedCriticalHitRate, OldRangedCriticalHitRate);
}

void UAttributeSetGlobal::OnRep_RangedCriticalHitBonus(const FGameplayAttributeData& OldRangedCriticalHitBonus) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, RangedCriticalHitBonus, OldRangedCriticalHitBonus);
}

void UAttributeSetGlobal::OnRep_AttackDelay(const FGameplayAttributeData& OldAttackDelay) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, AttackDelay, OldAttackDelay);
}

void UAttributeSetGlobal::OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, AttackSpeed, OldAttackSpeed);
}

void UAttributeSetGlobal::OnRep_RangedAttackDelay(const FGameplayAttributeData& OldRangedAttackDelay) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, RangedAttackDelay, OldRangedAttackDelay);
}

void UAttributeSetGlobal::OnRep_RangedAttackSpeed(const FGameplayAttributeData& OldRangedAttackSpeed) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, RangedAttackSpeed, OldRangedAttackSpeed);
}

#pragma endregion

#pragma region MagicalSubAttributes

void UAttributeSetGlobal::OnRep_MagicAttack(const FGameplayAttributeData& OldMagicAttack) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, MagicAttack, OldMagicAttack);
}

void UAttributeSetGlobal::OnRep_MagicAccuracy(const FGameplayAttributeData& OldMagicAccuracy) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, MagicAccuracy, OldMagicAccuracy);
}

void UAttributeSetGlobal::OnRep_MagicEvasion(const FGameplayAttributeData& OldMagicEvasion) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, MagicEvasion, OldMagicEvasion);
}

void UAttributeSetGlobal::OnRep_MagicCriticalHitRate(const FGameplayAttributeData& OldMagicCriticalHitRate) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, MagicCriticalHitRate, OldMagicCriticalHitRate);
}

void UAttributeSetGlobal::OnRep_MagicCriticalHitBonus(const FGameplayAttributeData& OldMagicCriticalHitBonus) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, MagicCriticalHitBonus, OldMagicCriticalHitBonus);
}

void UAttributeSetGlobal::OnRep_CastSpeed(const FGameplayAttributeData& OldCastSpeed) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, CastSpeed, OldCastSpeed);
}

#pragma endregion

#pragma region ElementalResistences

void UAttributeSetGlobal::OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, FireResistance, OldFireResistance);
}

void UAttributeSetGlobal::OnRep_IceResistance(const FGameplayAttributeData& OldIceResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, IceResistance, OldIceResistance);
}

void UAttributeSetGlobal::OnRep_WindResistance(const FGameplayAttributeData& OldWindResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, WindResistance, OldWindResistance);
}

void UAttributeSetGlobal::OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, LightningResistance, OldLightningResistance);
}

void UAttributeSetGlobal::OnRep_EarthResistance(const FGameplayAttributeData& OldEarthResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, EarthResistance, OldEarthResistance);
}

void UAttributeSetGlobal::OnRep_WaterResistance(const FGameplayAttributeData& OldWaterResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, WaterResistance, OldWaterResistance);
}

void UAttributeSetGlobal::OnRep_LightResistance(const FGameplayAttributeData& OldLightResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, LightResistance, OldLightResistance);
}

void UAttributeSetGlobal::OnRep_DarkResistance(const FGameplayAttributeData& OldDarkResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, DarkResistance, OldDarkResistance);
}

#pragma endregion

#pragma region ResistStatus

void UAttributeSetGlobal::OnRep_AmnesiaResistance(const FGameplayAttributeData& OldAmnesiaResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, AmnesiaResistance, OldAmnesiaResistance);
}

void UAttributeSetGlobal::OnRep_BindResistance(const FGameplayAttributeData& OldBindResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, BindResistance, OldBindResistance);
}

void UAttributeSetGlobal::OnRep_BlindResistance(const FGameplayAttributeData& OldBlindResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, BlindResistance, OldBlindResistance);
}

void UAttributeSetGlobal::OnRep_GravityResistance(const FGameplayAttributeData& OldGravityResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, GravityResistance, OldGravityResistance);
}

void UAttributeSetGlobal::OnRep_ParalyzeResistance(const FGameplayAttributeData& OldParalyzeResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, ParalyzeResistance, OldParalyzeResistance);
}

void UAttributeSetGlobal::OnRep_PetrifyResistance(const FGameplayAttributeData& OldPetrifyResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, PetrifyResistance, OldPetrifyResistance);
}

void UAttributeSetGlobal::OnRep_PoisonResistance(const FGameplayAttributeData& OldPoisonResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, PoisonResistance, OldPoisonResistance);
}

void UAttributeSetGlobal::OnRep_SilenceResistance(const FGameplayAttributeData& OldSilenceResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, SilenceResistance, OldSilenceResistance);
}

void UAttributeSetGlobal::OnRep_SleepResistance(const FGameplayAttributeData& OldSleepResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, SleepResistance, OldSleepResistance);
}

void UAttributeSetGlobal::OnRep_SlowResistance(const FGameplayAttributeData& OldSlowResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, SlowResistance, OldSlowResistance);
}

void UAttributeSetGlobal::OnRep_VirusResistance(const FGameplayAttributeData& OldVirusResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, VirusResistance, OldVirusResistance);
}

#pragma endregion ResistStatus

#pragma region OtherAttributes

void UAttributeSetGlobal::OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, MoveSpeed, OldMoveSpeed);
}

void UAttributeSetGlobal::OnRep_CurePotency(const FGameplayAttributeData& OldCurePotency) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, CurePotency, OldCurePotency);
}

void UAttributeSetGlobal::OnRep_CureReceivedPotency(const FGameplayAttributeData& OldCureReceivedPotency) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, CureReceivedPotency, OldCureReceivedPotency);
}

void UAttributeSetGlobal::OnRep_Enmity(const FGameplayAttributeData& OldEnmity) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Enmity, OldEnmity);
}

void UAttributeSetGlobal::OnRep_DamageResist(const FGameplayAttributeData& OldDamageResist) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, DamageResist, OldDamageResist);
}

void UAttributeSetGlobal::OnRep_SpellInterruption(const FGameplayAttributeData& OldSpellInterruption) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, SpellInterruption, OldSpellInterruption);
}

#pragma endregion OtherAttributes