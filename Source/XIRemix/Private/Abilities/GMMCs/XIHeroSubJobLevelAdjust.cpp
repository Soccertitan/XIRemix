// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GMMCs/XIHeroSubJobLevelAdjust.h"
#include "Characters/XICharacterBaseHero.h"

float UXIHeroSubJobLevelAdjust::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    FXICharacterHeroActiveJobsLevels HeroCharacterJobs;

    AXICharacterBaseHero* XIHero = Cast<AXICharacterBaseHero>(Spec.GetEffectContext().GetInstigator());
    if(XIHero)
    {
        HeroCharacterJobs = XIHero->GetCharacterActiveJobsAndLevels();
    }
    
    if(HeroCharacterJobs.SubJobLevel > FMath::Floor(HeroCharacterJobs.MainJobLevel / 2.f))
    {
        return FMath::Max(FMath::Floor(HeroCharacterJobs.MainJobLevel / 2.f), 1.f);
    }
    else
    {
        return HeroCharacterJobs.SubJobLevel;
    }
}