// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/XIAIControllerBase.h"
#include "Components/XIThreatTableComponent.h"
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

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XIAIControllerEnemy")
	UBehaviorTree* BTAsset;

	// An infinite GE that applies the tag "State.Gameplay.WeaponsOut"
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XIAIControllerEnemy")
	TSubclassOf<class UGameplayEffect> WeaponsOutGE; 

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UXIThreatTableComponent* XIThreatTableComponent;

	UPROPERTY(BlueprintReadOnly, Category = "XIAIControllerEnemy")
	class UXIAggroComponent* XIAggroComponentRef;

	UPROPERTY(BlueprintReadOnly, Category = "XIAIControllerEnemy")
	class AXICharacterBaseEnemy* ControlledPawn;

	UPROPERTY(BlueprintReadOnly, Category = "XIAIControllerEnemy")
	class AXICharacterBase* TargetedActor;

	UPROPERTY(BlueprintReadOnly, Category = "XIAIControllerEnemy")
	bool bIsAlive;

	UPROPERTY(BlueprintReadOnly, Category = "XIAIControllerEnemy")
	class UAbilitySystemComponent* ASC;

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void OnControlledActorDied(AActor* Actor);
	UFUNCTION()
	void OnActorDetected(AActor* Actor);
	UFUNCTION()
	void OnHighestThreat(AActor* Actor);
	UFUNCTION()
	void SetMainTarget(AActor* Actor);
	UFUNCTION()
	void OnTargetDied(AActor* Actor);

};
