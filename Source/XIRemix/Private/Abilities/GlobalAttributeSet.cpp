// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GlobalAttributeSet.h"
#include "Net/UnrealNetwork.h"


UGlobalAttributeSet::UGlobalAttributeSet() 
{

}

void UGlobalAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const 
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // Resource Attributes
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, HitPoints, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, HitPointsMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, ManaPoints, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, ManaPointsMax, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, TechPoints, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, TechPointsMax, COND_None, REPNOTIFY_Always);

    // Main Attributes
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, Strength, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, Dexterity, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, Agility, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, Vitality, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, Mind, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, Charisma, COND_None, REPNOTIFY_Always);

    // Physical Sub Attributes
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, Attack, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, RangedAttack, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, Defense, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, Accuracy, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, Evasion, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, CriticalHitRate, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, CriticalHitBonus, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, RangedCriticalHitRate, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, RangedCriticalHitBonus, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, RangedAttackSpeed, COND_None, REPNOTIFY_Always);

    // Magical Sub Attributes
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, MagicAttack, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, MagicDefense, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, MagicAccuracy, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, MagicEvasion, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, MagicCriticalHitRate, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, MagicCriticalHitBonus, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, CastSpeed, COND_None, REPNOTIFY_Always);

    // Elemental Resistences
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, FireResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, IceResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, WindResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, LightningResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, EarthResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, WaterResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, LightResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGlobalAttributeSet, DarkResistance, COND_None, REPNOTIFY_Always);
}

#pragma region ResourceAttributesFunctions

void UGlobalAttributeSet::OnRep_HitPoints(const FGameplayAttributeData& OldHitPoints) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, HitPoints, OldHitPoints);
}

void UGlobalAttributeSet::OnRep_HitPointsMax(const FGameplayAttributeData& OldHitPointsMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, HitPointsMax, OldHitPointsMax);
}

void UGlobalAttributeSet::OnRep_ManaPoints(const FGameplayAttributeData& OldManaPoints) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, ManaPoints, OldManaPoints);
}

void UGlobalAttributeSet::OnRep_ManaPointsMax(const FGameplayAttributeData& OldManaPointsMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, ManaPointsMax, OldManaPointsMax);
}

void UGlobalAttributeSet::OnRep_TechPoints(const FGameplayAttributeData& OldTechPoints) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, TechPoints, OldTechPoints);
}

void UGlobalAttributeSet::OnRep_TechPointsMax(const FGameplayAttributeData& OldTechPointsMax) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, TechPointsMax, OldTechPointsMax);
}

#pragma endregion

#pragma region MainAttributes

void UGlobalAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, Strength, OldStrength);
}

void UGlobalAttributeSet::OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, Dexterity, OldDexterity);
}

void UGlobalAttributeSet::OnRep_Agility(const FGameplayAttributeData& OldAgility) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, Agility, OldAgility);
}

void UGlobalAttributeSet::OnRep_Vitality(const FGameplayAttributeData& OldVitality) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, Vitality, OldVitality);
}

void UGlobalAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, Intelligence, OldIntelligence);
}

void UGlobalAttributeSet::OnRep_Mind(const FGameplayAttributeData& OldMind) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, Mind, OldMind);
}

void UGlobalAttributeSet::OnRep_Charisma(const FGameplayAttributeData& OldCharisma) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, Charisma, OldCharisma);
}

#pragma endregion

#pragma region PhysicalSubAttributes

void UGlobalAttributeSet::OnRep_Attack(const FGameplayAttributeData& OldAttack) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, Attack, OldAttack);
}

void UGlobalAttributeSet::OnRep_RangedAttack(const FGameplayAttributeData& OldRangedAttack) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, RangedAttack, OldRangedAttack);
}

void UGlobalAttributeSet::OnRep_Defense(const FGameplayAttributeData& OldDefense) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, Defense, OldDefense);
}

