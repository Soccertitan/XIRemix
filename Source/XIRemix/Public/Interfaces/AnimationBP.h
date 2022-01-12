// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XIEnums.h"
#include "AnimationBP.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAnimationBP : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XIREMIX_API IAnimationBP
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// GetDirection is Implemented in C++
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "XICharacter|AnimBP")
	float GetDirection();

	// GetSpeed is Implemented in C++
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "XICharacter|AnimBP")
	float GetSpeed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "XICharacter|AnimBP")
	void SetCombatStyle(ECombatStyle CombatStyle);
};
