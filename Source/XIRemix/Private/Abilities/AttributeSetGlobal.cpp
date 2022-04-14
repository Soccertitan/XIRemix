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
    , AttackDelay(340.f)
    , AttackSpeed(1.f)
    , CriticalHitRate(0.05f)
    , RangedCriticalHitRate(0.05f)
    , BluntResistance(1.f)
    , PierceResistance(1.f)
    , SlashResistance(1.f)
    , FireResistance(1.f)
    , IceResistance(1.f)
    , WindResistance(1.f)
    , LightningResistance(1.f)
    , EarthResistance(1.f)
    , WaterResistance(1.f)
    , LightResistance(1.f)
    , DarkResistance(1.f)
    , AmnesiaResistance(1.f)
    , BindResistance(1.f)
    , BlindResistance(1.f)
    , GravityResistance(1.f)
    , ParalyzeResistance(1.f)
    , PetrifyResistance(1.f)
    , PoisonResistance(1.f)
    , SilenceResistance(1.f)
    , SleepResistance(1.f)
    , SlowResistance(1.f)
    , VirusResistance(1.f)
    , MoveSpeed(600.f)
    , CurePotency(1.f)
    , CureReceivedPotency(1.f)
    , DamageResist(1.f)
    , SpellInterruption(1.f)
{
}

void UAttributeSetGlobal::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);
    
    if (Attribute == GetHitPointsMaxAttribute())
    {
        UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
        if (AbilityComp)
        {
            AbilityComp->ApplyModToAttribute(GetHitPointsAttribute(), EGameplayModOp::Override, FMath::Min(GetHitPoints(), NewValue));
        }
    }
    else if (Attribute == GetManaPointsMaxAttribute())
    {
        UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
        if (AbilityComp)
        {
            AbilityComp->ApplyModToAttribute(GetManaPointsAttribute(), EGameplayModOp::Override, FMath::Min(GetManaPoints(), NewValue));
        }
    }
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
    else if (Data.EvaluatedData.Attribute == GetHitPointsMaxAttribute())
    {
        //Clamp Current HitPoints
        SetHitPoints(FMath::Min(GetHitPoints(), GetHitPointsMax()));
    }
    else if (Data.EvaluatedData.Attribute == GetManaPointsMaxAttribute())
    {
        SetManaPoints(FMath::Min(GetManaPoints(), GetManaPointsMax()));
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
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, Evasion, COND_None, REPNOTIFY_Always);
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
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, AxeSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, AxeSkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, GreatAxeSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, GreatAxeSkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, ClubSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, ClubSkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, DaggerSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, DaggerSkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, HandToHandSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, HandToHandSkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, KatanaSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, KatanaSkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, GreatKatanaSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, GreatKatanaSkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, PolearmSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, PolearmSkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, ScytheSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, ScytheSkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, StaffSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, StaffSkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, SwordSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, SwordSkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, GreatSwordSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, GreatSwordSkillMax, COND_None, REPNOTIFY_Always);

    //**
    // Ranged Skills
    //**
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, ArcherySkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, ArcherySkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, MarksmanshipSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, MarksmanshipSkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, ThrowingSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, ThrowingSkillMax, COND_None, REPNOTIFY_Always);

    //**
    // Defensive Skills
    //**
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, EvasionSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, EvasionSkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, GuardSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, GuardSkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, ParrySkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, ParrySkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, ShieldSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, ShieldSkillMax, COND_None, REPNOTIFY_Always);

    //**
    // Special Skills
    //**
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, BlueMagicSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, BlueMagicSkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, DarkMagicSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, DarkMagicSkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, DivineMagicSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, DivineMagicSkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, ElementalMagicSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, ElementalMagicSkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, EnfeeblingMagicSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, EnfeeblingMagicSkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, EnhancingMagicSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, EnhancingMagicSkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, HealingMagicSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, HealingMagicSkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, SummoningMagicSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, SummoningMagicSkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, NinjutsuSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, NinjutsuSkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, SingingSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, SingingSkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, StringSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, StringSkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, WindSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, WindSkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, GeomancySkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, GeomancySkillMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, HandbellSkill, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetGlobal, HandbellSkillMax, COND_None, REPNOTIFY_Always);

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

