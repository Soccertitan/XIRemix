// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "XIJobTagCollection.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class XIREMIX_API UXIJobTagCollection : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories="State.Job"))
	FGameplayTagContainer JobTags;
};
