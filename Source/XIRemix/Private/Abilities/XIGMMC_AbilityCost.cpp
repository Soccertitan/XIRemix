// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/XIGMMC_AbilityCost.h"
#include "Interfaces/XIGameplayAbilityInterface.h"

float UXIGMMC_AbilityCost::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const IXIGameplayAbilityInterface* GAInt = Cast<IXIGameplayAbilityInterface>(Spec.GetContext().GetAbilityInstance_NotReplicated());

	if (!GAInt)
	{
		return 0.0f;
	}
	
	return GAInt->GetCost();
}