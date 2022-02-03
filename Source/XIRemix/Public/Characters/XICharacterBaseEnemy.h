// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/XICharacterBase.h"
#include "XIEnums.h"
#include "AI/XIAggroComponent.h"
#include "XICharacterBaseEnemy.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API AXICharacterBaseEnemy : public AXICharacterBase
{
	GENERATED_BODY()
	
	AXICharacterBaseEnemy(const class FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = XIAggro, meta = (AllowPrivateAccess = "true"))
	class UXIAggroComponent* XIAggroComponent;

	// Only called on the Server. Calls before Server's AcknowledgePossession.
	virtual void PossessedBy(AController* NewController) override;

protected:
	
	UPROPERTY()
	class UAttributeSetEnemy* AttributeSetEnemy;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Client only
	virtual void OnRep_PlayerState() override;	
};
