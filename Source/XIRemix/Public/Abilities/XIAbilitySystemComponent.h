// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "XIAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReceivedCombatExpDelegate, float, ExpGained);

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	bool CharacterAbilitiesGiven = false;
	bool StartupEffectsApplied = false;

	FReceivedCombatExpDelegate ReceivedCombatExp;

	virtual void ReceiveCombatExp(float ExpGained);

	virtual void CheckLevelUp();
};
