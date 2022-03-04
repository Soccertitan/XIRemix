// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "XIDataTables.generated.h"

USTRUCT(BlueprintType)
struct FXIAbilityData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BasePower;

	// The length an ability persits
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Duration;

	// The range of the ability to target.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Range;

	// The angle for Line of sight. 180 degrees is equal to 180 degrees to the right and left = 360 degrees.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Angle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CastTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Cost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Cooldown;

	// if bAreaEffect = true affect all targets within the radius of AreaEffectRange
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bAreaEffect;

	// The radius of the area of effect centered on the target.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AreaEffectRange;

	// if bFixedEnmity = true use CumlativeEnmity and VolatileEnmity values
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bFixedEnmity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CumulativeEnmity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float VolatileEnmity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Description;
};