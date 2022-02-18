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
	static FText GetCharacterName (AActor* OwnerActor);

	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIRemix|Combat")
	static EXITeam GetXITeam (AActor* OwnerActor);

	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIRemix|Combat")
	static EXITeamAttitude GetAttitudeTowardsActor (AActor* OwnerActor, AActor* TargetActor);

	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIRemix|Character")
	static float GetCapsuleRadius (AActor* OwnerActor);

	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIRemix|Combat|Animation")
	static UAnimMontage* GetAutoAttackMontage(AActor* OwnerActor);

	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIRemix|Combat|Animation")
	static UAnimMontage* GetBlackMagicMontage(AActor* OwnerActor);
	
	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIRemix|Combat|Animation")
	static UAnimMontage* GetWhiteMagicMontage(AActor* OwnerActor);
	
	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIRemix|Combat|Animation")
	static UAnimMontage* GetSummonerMagicMontage(AActor* OwnerActor);
	
	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIRemix|Combat|Animation")
	static UAnimMontage* GetNinjitsuMagicMontage(AActor* OwnerActor);
	
	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIRemix|Combat|Animation")
	static UAnimMontage* GetBlueMagicMontage(AActor* OwnerActor);
	
	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIRemix|Combat|Animation")
	static UAnimMontage* GetGeoMagicMontage(AActor* OwnerActor);
	
	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIRemix|Combat|Animation")
	static UAnimMontage* GetJobAbilityMontage(AActor* OwnerActor);
    
	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIRemix|Combat|Animation")
	static UAnimMontage* GetJobAbilityCombatMontage(AActor* OwnerActor);

	//XIEnemyCharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIRemix|Combat|AI")
	static UXIThreatTableComponent* GetXIThreatTableComponent(AActor* OwnerActor);
};
