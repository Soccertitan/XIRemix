// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XIAIControllerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UXIAIControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XIREMIX_API IXIAIControllerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// SetMainTarget is Implemented in C++
	virtual void SetMainTarget(AActor* TargetActor) PURE_VIRTUAL(IXAIControllerInterface::SetMainTarget(AActor* TargetActor););
};
