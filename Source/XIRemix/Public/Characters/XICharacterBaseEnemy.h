// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/XICharacterBase.h"
#include "XIEnums.h"
#include "AI/XIAggroComponent.h"
#include "AI/XIThreatTableComponent.h"
#include "Interfaces/XIEnemyCharacterInterface.h"
#include "XICharacterBaseEnemy.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API AXICharacterBaseEnemy : public AXICharacterBase, public IXIEnemyCharacterInterface
{
	GENERATED_BODY()
	
	AXICharacterBaseEnemy(const class FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "XIAggro", meta = (AllowPrivateAccess = "true"))
	class UXIAggroComponent* XIAggroComponent;

	// Only called on the Server. Calls before Server's AcknowledgePossession.
	virtual void PossessedBy(AController* NewController) override;

public:
	//Implements IXIEnemyCharacterInterface
	virtual class UXIAggroComponent* GetXIAggroComponent() const override;

protected:
	
	UPROPERTY()
	class UAttributeSetEnemy* AttributeSetEnemy;

	UPROPERTY()
	class UXIThreatTableComponent* XIThreatTableComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "XICharacter", meta = (ExposeOnSpawn = true))
	float Level = 1;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Client only
	virtual void OnRep_PlayerState() override;	
};
