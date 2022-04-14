// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XIEnums.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class XIREMIX_API UItem : public UObject
{
	GENERATED_BODY()

public:

	UItem();

	virtual class UWorld* GetWorld() const {return World;};

	UPROPERTY(Transient)
	class UWorld* World;

	/** Item Name */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FText Name;

	/** Item Description */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FText Description;

	/** The thumbnail for the item*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		class UTexture2D* Thumbnail;

	/** The item type used for UI*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		EItemType ItemType;

	/** Is item Exclusive to the owner */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		bool bIsExclusive;

	/**The Inventory that owns this item*/
	UPROPERTY()
	class UInventoryComponent* OwningInventory;

};
