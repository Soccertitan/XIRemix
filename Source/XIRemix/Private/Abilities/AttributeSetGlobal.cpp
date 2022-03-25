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
    , TacticalPointsMax(3000.f)
{
}

void UAttributeSetGlobal::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

    if(Data.EvaluatedData.Attribute == GetDamageHPAttribute())
    {
        // Store a local copy of the amount of damage done and clear the damage attribute
		const float LocalDamageDone = GetDamageHP();
		SetDamageHP(0.f);

        if(LocalDamageDone > 0)
        {
            //TODO: Add something for Stoneskin to remove damage from there before applying to HP.

            // Apply the health change and then clamp it.
            const float OldHealth = GetHitPoints();
            SetHitPoints(FMath::Clamp(OldHealth - LocalDamageDone, 0.f, GetHitPointsMax()));
        }
    }
    else if (Data.EvaluatedData.Attribute == GetHitPointsAttribute())
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
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, SpellInterruption, COND_None, REPNOTIFY_Always);

    // Skill Attributes

    //**
    // Melee Skills
    //**
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Axe, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, AxeMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, GreatAxe, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, GreatAxeMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Club, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, ClubMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Dagger, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, DaggerMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, HandToHand, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, HandToHandMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Katana, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, KatanaMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, GreatKatana, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, GreatKatanaMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Polearm, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, PolearmMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Scythe, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, ScytheMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Staff, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, StaffMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Sword, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, SwordMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, GreatSword, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, GreatSwordMax, COND_None, REPNOTIFY_Always);

    //**
    // Ranged Skills
    //**
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Archery, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, ArcheryMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Marksmanship, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, MarksmanshipMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Throwing, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, ThrowingMax, COND_None, REPNOTIFY_Always);

    //**
    // Defensive Skills
    //**
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Evasion, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, EvasionMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Guard, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, GuardMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Parry, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, ParryMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Shield, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, ShieldMax, COND_None, REPNOTIFY_Always);

    //**
    // Special Skills
    //**
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Blue, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, BlueMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Dark, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, DarkMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Divine, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, DivineMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Elemental, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, ElementalMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Enfeebling, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, EnfeeblingMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Enhancing, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, EnhancingMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Healing, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, HealingMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Summoning, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, SummoningMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Ninjutsu, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, NinjutsuMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Singing, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, SingingMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, String, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, StringMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Wind, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, WindMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Geomancy, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, GeomancyMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Handbell, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, HandbellMax, COND_None, REPNOTIFY_Always);

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

void UAttributeSetGlobal::OnRep_DamageResist(const FGameplayAttributeData& OldDamageResist) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, DamageResist, OldDamageResist);
}

void UAttributeSetGlobal::OnRep_SpellInterruption(const FGameplayAttributeData& OldSpellInterruption) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, SpellInterruption, OldSpellInterruption);
}

#pragma endregion OtherAttributes

#pragma region CombatSkills

//**
// Melee Skills
//**

