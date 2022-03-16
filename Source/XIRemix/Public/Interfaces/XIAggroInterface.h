// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XIAggroInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UXIAggroInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XIREMIX_API IXIAggroInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual class UXIAggroComponent* GetXIAggroComponent() const PURE_VIRTUAL(IXIAggroInterface::GetXIAggroComponent(), return nullptr;);
};
