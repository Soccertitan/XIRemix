// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "PlayerControllerTeam.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API APlayerControllerTeam : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
  APlayerControllerTeam();

private: 
  // Implement The Generic Team Interface 
  FGenericTeamId TeamId;
  FGenericTeamId GetGenericTeamId() const;

  // ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
};
