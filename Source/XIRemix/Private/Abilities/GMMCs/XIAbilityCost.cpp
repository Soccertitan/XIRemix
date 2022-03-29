// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GMMCs/XIAbilityCost.h"
#include "Abilities/XIGameplayAbility.h"

float UXIAbilityCost::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const UXIGameplayAbility* Ability = Cast<UXIGameplayAbility>(Spec.GetContext().GetAbilityInstance_NotReplicated());

	if (!Ability)
	{
		return 0.0f;
	}
	
	return Ability->GetCost();
}