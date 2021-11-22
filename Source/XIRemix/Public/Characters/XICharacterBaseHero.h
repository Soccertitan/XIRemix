// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/XICharacterBase.h"
#include "XICharacterBaseHero.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API AXICharacterBaseHero : public AXICharacterBase
{
	GENERATED_BODY()

public:
	AXICharacterBaseHero(const class FObjectInitializer& ObjectInitializer);

	// Only called on the Server. Calls before Server's AcknowledgePossession.
	virtual void PossessedBy(AController* NewController) override;

	// /**
	// * Getters for attributes from AttributeSetHero
	// **/
	UFUNCTION(BlueprintCallable, Category = "XICharacter|Attributes|Jobs")
	float GetWarriorLevel() const;

protected:
	
	UPROPERTY()
	class UAttributeSetHero* AttributeSetHero;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Client only
	virtual void OnRep_PlayerState() override;	
};
