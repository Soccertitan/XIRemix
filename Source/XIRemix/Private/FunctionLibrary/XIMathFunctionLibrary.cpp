// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/XIMathFunctionLibrary.h"

#pragma region ConstVariables

const FGameplayTag UXIMathFunctionLibrary::Axe = FGameplayTag::RequestGameplayTag("Weapon.Melee.Axe");
const FGameplayTag UXIMathFunctionLibrary::Club = FGameplayTag::RequestGameplayTag("Weapon.Melee.Club");
const FGameplayTag UXIMathFunctionLibrary::Dagger = FGameplayTag::RequestGameplayTag("Weapon.Melee.Dagger");
const FGameplayTag UXIMathFunctionLibrary::GreatAxe = FGameplayTag::RequestGameplayTag("Weapon.Melee.GreatAxe");
const FGameplayTag UXIMathFunctionLibrary::GreatKatana = FGameplayTag::RequestGameplayTag("Weapon.Melee.GreatKatana");
const FGameplayTag UXIMathFunctionLibrary::HandToHand = FGameplayTag::RequestGameplayTag("Weapon.Melee.HandToHand");
const FGameplayTag UXIMathFunctionLibrary::Katana = FGameplayTag::RequestGameplayTag("Weapon.Melee.Katana");
const FGameplayTag UXIMathFunctionLibrary::Polearm = FGameplayTag::RequestGameplayTag("Weapon.Melee.Polearm");
const FGameplayTag UXIMathFunctionLibrary::Scythe = FGameplayTag::RequestGameplayTag("Weapon.Melee.Scythe");
const FGameplayTag UXIMathFunctionLibrary::Staff = FGameplayTag::RequestGameplayTag("Weapon.Melee.Staff");
const FGameplayTag UXIMathFunctionLibrary::Sword = FGameplayTag::RequestGameplayTag("Weapon.Melee.Sword");

const FGameplayTag UXIMathFunctionLibrary::Archery = FGameplayTag::RequestGameplayTag("Weapon.Ranged.Archery");
const FGameplayTag UXIMathFunctionLibrary::Marksmanship = FGameplayTag::RequestGameplayTag("Weapon.Ranged.Marksmanship");
const FGameplayTag UXIMathFunctionLibrary::Throwing = FGameplayTag::RequestGameplayTag("Weapon.Ranged.Throwing");

#pragma endregion ConstVariables

float UXIMathFunctionLibrary::fSTRMelee(float STR, float VIT, float WeaponDamage, bool bIsHandToHand)
{
    float dSTR = STR - VIT;
    float fSTR = FMath::Floor((dSTR + FMath::RoundToInt((-0.0017 * FMath::Pow(dSTR, 2)) - (0.2820 * dSTR) + 7.6319)) / 4);
    float WeaponRank;

    if (bIsHandToHand)
    {
        WeaponRank = FMath::Floor((WeaponDamage + 3) / 9);
    }
    else
    {
        WeaponRank = FMath::Floor(WeaponDamage / 9);
    }

    return FMath::Clamp(fSTR, FMath::Min(-WeaponRank, -1.f), WeaponRank + 8.f);
}

float UXIMathFunctionLibrary::fSTRRange(float STR, float VIT, float WeaponDamage)
{
    float dSTR = STR - VIT;
    float fSTR = FMath::Floor((dSTR + FMath::RoundToInt((-0.0017 * FMath::Pow(dSTR, 2)) - (0.2820 * dSTR) + 7.6319)) / 2);
    float WeaponRank = FMath::Floor(WeaponDamage / 9);
    
    return FMath::Clamp(fSTR, FMath::Min((-WeaponRank * 2), -2.f), (WeaponRank + 8.f) * 2.f);
}

float UXIMathFunctionLibrary::pDIF(float Attack, float Defense, float LevelDif, float CritChance, float CritBonus, FGameplayTag WeaponType, bool bIsMonster, bool& OutbIsCriticalHit)
{
    float pDIFCap;
    float cRatio;
    OutbIsCriticalHit = false;
    
    // Calculates the corrected attack/defense ratio based on the difference in levels. Only monsters get a bonus attacking characters at a lower level.
    if(bIsMonster)
    {
        cRatio = (Attack / Defense) - (LevelDif * 0.05);
    }
    else
    {
        if(WeaponType == Archery || WeaponType == Throwing || WeaponType == Marksmanship)
        {
            cRatio = (Attack / Defense) - (FMath::Max(0, LevelDif) * 0.025);
        }
        else
        {
            cRatio = (Attack / Defense) - (FMath::Max(0, LevelDif) * 0.05);
        }
    }
    
    if(WeaponType == Axe || WeaponType == Club || WeaponType == Dagger || WeaponType == Katana || WeaponType == Sword) pDIFCap = 3.25;
    else if(WeaponType == HandToHand || WeaponType == GreatKatana) pDIFCap = 3.5;
    else if(WeaponType == GreatAxe || WeaponType == Polearm || WeaponType == Staff) pDIFCap = 3.75;
    else if(WeaponType == Scythe) pDIFCap = 4;
    else if(WeaponType == Archery || WeaponType == Throwing) pDIFCap = 3.25;
    else if(WeaponType == Marksmanship) pDIFCap = 3.5;
    else pDIFCap = 3.5;

    if(FMath::RandRange(0.f, 1.f) <= CritChance)
    {
        if(WeaponType == Archery || WeaponType == Throwing || WeaponType == Marksmanship)
        {
            pDIFCap = pDIFCap * (1.25 + CritBonus);
            cRatio = cRatio * (1.25 + CritBonus);
        }
        else
        {
            pDIFCap = pDIFCap + 1 + CritBonus;
            cRatio = cRatio + 1 + CritBonus;
        }
        OutbIsCriticalHit = true;
    }

    float qRatio = FMath::Clamp(FMath::RandRange(cRatio - 0.375, cRatio + 0.375), 0, pDIFCap);

    return qRatio * FMath::RandRange(1.f, 1.05f);
}

float UXIMathFunctionLibrary::HitRate(float Accuracy, float Evasion, float LevelDif)
{
    float HitChance = (75 + FMath::Floor((Accuracy - Evasion) / 2) - (2.f * LevelDif)) / 100;

    return FMath::Clamp(HitChance, .2f, .95f);
}

float UXIMathFunctionLibrary::TPGained(float Delay)
{
    return FMath::Floor(61.f + ((Delay - 180.f) * 0.175f));
}