// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GMMCs/XIHeroSubJobLevelAdjust.h"
#include "Characters/XICharacterBaseHero.h"

float UXIHeroSubJobLevelAdjust::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    float MainJobLevel = 0.f;
    float SubJobLevel = 0.f;

    AXICharacterBaseHero* XIHero = Cast<AXICharacterBaseHero>(Spec.GetEffectContext().GetInstigator());
    if(XIHero)
    {
        FGameplayTag MainJobTag;
        FGameplayTag SubJobTag;
    
        XIHero->GetCharacterActiveJobsAndLevels(MainJobTag, MainJobLevel, SubJobTag, SubJobLevel);
    }
    
    if(SubJobLevel > FMath::Floor(MainJobLevel / 2.f))
    {
        return FMath::Floor(MainJobLevel / 2.f);
    }
    else
    {
        return SubJobLevel;
    }
}