void UAttributeSetGlobal::OnRep_Evasion(const FGameplayAttributeData& OldEvasion) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, Evasion, OldEvasion);
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

void UAttributeSetGlobal::OnRep_AxeSkill(const FGameplayAttributeData& OldAxeSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, AxeSkill, OldAxeSkill);
}
void UAttributeSetGlobal::OnRep_AxeSkillMax(const FGameplayAttributeData& OldAxeSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, AxeSkillMax, OldAxeSkillMax);
}
void UAttributeSetGlobal::OnRep_GreatAxeSkill(const FGameplayAttributeData& OldGreatAxeSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, GreatAxeSkill, OldGreatAxeSkill);
}
void UAttributeSetGlobal::OnRep_GreatAxeSkillMax(const FGameplayAttributeData& OldGreatAxeSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, GreatAxeSkillMax, OldGreatAxeSkillMax);
}
void UAttributeSetGlobal::OnRep_ClubSkill(const FGameplayAttributeData& OldClubSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, ClubSkill, OldClubSkill);
}
void UAttributeSetGlobal::OnRep_ClubSkillMax(const FGameplayAttributeData& OldClubSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, ClubSkillMax, OldClubSkillMax);
}
void UAttributeSetGlobal::OnRep_DaggerSkill(const FGameplayAttributeData& OldDaggerSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, DaggerSkill, OldDaggerSkill);
}
void UAttributeSetGlobal::OnRep_DaggerSkillMax(const FGameplayAttributeData& OldDaggerSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, DaggerSkillMax, OldDaggerSkillMax);
}
void UAttributeSetGlobal::OnRep_HandToHandSkill(const FGameplayAttributeData& OldHandToHandSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, HandToHandSkill, OldHandToHandSkill);
}
void UAttributeSetGlobal::OnRep_HandToHandSkillMax(const FGameplayAttributeData& OldHandToHandSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, HandToHandSkillMax, OldHandToHandSkillMax);
}
void UAttributeSetGlobal::OnRep_KatanaSkill(const FGameplayAttributeData& OldKatanaSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, KatanaSkill, OldKatanaSkill);
}
void UAttributeSetGlobal::OnRep_KatanaSkillMax(const FGameplayAttributeData& OldKatanaSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, KatanaSkillMax, OldKatanaSkillMax);
}
void UAttributeSetGlobal::OnRep_GreatKatanaSkill(const FGameplayAttributeData& OldGreatKatanaSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, GreatKatanaSkill, OldGreatKatanaSkill);
}
void UAttributeSetGlobal::OnRep_GreatKatanaSkillMax(const FGameplayAttributeData& OldGreatKatanaSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, GreatKatanaSkillMax, OldGreatKatanaSkillMax);
}
void UAttributeSetGlobal::OnRep_PolearmSkill(const FGameplayAttributeData& OldPolearmSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, PolearmSkill, OldPolearmSkill);
}
void UAttributeSetGlobal::OnRep_PolearmSkillMax(const FGameplayAttributeData& OldPolearmSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, PolearmSkillMax, OldPolearmSkillMax);
}
void UAttributeSetGlobal::OnRep_ScytheSkill(const FGameplayAttributeData& OldScytheSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, ScytheSkill, OldScytheSkill);
}
void UAttributeSetGlobal::OnRep_ScytheSkillMax(const FGameplayAttributeData& OldScytheSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, ScytheSkillMax, OldScytheSkillMax);
}
void UAttributeSetGlobal::OnRep_StaffSkill(const FGameplayAttributeData& OldStaffSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, StaffSkill, OldStaffSkill);
}
void UAttributeSetGlobal::OnRep_StaffSkillMax(const FGameplayAttributeData& OldStaffSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, StaffSkillMax, OldStaffSkillMax);
}
void UAttributeSetGlobal::OnRep_SwordSkill(const FGameplayAttributeData& OldSwordSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, SwordSkill, OldSwordSkill);
}
void UAttributeSetGlobal::OnRep_SwordSkillMax(const FGameplayAttributeData& OldSwordSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, SwordSkillMax, OldSwordSkillMax);
}
void UAttributeSetGlobal::OnRep_GreatSwordSkill(const FGameplayAttributeData& OldGreatSwordSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, GreatSwordSkill, OldGreatSwordSkill);
}
void UAttributeSetGlobal::OnRep_GreatSwordSkillMax(const FGameplayAttributeData& OldGreatSwordSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, GreatSwordSkillMax, OldGreatSwordSkillMax);
}

