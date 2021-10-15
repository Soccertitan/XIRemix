// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/PlayerControllerTeam.h"

APlayerControllerTeam::APlayerControllerTeam()
{
  PrimaryActorTick.bCanEverTick = true;
  TeamId = FGenericTeamId(2);
}

FGenericTeamId APlayerControllerTeam::GetGenericTeamId() const
{
  return TeamId;
}

// ETeamAttitude::Type APlayerControllerTeam::GetTeamAttitudeTowards(const AActor& Other) const
// {
//   // DEFAULT BEHAVIOR---------------------------------------------------
//   if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
//   {
//     return Super::GetTeamAttitudeTowards(*OtherPawn->GetController());
//   }

// }