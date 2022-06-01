// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "XIEnums.h"
#include "XIGameplayFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIGameplayFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Checks if the TargetActor is in Range and within Line of Sight
	UFUNCTION(BlueprintPure, Category = "XIGameplayFunctionLibrary")
	static bool CheckTargetWithinRange (AActor* OwnerActor, AActor* TargetActor, float AngleInDegrees, float Range);

	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIGameplayFunctionLibrary")
	static AActor* GetMainTarget (AActor* OwnerActor);

	//XICharacter Interface Function
	UFUNCTION(BlueprintCallable, Category = "XIGameplayFunctionLibrary")
	static void SetMainTarget (AActor* OwnerActor, AActor* TargetActor);

	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIGameplayFunctionLibrary")
	static AActor* GetSubTarget (AActor* OwnerActor);

	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIGameplayFunctionLibrary")
	static FText GetCharacterName (AActor* OwnerActor);

	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIGameplayFunctionLibrary")
	static EXITeam GetXITeam (AActor* OwnerActor);

	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIGameplayFunctionLibrary")
	static EXITeamAttitude GetAttitudeTowardsActor (AActor* OwnerActor, AActor* TargetActor);

	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIGameplayFunctionLibrary")
	static float GetCapsuleRadius (AActor* OwnerActor);

	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIGameplayFunctionLibrary")
	static float GetCharacterLevel(AActor* OwnerActor);

	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIGameplayFunctionLibrary")
	static UAnimMontage* GetAutoAttackMontage(AActor* OwnerActor);

	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIGameplayFunctionLibrary")
	static class UXICharacterAnimMontages* GetXICharacterAnimMontages(AActor* OwnerActor);

	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIGameplayFunctionLibrary")
	static bool IsAlive(AActor* OwnerActor);

	//XICharacter Interface Function
	UFUNCTION(BlueprintPure, Category = "XIGameplayFunctionLibrary")
	static class AXICharacterBase* GetXICharacterBase(AActor* OwnerActor);

	//XIAI Controller Interface Function
	UFUNCTION(BlueprintPure, Category = "XIGameplayFunctionLibrary")
	static class UXIThreatTableComponent* GetXIThreatTableComponent(AController* AIController);

	//XI Aggro Component Interface Function
	UFUNCTION(BlueprintPure, Category = "XIGameplayFunctionLibrary")
	static class UXIAggroComponent* GetXIAggroComponent(AActor* OwnerActor);

	//XI Target System Component Interface Function
	UFUNCTION(BlueprintPure, Category = "XIGameplayFunctionLibrary")
	static class UXITargetSystemComponent* GetXITargetSystemComponent(AActor* OwnerActor);

	//XI Equipment System Component Interface Function
	UFUNCTION(BlueprintPure, Category = "XIGameplayFunctionLibrary")
	static class UXIEquipmentManagerComponent* GetXIEquipmentManagerComponent(AActor* OwnerActor);	
};
