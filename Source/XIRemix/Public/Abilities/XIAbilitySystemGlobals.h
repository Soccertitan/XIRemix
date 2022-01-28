// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "XIAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

public:
	UXIAbilitySystemGlobals();

	static UXIAbilitySystemGlobals& XIGet()
	{
		return dynamic_cast<UXIAbilitySystemGlobals&>(Get());
	}

};
