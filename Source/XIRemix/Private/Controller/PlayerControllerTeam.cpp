// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/PlayerControllerTeam.h"

APlayerControllerTeam::APlayerControllerTeam()
{
  PrimaryActorTick.bCanEverTick = true;
  TeamId = FGenericTeamId(10);
}

FGenericTeamId APlayerControllerTeam::GetGenericTeamId() const
{
  return TeamId;
}