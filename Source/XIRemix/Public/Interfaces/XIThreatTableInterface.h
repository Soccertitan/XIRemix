// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XIThreatTableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UXIThreatTableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XIREMIX_API IXIThreatTableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual class UXIThreatTableComponent* GetXIThreatTableComponent() const PURE_VIRTUAL(IXIThreatTableInterface::GetXIThreatTableComponent(), return nullptr;);
};
