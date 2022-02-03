// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Interfaces/XIAIControllerInterface.h"
#include "XIAIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API AXIAIControllerBase : public AAIController, public IXIAIControllerInterface
{
	GENERATED_BODY()
	
public:

	//XIAIControllerInterface Functions
	virtual void SetMainTarget(AActor* TargetActor) override;
};
