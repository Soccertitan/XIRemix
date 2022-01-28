// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "XIEnums.h"
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
	UFUNCTION(BlueprintPure, Category = "XIRemix|Combat")
	static bool CheckTargetWithinRange (AActor* OwnerActor, AActor* TargetActor, float AngleInDegrees, float Range);

	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIRemix|Combat")
	static AActor* GetMainTarget (AActor* OwnerActor);

	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIRemix|Combat")
	static AActor* GetSubTarget (AActor* OwnerActor);

	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIRemix|Combat")
	static UAnimMontage* GetAutoAttackMontage(AActor* OwnerActor);

	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIRemix|Combat")
	static FText GetCharacterName (AActor* OwnerActor);

	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIRemix|Combat")
	static EXITeam GetXITeam (AActor* OwnerActor);

	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIRemix|Combat")
	static EXITeamAttitude GetAttitudeTowardsActor (AActor* OwnerActor, AActor* TargetActor);
};