//**
// Ranged SKills
//**

void UAttributeSetGlobal::OnRep_ArcherySkill(const FGameplayAttributeData& OldArcherySkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, ArcherySkill, OldArcherySkill);
}
void UAttributeSetGlobal::OnRep_ArcherySkillMax(const FGameplayAttributeData& OldArcherySkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, ArcherySkillMax, OldArcherySkillMax);
}
void UAttributeSetGlobal::OnRep_MarksmanshipSkill(const FGameplayAttributeData& OldMarksmanshipSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, MarksmanshipSkill, OldMarksmanshipSkill);
}
void UAttributeSetGlobal::OnRep_MarksmanshipSkillMax(const FGameplayAttributeData& OldMarksmanshipSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, MarksmanshipSkillMax, OldMarksmanshipSkillMax);
}
void UAttributeSetGlobal::OnRep_ThrowingSkill(const FGameplayAttributeData& OldThrowingSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, ThrowingSkill, OldThrowingSkill);
}
void UAttributeSetGlobal::OnRep_ThrowingSkillMax(const FGameplayAttributeData& OldThrowingSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, ThrowingSkillMax, OldThrowingSkillMax);
}

//**
// Defensive Skills
//**

void UAttributeSetGlobal::OnRep_EvasionSkill(const FGameplayAttributeData& OldEvasionSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, EvasionSkill, OldEvasionSkill);
}
void UAttributeSetGlobal::OnRep_EvasionSkillMax(const FGameplayAttributeData& OldEvasionSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, EvasionSkillMax, OldEvasionSkillMax);
}
void UAttributeSetGlobal::OnRep_GuardSkill(const FGameplayAttributeData& OldGuardSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, GuardSkill, OldGuardSkill);
}
void UAttributeSetGlobal::OnRep_GuardSkillMax(const FGameplayAttributeData& OldGuardSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, GuardSkillMax, OldGuardSkillMax);
}
void UAttributeSetGlobal::OnRep_ParrySkill(const FGameplayAttributeData& OldParrySkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, ParrySkill, OldParrySkill);
}
void UAttributeSetGlobal::OnRep_ParrySkillMax(const FGameplayAttributeData& OldParrySkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, ParrySkillMax, OldParrySkillMax);
}
void UAttributeSetGlobal::OnRep_ShieldSkill(const FGameplayAttributeData& OldShieldSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, ShieldSkill, OldShieldSkill);
}
void UAttributeSetGlobal::OnRep_ShieldSkillMax(const FGameplayAttributeData& OldShieldSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, ShieldSkillMax, OldShieldSkillMax);
}

//**
// Special SKills
//**

