// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAssets/XIAbilityData.h"
#include "XIJobAbilityData.generated.h"

USTRUCT(BlueprintType)
struct FXIJobAbilityDataItem
{
	GENERATED_BODY()

	// Level Required to be granted the ability
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Level;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UXIAbilityData* XIAbility;
};

/**
 * 
 */
UCLASS(BlueprintType)
class XIREMIX_API UXIJobAbilityData : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FXIJobAbilityDataItem> XIJobAbilityDataItem;
};