void UAttributeSetGlobal::OnRep_Axe(const FGameplayAttributeData& OldAxe) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Axe, OldAxe);
}
void UAttributeSetGlobal::OnRep_AxeMax(const FGameplayAttributeData& OldAxeMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, AxeMax, OldAxeMax);
}
void UAttributeSetGlobal::OnRep_GreatAxe(const FGameplayAttributeData& OldGreatAxe) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, GreatAxe, OldGreatAxe);
}
void UAttributeSetGlobal::OnRep_GreatAxeMax(const FGameplayAttributeData& OldGreatAxeMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, GreatAxeMax, OldGreatAxeMax);
}
void UAttributeSetGlobal::OnRep_Club(const FGameplayAttributeData& OldClub) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Club, OldClub);
}
void UAttributeSetGlobal::OnRep_ClubMax(const FGameplayAttributeData& OldClubMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, ClubMax, OldClubMax);
}
void UAttributeSetGlobal::OnRep_Dagger(const FGameplayAttributeData& OldDagger) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Dagger, OldDagger);
}
void UAttributeSetGlobal::OnRep_DaggerMax(const FGameplayAttributeData& OldDaggerMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, DaggerMax, OldDaggerMax);
}
void UAttributeSetGlobal::OnRep_HandToHand(const FGameplayAttributeData& OldHandToHand) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, HandToHand, OldHandToHand);
}
void UAttributeSetGlobal::OnRep_HandToHandMax(const FGameplayAttributeData& OldHandToHandMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, HandToHandMax, OldHandToHandMax);
}
void UAttributeSetGlobal::OnRep_Katana(const FGameplayAttributeData& OldKatana) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Katana, OldKatana);
}
void UAttributeSetGlobal::OnRep_KatanaMax(const FGameplayAttributeData& OldKatanaMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, KatanaMax, OldKatanaMax);
}
void UAttributeSetGlobal::OnRep_GreatKatana(const FGameplayAttributeData& OldGreatKatana) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, GreatKatana, OldGreatKatana);
}
void UAttributeSetGlobal::OnRep_GreatKatanaMax(const FGameplayAttributeData& OldGreatKatanaMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, GreatKatanaMax, OldGreatKatanaMax);
}
void UAttributeSetGlobal::OnRep_Polearm(const FGameplayAttributeData& OldPolearm) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Polearm, OldPolearm);
}
void UAttributeSetGlobal::OnRep_PolearmMax(const FGameplayAttributeData& OldPolearmMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, PolearmMax, OldPolearmMax);
}
void UAttributeSetGlobal::OnRep_Scythe(const FGameplayAttributeData& OldScythe) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Scythe, OldScythe);
}
void UAttributeSetGlobal::OnRep_ScytheMax(const FGameplayAttributeData& OldScytheMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, ScytheMax, OldScytheMax);
}
void UAttributeSetGlobal::OnRep_Staff(const FGameplayAttributeData& OldStaff) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Staff, OldStaff);
}
void UAttributeSetGlobal::OnRep_StaffMax(const FGameplayAttributeData& OldStaffMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, StaffMax, OldStaffMax);
}
void UAttributeSetGlobal::OnRep_Sword(const FGameplayAttributeData& OldSword) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Sword, OldSword);
}
void UAttributeSetGlobal::OnRep_SwordMax(const FGameplayAttributeData& OldSwordMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, SwordMax, OldSwordMax);
}
void UAttributeSetGlobal::OnRep_GreatSword(const FGameplayAttributeData& OldGreatSword) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, GreatSword, OldGreatSword);
}
void UAttributeSetGlobal::OnRep_GreatSwordMax(const FGameplayAttributeData& OldGreatSwordMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, GreatSwordMax, OldGreatSwordMax);
}

//**
// Ranged SKills
//**

void UAttributeSetGlobal::OnRep_Archery(const FGameplayAttributeData& OldArchery) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Archery, OldArchery);
}
void UAttributeSetGlobal::OnRep_ArcheryMax(const FGameplayAttributeData& OldArcheryMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, ArcheryMax, OldArcheryMax);
}
void UAttributeSetGlobal::OnRep_Marksmanship(const FGameplayAttributeData& OldMarksmanship) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Marksmanship, OldMarksmanship);
}
void UAttributeSetGlobal::OnRep_MarksmanshipMax(const FGameplayAttributeData& OldMarksmanshipMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, MarksmanshipMax, OldMarksmanshipMax);
}
void UAttributeSetGlobal::OnRep_Throwing(const FGameplayAttributeData& OldThrowing) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Throwing, OldThrowing);
}
void UAttributeSetGlobal::OnRep_ThrowingMax(const FGameplayAttributeData& OldThrowingMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, ThrowingMax, OldThrowingMax);
}

//**
// Defensive Skills
//**

void UAttributeSetGlobal::OnRep_Evasion(const FGameplayAttributeData& OldEvasion) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Evasion, OldEvasion);
}
void UAttributeSetGlobal::OnRep_EvasionMax(const FGameplayAttributeData& OldEvasionMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, EvasionMax, OldEvasionMax);
}
void UAttributeSetGlobal::OnRep_Guard(const FGameplayAttributeData& OldGuard) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Guard, OldGuard);
}
void UAttributeSetGlobal::OnRep_GuardMax(const FGameplayAttributeData& OldGuardMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, GuardMax, OldGuardMax);
}
void UAttributeSetGlobal::OnRep_Parry(const FGameplayAttributeData& OldParry) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Parry, OldParry);
}
void UAttributeSetGlobal::OnRep_ParryMax(const FGameplayAttributeData& OldParryMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, ParryMax, OldParryMax);
}
void UAttributeSetGlobal::OnRep_Shield(const FGameplayAttributeData& OldShield) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Shield, OldShield);
}
void UAttributeSetGlobal::OnRep_ShieldMax(const FGameplayAttributeData& OldShieldMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, ShieldMax, OldShieldMax);
}

