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
	UInventoryComponent* GetInventory(EItemType ItemType);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	class UInventoryComponent* InventoryMelee;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	class UInventoryComponent* InventoryRanged;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	class UInventoryComponent* InventoryArmor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	class UInventoryComponent* InventoryAccessories;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	class UInventoryComponent* InventoryConsumables;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	class UInventoryComponent* InventoryMaterials;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	class UInventoryComponent* InventoryKeyItems;
};