void UGlobalAttributeSet::OnRep_Accuracy(const FGameplayAttributeData& OldAccuracy) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, Accuracy, OldAccuracy);
}

void UGlobalAttributeSet::OnRep_Evasion(const FGameplayAttributeData& OldEvasion) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, Evasion, OldEvasion);
}

void UGlobalAttributeSet::OnRep_CriticalHitRate(const FGameplayAttributeData& OldCriticalHitRate) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, CriticalHitRate, OldCriticalHitRate);
}

void UGlobalAttributeSet::OnRep_CriticalHitBonus(const FGameplayAttributeData& OldCriticalHitBonus) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, CriticalHitBonus, OldCriticalHitBonus);
}

void UGlobalAttributeSet::OnRep_RangedCriticalHitRate(const FGameplayAttributeData& OldRangedCriticalHitRate) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, RangedCriticalHitRate, OldRangedCriticalHitRate);
}

void UGlobalAttributeSet::OnRep_RangedCriticalHitBonus(const FGameplayAttributeData& OldRangedCriticalHitBonus) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, RangedCriticalHitBonus, OldRangedCriticalHitBonus);
}

void UGlobalAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, AttackSpeed, OldAttackSpeed);
}

void UGlobalAttributeSet::OnRep_RangedAttackSpeed(const FGameplayAttributeData& OldRangedAttackSpeed) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, RangedAttackSpeed, OldRangedAttackSpeed);
}

#pragma endregion

#pragma region MagicalSubAttributes

void UGlobalAttributeSet::OnRep_MagicAttack(const FGameplayAttributeData& OldMagicAttack) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, MagicAttack, OldMagicAttack);
}

void UGlobalAttributeSet::OnRep_MagicDefense(const FGameplayAttributeData& OldMagicDefense) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, MagicDefense, OldMagicDefense);
}

void UGlobalAttributeSet::OnRep_MagicAccuracy(const FGameplayAttributeData& OldMagicAccuracy) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, MagicAccuracy, OldMagicAccuracy);
}

void UGlobalAttributeSet::OnRep_MagicEvasion(const FGameplayAttributeData& OldMagicEvasion) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, MagicEvasion, OldMagicEvasion);
}

void UGlobalAttributeSet::OnRep_MagicCriticalHitRate(const FGameplayAttributeData& OldMagicCriticalHitRate) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, MagicCriticalHitRate, OldMagicCriticalHitRate);
}

void UGlobalAttributeSet::OnRep_MagicCriticalHitBonus(const FGameplayAttributeData& OldMagicCriticalHitBonus) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, MagicCriticalHitBonus, OldMagicCriticalHitBonus);
}

void UGlobalAttributeSet::OnRep_CastSpeed(const FGameplayAttributeData& OldCastSpeed) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, CastSpeed, OldCastSpeed);
}

#pragma endregion

#pragma region ElementalResistences

void UGlobalAttributeSet::OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, FireResistance, OldFireResistance);
}

void UGlobalAttributeSet::OnRep_IceResistance(const FGameplayAttributeData& OldIceResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, IceResistance, OldIceResistance);
}

void UGlobalAttributeSet::OnRep_WindResistance(const FGameplayAttributeData& OldWindResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, WindResistance, OldWindResistance);
}

void UGlobalAttributeSet::OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, LightningResistance, OldLightningResistance);
}

void UGlobalAttributeSet::OnRep_EarthResistance(const FGameplayAttributeData& OldEarthResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, EarthResistance, OldEarthResistance);
}

void UGlobalAttributeSet::OnRep_WaterResistance(const FGameplayAttributeData& OldWaterResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, WaterResistance, OldWaterResistance);
}

void UGlobalAttributeSet::OnRep_LightResistance(const FGameplayAttributeData& OldLightResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, LightResistance, OldLightResistance);
}

void UGlobalAttributeSet::OnRep_DarkResistance(const FGameplayAttributeData& OldDarkResistance) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGlobalAttributeSet, DarkResistance, OldDarkResistance);
}

#pragma endregion

