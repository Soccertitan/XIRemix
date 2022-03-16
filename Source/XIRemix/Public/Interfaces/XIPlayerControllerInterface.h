// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XIPlayerControllerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UXIPlayerControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XIREMIX_API IXIPlayerControllerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual class UXIPlayerHUD* GetHUD() const PURE_VIRTUAL(IXIPlayerControllerInterface::GetHUD(), return nullptr;);
	virtual void CreateHUD() PURE_VIRTUAL(IXIPlayerControllerInterface::CreateHUD());
};