//**
// Special SKills
//**

void UAttributeSetGlobal::OnRep_Blue(const FGameplayAttributeData& OldBlue) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Blue, OldBlue);
}
void UAttributeSetGlobal::OnRep_BlueMax(const FGameplayAttributeData& OldBlueMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, BlueMax, OldBlueMax);
}
void UAttributeSetGlobal::OnRep_Dark(const FGameplayAttributeData& OldDark) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Dark, OldDark);
}
void UAttributeSetGlobal::OnRep_DarkMax(const FGameplayAttributeData& OldDarkMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, DarkMax, OldDarkMax);
}
void UAttributeSetGlobal::OnRep_Divine(const FGameplayAttributeData& OldDivine) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Divine, OldDivine);
}
void UAttributeSetGlobal::OnRep_DivineMax(const FGameplayAttributeData& OldDivineMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, DivineMax, OldDivineMax);
}
void UAttributeSetGlobal::OnRep_Elemental(const FGameplayAttributeData& OldElemental) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Elemental, OldElemental);
}
void UAttributeSetGlobal::OnRep_ElementalMax(const FGameplayAttributeData& OldElementalMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, ElementalMax, OldElementalMax);
}
void UAttributeSetGlobal::OnRep_Enfeebling(const FGameplayAttributeData& OldEnfeebling) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Enfeebling, OldEnfeebling);
}
void UAttributeSetGlobal::OnRep_EnfeeblingMax(const FGameplayAttributeData& OldEnfeeblingMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, EnfeeblingMax, OldEnfeeblingMax);
}
void UAttributeSetGlobal::OnRep_Enhancing(const FGameplayAttributeData& OldEnhancing) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Enhancing, OldEnhancing);
}
void UAttributeSetGlobal::OnRep_EnhancingMax(const FGameplayAttributeData& OldEnhancingMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, EnhancingMax, OldEnhancingMax);
}
void UAttributeSetGlobal::OnRep_Healing(const FGameplayAttributeData& OldHealing) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Healing, OldHealing);
}
void UAttributeSetGlobal::OnRep_HealingMax(const FGameplayAttributeData& OldHealingMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, HealingMax, OldHealingMax);
}
void UAttributeSetGlobal::OnRep_Summoning(const FGameplayAttributeData& OldSummoning) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Summoning, OldSummoning);
}
void UAttributeSetGlobal::OnRep_SummoningMax(const FGameplayAttributeData& OldSummoningMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, SummoningMax, OldSummoningMax);
}
void UAttributeSetGlobal::OnRep_Ninjutsu(const FGameplayAttributeData& OldNinjutsu) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Ninjutsu, OldNinjutsu);
}
void UAttributeSetGlobal::OnRep_NinjutsuMax(const FGameplayAttributeData& OldNinjutsuMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, NinjutsuMax, OldNinjutsuMax);
}
void UAttributeSetGlobal::OnRep_Singing(const FGameplayAttributeData& OldSinging) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Singing, OldSinging);
}
void UAttributeSetGlobal::OnRep_SingingMax(const FGameplayAttributeData& OldSingingMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, SingingMax, OldSingingMax);
}
void UAttributeSetGlobal::OnRep_String(const FGameplayAttributeData& OldString) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, String, OldString);
}
void UAttributeSetGlobal::OnRep_StringMax(const FGameplayAttributeData& OldStringMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, StringMax, OldStringMax);
}
void UAttributeSetGlobal::OnRep_Wind(const FGameplayAttributeData& OldWind) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Wind, OldWind);
}
void UAttributeSetGlobal::OnRep_WindMax(const FGameplayAttributeData& OldWindMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, WindMax, OldWindMax);
}
void UAttributeSetGlobal::OnRep_Geomancy(const FGameplayAttributeData& OldGeomancy) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Geomancy, OldGeomancy);
}
void UAttributeSetGlobal::OnRep_GeomancyMax(const FGameplayAttributeData& OldGeomancyMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, GeomancyMax, OldGeomancyMax);
}
void UAttributeSetGlobal::OnRep_Handbell(const FGameplayAttributeData& OldHandbell) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Handbell, OldHandbell);
}
void UAttributeSetGlobal::OnRep_HandbellMax(const FGameplayAttributeData& OldHandbellMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, HandbellMax, OldHandbellMax);
}

#pragma endregion CombatSkills

