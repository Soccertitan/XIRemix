// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "XIRemix.h"
#include "GlobalGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UGlobalGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:

	UGlobalGameplayAbility();

	// Abilities with this set will automatically activate when the input is pressed.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EGASAbilityInput AbilityInput = EGASAbilityInput::None;
};

