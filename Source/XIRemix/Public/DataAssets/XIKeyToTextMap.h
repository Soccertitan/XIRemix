// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTags.h"
#include "XIEnums.h"
#include "XIKeyToTextMap.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class XIREMIX_API UXIKeyToTextMap : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FGameplayTag, FText> TagToText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EEquipSlot, FText> EquipSlotToText;
};
