// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/XIItemAbility.h"

FGameplayTagContainer UXIItemAbility::GetCooldownTag()
{
	if(AbilityData)
    {
        return AbilityData->CooldownTags;
    }
    return FGameplayTagContainer::FGameplayTagContainer();
}

float UXIItemAbility::GetCost()
{
    if(AbilityData)
    {
        return AbilityData->Cost;
    }
	return 0.f;
}