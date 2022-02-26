// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XITargetSystemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UXITargetSystemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XIREMIX_API IXITargetSystemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual class UXITargetSystemComponent* GetXITargetSystemComponent() const PURE_VIRTUAL(IXITargetSystemInterface::GetXITargetSystemComponent(), return nullptr;);
};
