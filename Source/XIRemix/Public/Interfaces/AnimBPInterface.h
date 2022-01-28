// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XIEnums.h"
#include "AnimBPInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAnimBPInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XIREMIX_API IAnimBPInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// GetDirection is Implemented in C++
	virtual float GetDirection() PURE_VIRTUAL(IAnimBPInterface::GetDirection(), return 0;);

	// GetSpeed is Implemented in C++
	virtual float GetSpeed() PURE_VIRTUAL(IAnimBPInterface::GetSpeed(), return 0;);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "XICharacter|AnimBP")
	void SetCombatStyle(ECombatStyle CombatStyle);
};
