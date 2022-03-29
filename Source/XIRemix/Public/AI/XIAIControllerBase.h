// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Interfaces/XIGameplayControllerInterface.h"
#include "XIAIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API AXIAIControllerBase : public AAIController, public IXIGameplayControllerInterface
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "XIPCInt")
	void SetIsMoveable(bool bIsMoveable); void SetIsMoveable_Implementation(bool bIsMoveable) override;

protected:

	UPROPERTY(BlueprintReadWrite)
	bool bCanMove = true;

};
