// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/XIAIControllerBase.h"
#include "AI/XIThreatTableComponent.h"
#include "Interfaces/XIThreatTableInterface.h"
#include "XIAIControllerEnemy.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API AXIAIControllerEnemy : public AXIAIControllerBase, public IXIThreatTableInterface
{
	GENERATED_BODY()

public:
	AXIAIControllerEnemy();

	//Implements IXIThreatTableInterface
	virtual class UXIThreatTableComponent* GetXIThreatTableComponent() const override;

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UXIThreatTableComponent* XIThreatTableComponent;

};
