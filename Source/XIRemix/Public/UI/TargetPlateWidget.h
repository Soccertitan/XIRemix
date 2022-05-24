// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TargetPlateWidget.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UTargetPlateWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "TargetPlate")
	float GetHitPointsPercent();

	UPROPERTY(BlueprintReadWrite, Category = "TargetPlate", meta = (ExposeOnSpawn))
	AActor* TargetedActor;

protected:

	UPROPERTY(BlueprintReadWrite, Category = "TargetPlate")
	float HitPoints;

	UPROPERTY(BlueprintReadWrite, Category = "TargetPlate")
	float HitPointsMax;

};
