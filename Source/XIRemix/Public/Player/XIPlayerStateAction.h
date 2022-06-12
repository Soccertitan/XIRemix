// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "XIEnums.h"
#include "XIPlayerStateAction.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API AXIPlayerStateAction : public APlayerState
{
	GENERATED_BODY()
	
public:

	AXIPlayerStateAction();

	UFUNCTION(BlueprintPure, Category = "Inventory")
	UXIInventoryComponent* GetInventory(EInventoryType InventoryType);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	class UXIInventoryComponent* InventoryMelee;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	class UXIInventoryComponent* InventoryRanged;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	class UXIInventoryComponent* InventoryArmor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	class UXIInventoryComponent* InventoryAccessories;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	class UXIInventoryComponent* InventoryConsumables;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	class UXIInventoryComponent* InventoryMaterials;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	class UXIInventoryComponent* InventoryKeyItems;
};
