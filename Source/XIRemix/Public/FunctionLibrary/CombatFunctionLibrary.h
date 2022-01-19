// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CombatFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UCombatFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	// Checks if the TargetActor is in Range and within Line of Sight
	UFUNCTION(BlueprintCallable, Category = "XIRemix|Combat")
	static bool CheckTargetWithinRange(AActor* OwnerActor, AActor* TargetActor, float AngleInDegrees, float Range);
};
