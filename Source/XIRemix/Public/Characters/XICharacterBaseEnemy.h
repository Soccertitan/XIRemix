// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/XICharacterBase.h"
#include "XIEnums.h"
#include "Components/XIAggroComponent.h"
#include "Components/XIThreatTableComponent.h"
#include "Interfaces/XIAggroInterface.h"
#include "XICharacterBaseEnemy.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API AXICharacterBaseEnemy : public AXICharacterBase, public IXIAggroInterface
{
	GENERATED_BODY()
	
	AXICharacterBaseEnemy(const class FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "XIAggro", meta = (AllowPrivateAccess = "true"))
	class UXIAggroComponent* XIAggroComponent;

	// Only called on the Server. Calls before Server's AcknowledgePossession.
	virtual void PossessedBy(AController* NewController) override;

public:
	//Implements IXIAggroInterface
	virtual class UXIAggroComponent* GetXIAggroComponent() const override;

	//Implements IXICharacterInterface
	virtual float GetCharacterLevel() const override;

	FORCEINLINE void SetCharacterLevel(float InLevel) {Level = InLevel;};

protected:
	
	UPROPERTY()
	class UAttributeSetEnemy* AttributeSetEnemy;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "XICharacter", meta = (ExposeOnSpawn = true))
	float Level = 1;

	virtual void InitializeAttributes() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Client only
	virtual void OnRep_PlayerState() override;

	virtual void Die() override;
};
