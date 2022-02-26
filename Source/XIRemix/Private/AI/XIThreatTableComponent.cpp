// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/XIThreatTableComponent.h"

// Sets default values for this component's properties
UXIThreatTableComponent::UXIThreatTableComponent()
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 1.0f;
}


// Called when the game starts
void UXIThreatTableComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Adds threat for the specified target actor.
void UXIThreatTableComponent::AddEnmity(AActor* TargetActor, float InVolatileEnmity, float InCumulativeEnmity, bool bOverrideEnmity)
{
	if(!TargetActor)
	{
		return;
	}
	
	FThreatTableStruct Threat;
	Threat.Actor = TargetActor;
	Threat.VolatileEnmity = FMath::Clamp(InVolatileEnmity, ClampMin, ClampMax);
	Threat.CumulativeEnmity = FMath::Clamp(InCumulativeEnmity, ClampMin, ClampMax);

	if(!ThreatTable.IsValidIndex(0))
	{
		//First Aggro Bonus Enmity
		Threat.CumulativeEnmity += 200;

		ThreatTable.AddUnique(Threat);
		HighestThreatActor = TargetActor;
		SetComponentTickEnabled(true);
		OnHighestThreat.Broadcast(TargetActor);
	}
	else
	{
		for(FThreatTableStruct &ThreatEntry : ThreatTable)
		{
			if (ThreatEntry.Actor == TargetActor)
			{
				if(bOverrideEnmity)
				{
					ThreatEntry.VolatileEnmity = FMath::Clamp(InVolatileEnmity, ClampMin, ClampMax);
					ThreatEntry.CumulativeEnmity = FMath::Clamp(InCumulativeEnmity, ClampMin, ClampMax);
					CheckHighestEnmity();
					return;
				}
				else
				{
					ThreatEntry.VolatileEnmity = FMath::Clamp(ThreatEntry.VolatileEnmity + InVolatileEnmity, ClampMin, ClampMax);
					ThreatEntry.CumulativeEnmity = FMath::Clamp(ThreatEntry.CumulativeEnmity + InCumulativeEnmity, ClampMin, ClampMax);
					CheckHighestEnmity();
					return;
				}
			}
		}

		ThreatTable.AddUnique(Threat);
		CheckHighestEnmity();
		return;
	}
}

//Checks the highest threat actor and broadcasts an event when the highest threat actor changes.
void UXIThreatTableComponent::CheckHighestEnmity()
{
	if(!ThreatTable.IsValidIndex(0))
	{
		OnHighestThreat.Broadcast(nullptr);
	}

	float ThreatAmount = 0;
	float ThreatComparison;
	AActor* TargetActor = nullptr;

	for(FThreatTableStruct ThreatEntry : ThreatTable)
	{
		ThreatComparison = ThreatEntry.VolatileEnmity + ThreatEntry.CumulativeEnmity;
		if (ThreatComparison > ThreatAmount)
		{
			ThreatAmount = ThreatComparison;
			TargetActor = ThreatEntry.Actor;
		}
	}

	if(!(TargetActor == HighestThreatActor))
	{
		HighestThreatActor = TargetActor;
		OnHighestThreat.Broadcast(TargetActor);
	}
}

void UXIThreatTableComponent::RemoveTargetActor(AActor* TargetActor)
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
		}
	}
	CheckHighestEnmity();
}

void UXIThreatTableComponent::ApplyDamageEnmity(AActor* TargetActor, float EnemyLevel, float Damage, float EnmityRate)
{
	// **
	// Formula for calculating CumulativeEnmity [CE] and VolatileEnmity [VE] from dealing damage.
	// [CE Modifier] = 80 / {floor(31 * [EnemyLevel] / 50) + 6 }
	// [EnemyLvScaleFactor] = -0.01428 * [EnemyLevel] + 1.71428
	// [CE] = [CE Modifier] * [Damage] * EnmityRate * [EnemyLvScaleFactor]
	// [VE] = [CE] * 3
	// **
	
	float CEMod = 80 / (FMath::Floor(31 * EnemyLevel / 50) + 6);
	float EnemyLvScaleFactor = FMath::Clamp(-0.01428f * EnemyLevel + 1.71428f, 0.3f, 1.0f);

	float CE = CEMod * Damage * EnmityRate * EnemyLvScaleFactor;
	float VE = CE * 3;
	
	AddEnmity(TargetActor, VE, CE, false);
}

void UXIThreatTableComponent::ApplyHealEnmity(AActor* TargetActor, float HealedTargetLevel, float Heal, float EnmityRate)
{
	//**
	// Formula using my best estimate from original FFXI data gathered.
	// [CE Modifier] = 40 / {floor(31 * [HealedTargetLevel] / 52) + 11}
	// [CE] = [CE Modifier] * [HealAmount]
	// [VE] = [CE] * 6
	//**

	float CEMod = 40 / (FMath::Floor(31 * HealedTargetLevel / 52) + 11);
	float CE = CEMod * Heal;
	float VE = CE * 6;

	AddEnmity(TargetActor, VE, CE, false);
}

void UXIThreatTableComponent::ApplyDamageTakenEnmity(AActor* TargetActor, float Damage, float TargetMaxHP)
{
	//**
	// Forumula for calculating Cumulative Enmity lost when taking damage.
	// [CE Lost] = 1800 * [Damage] / [TargetMaxHP]
	// Will need to revamp this function to include another parameter to take in a percentage to reduce enmity lost.
	//**

	float CELost = -(1800 * Damage / FMath::Max(TargetMaxHP, 1.f));

	AddEnmity(TargetActor, 0, CELost, false);
}

bool UXIThreatTableComponent::GetTargetActorEnmity(AActor* TargetActor, float& OutVolatileEnmity, float& OutCumulativeEnmity) const
{
	if (!TargetActor | !ThreatTable.IsValidIndex(0))
	{
		return false;
	}

	for (FThreatTableStruct ThreatEntry : ThreatTable)
	{
		if (ThreatEntry.Actor == TargetActor)
		{
			OutCumulativeEnmity = ThreatEntry.CumulativeEnmity;
			OutVolatileEnmity = ThreatEntry.VolatileEnmity;
			return true;
		}
	}
	return false;
}

void UXIThreatTableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!ThreatTable.IsValidIndex(0))
	{
		SetComponentTickEnabled(false);
		return;
	}

	for (FThreatTableStruct &ThreatEntry : ThreatTable)
	{
		ThreatEntry.VolatileEnmity = FMath::Clamp(ThreatEntry.VolatileEnmity - VolatileEnimtyDecayRate, ClampMin, ClampMax);
	}

	CheckHighestEnmity();
}