void UAttributeSetGlobal::OnRep_BlueMagicSkill(const FGameplayAttributeData& OldBlueMagicSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, BlueMagicSkill, OldBlueMagicSkill);
}
void UAttributeSetGlobal::OnRep_BlueMagicSkillMax(const FGameplayAttributeData& OldBlueMagicSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, BlueMagicSkillMax, OldBlueMagicSkillMax);
}
void UAttributeSetGlobal::OnRep_DarkMagicSkill(const FGameplayAttributeData& OldDarkMagicSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, DarkMagicSkill, OldDarkMagicSkill);
}
void UAttributeSetGlobal::OnRep_DarkMagicSkillMax(const FGameplayAttributeData& OldDarkMagicSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, DarkMagicSkillMax, OldDarkMagicSkillMax);
}
void UAttributeSetGlobal::OnRep_DivineMagicSkill(const FGameplayAttributeData& OldDivineMagicSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, DivineMagicSkill, OldDivineMagicSkill);
}
void UAttributeSetGlobal::OnRep_DivineMagicSkillMax(const FGameplayAttributeData& OldDivineMagicSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, DivineMagicSkillMax, OldDivineMagicSkillMax);
}
void UAttributeSetGlobal::OnRep_ElementalMagicSkill(const FGameplayAttributeData& OldElementalMagicSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, ElementalMagicSkill, OldElementalMagicSkill);
}
void UAttributeSetGlobal::OnRep_ElementalMagicSkillMax(const FGameplayAttributeData& OldElementalMagicSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, ElementalMagicSkillMax, OldElementalMagicSkillMax);
}
void UAttributeSetGlobal::OnRep_EnfeeblingMagicSkill(const FGameplayAttributeData& OldEnfeeblingMagicSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, EnfeeblingMagicSkill, OldEnfeeblingMagicSkill);
}
void UAttributeSetGlobal::OnRep_EnfeeblingMagicSkillMax(const FGameplayAttributeData& OldEnfeeblingMagicSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, EnfeeblingMagicSkillMax, OldEnfeeblingMagicSkillMax);
}
void UAttributeSetGlobal::OnRep_EnhancingMagicSkill(const FGameplayAttributeData& OldEnhancingMagicSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, EnhancingMagicSkill, OldEnhancingMagicSkill);
}
void UAttributeSetGlobal::OnRep_EnhancingMagicSkillMax(const FGameplayAttributeData& OldEnhancingMagicSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, EnhancingMagicSkillMax, OldEnhancingMagicSkillMax);
}
void UAttributeSetGlobal::OnRep_HealingMagicSkill(const FGameplayAttributeData& OldHealingMagicSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, HealingMagicSkill, OldHealingMagicSkill);
}
void UAttributeSetGlobal::OnRep_HealingMagicSkillMax(const FGameplayAttributeData& OldHealingMagicSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, HealingMagicSkillMax, OldHealingMagicSkillMax);
}
void UAttributeSetGlobal::OnRep_SummoningMagicSkill(const FGameplayAttributeData& OldSummoningMagicSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, SummoningMagicSkill, OldSummoningMagicSkill);
}
void UAttributeSetGlobal::OnRep_SummoningMagicSkillMax(const FGameplayAttributeData& OldSummoningMagicSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, SummoningMagicSkillMax, OldSummoningMagicSkillMax);
}
void UAttributeSetGlobal::OnRep_NinjutsuSkill(const FGameplayAttributeData& OldNinjutsuSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, NinjutsuSkill, OldNinjutsuSkill);
}
void UAttributeSetGlobal::OnRep_NinjutsuSkillMax(const FGameplayAttributeData& OldNinjutsuSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, NinjutsuSkillMax, OldNinjutsuSkillMax);
}
void UAttributeSetGlobal::OnRep_SingingSkill(const FGameplayAttributeData& OldSingingSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, SingingSkill, OldSingingSkill);
}
void UAttributeSetGlobal::OnRep_SingingSkillMax(const FGameplayAttributeData& OldSingingSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, SingingSkillMax, OldSingingSkillMax);
}
void UAttributeSetGlobal::OnRep_StringSkill(const FGameplayAttributeData& OldStringSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, StringSkill, OldStringSkill);
}
void UAttributeSetGlobal::OnRep_StringSkillMax(const FGameplayAttributeData& OldStringSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, StringSkillMax, OldStringSkillMax);
}
void UAttributeSetGlobal::OnRep_WindSkill(const FGameplayAttributeData& OldWindSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, WindSkill, OldWindSkill);
}
void UAttributeSetGlobal::OnRep_WindSkillMax(const FGameplayAttributeData& OldWindSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, WindSkillMax, OldWindSkillMax);
}
void UAttributeSetGlobal::OnRep_GeomancySkill(const FGameplayAttributeData& OldGeomancySkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, GeomancySkill, OldGeomancySkill);
}
void UAttributeSetGlobal::OnRep_GeomancySkillMax(const FGameplayAttributeData& OldGeomancySkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, GeomancySkillMax, OldGeomancySkillMax);
}
void UAttributeSetGlobal::OnRep_HandbellSkill(const FGameplayAttributeData& OldHandbellSkill) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, HandbellSkill, OldHandbellSkill);
}
void UAttributeSetGlobal::OnRep_HandbellSkillMax(const FGameplayAttributeData& OldHandbellSkillMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetGlobal, HandbellSkillMax, OldHandbellSkillMax);
}

#pragma endregion CombatSkills

