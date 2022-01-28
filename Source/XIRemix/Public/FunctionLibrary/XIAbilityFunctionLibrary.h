// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Abilities/XIAbilityTypes.h"
#include "XIAbilityFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS(meta=(ScriptName="XIAbilityFunctionLibrary"))
class XIREMIX_API UXIAbilityFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/** Returns the Targeted Actor if it was in Range to be hit. */
	UFUNCTION(BlueprintPure, Category = "XIAbility|TargetData")
	static const FGameplayAbilitySingleTargetData& GetGameplayAbilitySingleTargetData(const FGameplayAbilityTargetDataHandle& TargetData, int32 Index);
};
