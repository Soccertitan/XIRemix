// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "XIRemix/XIRemix.h"
#include "GameplayAbilityGlobal.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UGameplayAbilityGlobal : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UGameplayAbilityGlobal();

	// Abilities with this set will automatically activate when the input is pressed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EXIAbilityInputID AbilityInputID = EXIAbilityInputID::None;

	// Value to associate an ability with an slot without tying it to an automatically activated input.
	// Passive abilities won't be tied to an input so we need a way to generically associate abilities with slots.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EXIAbilityInputID AbilityID = EXIAbilityInputID::None;

	// Tells an ability to activate immediately when its granted. Used for passive abilities and abilities forced on others.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
	bool ActivateAbilityOnGranted = false;
};
