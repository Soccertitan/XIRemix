// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/XIThreatTableComponent.h"

// Sets default values for this component's properties
UXIThreatTableComponent::UXIThreatTableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}


// Called when the game starts
void UXIThreatTableComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Adds threat for the specified target actor.
void UXIThreatTableComponent::AddThreat(AActor* TargetActor, float ThreatAmount)
{
	if(!TargetActor)
	{
		return;
	}
	
	if(!ThreatTable.IsValidIndex(0))
	{
		FThreatTableStruct Threat;
		Threat.Actor = TargetActor;
		Threat.ThreatLevel = ThreatAmount;

		ThreatTable.Add(Threat);

		HighestThreatActor = TargetActor;
		OnHighestThreat.Broadcast(TargetActor);
	}
	else
	{
		for(FThreatTableStruct &ThreatEntry : ThreatTable)
		{
			if (ThreatEntry.Actor == TargetActor)
			{
				ThreatEntry.ThreatLevel += ThreatAmount;
				CheckHighestThreat();
				return;
			}
		}

		FThreatTableStruct Threat;
		Threat.Actor = TargetActor;
		Threat.ThreatLevel = ThreatAmount;

		ThreatTable.Add(Threat);
		CheckHighestThreat();
		return;
	}
}

//Checks the highest threat actor and broadcasts an event when the highest threat actor changes.
void UXIThreatTableComponent::CheckHighestThreat()
{
	if(!ThreatTable.IsValidIndex(0))
	{
		OnHighestThreat.Broadcast(nullptr);
	}

	float ThreatAmount = 0;
	AActor* TargetActor = nullptr;

	for(FThreatTableStruct ThreatEntry : ThreatTable)
	{
		if (ThreatEntry.ThreatLevel > ThreatAmount)
		{
			ThreatAmount = ThreatEntry.ThreatLevel;
			TargetActor = ThreatEntry.Actor;
		}
	}

	if(!(TargetActor == HighestThreatActor))
	{
		HighestThreatActor = TargetActor;
		OnHighestThreat.Broadcast(TargetActor);
	}
}

void UXIThreatTableComponent::RemoveThreatActor(AActor* TargetActor)
{
	if(!(ThreatTable.IsValidIndex(0)) || !TargetActor)
	{
		return;
	}

	for(FThreatTableStruct ThreatEntry : ThreatTable)
	{
		if (ThreatEntry.Actor == TargetActor)
		{
			ThreatTable.Remove(ThreatEntry);
			return;
		}
	}
}