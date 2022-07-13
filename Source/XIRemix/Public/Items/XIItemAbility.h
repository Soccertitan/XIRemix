// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/XIItem.h"
#include "DataAssets/XIAbilityData.h"
#include "XIItemAbility.generated.h"

/**
 * Contains a reference to an XIAbility (passive or active). Serves as an interface to allow players to activate abilities.
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class XIREMIX_API UXIItemAbility : public UXIItem
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	UXIAbilityData* AbilityData;

	virtual FGameplayTagContainer GetCooldownTag() override;
	virtual float GetCost() override;
};
