// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "XIAT_SingleTargetActor.generated.h"

/**
 * Sends the selected target and anim montage from the client to the server.
 */
UCLASS()
class XIREMIX_API AXIAT_SingleTargetActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:
	AXIAT_SingleTargetActor();

	virtual void StartTargeting(UGameplayAbility* Ability) override;

	virtual void ConfirmTargetingAndContinue() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "TargetedActor")
	AActor* TargetedActor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "AnimMontage")
	UAnimMontage* AnimMontage;
};
