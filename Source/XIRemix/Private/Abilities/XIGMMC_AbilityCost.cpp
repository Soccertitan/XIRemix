// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/XIGMMC_AbilityCost.h"
#include "Abilities/XIGameplayAbility.h"

float UXIGMMC_AbilityCost::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const UXIGameplayAbility* Ability = Cast<UXIGameplayAbility>(Spec.GetContext().GetAbilityInstance_NotReplicated());

	if (!Ability)
	{
		return 0.0f;
	}
	
	return Ability->GetCost();
}