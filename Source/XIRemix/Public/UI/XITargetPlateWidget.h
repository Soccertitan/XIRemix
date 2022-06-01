// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/XIUserWidget.h"
#include "XITargetPlateWidget.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXITargetPlateWidget : public UXIUserWidget
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
