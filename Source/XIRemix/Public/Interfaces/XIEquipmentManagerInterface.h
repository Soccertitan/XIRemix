// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XIEquipmentManagerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UXIEquipmentManagerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XIREMIX_API IXIEquipmentManagerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual class UXIEquipmentManagerComponent* GetXIEquipmentManagerComponent() const PURE_VIRTUAL(IXIEquipmentManagerInterface::GetXIEquipmentManagerComponent(), return nullptr;);
};
