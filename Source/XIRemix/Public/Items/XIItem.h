// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XIEnums.h"
#include "GameplayTagContainer.h"
#include "XIItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemModified);

/**
 * The base Item class.
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class XIREMIX_API UXIItem : public UObject
{
	GENERATED_BODY()
	
protected:

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const override;
	virtual bool IsSupportedForNetworking() const override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:

	UXIItem();

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(class AXICharacterBase* Character);

	virtual void Use(class AXICharacterBase* Character);
	virtual void AddedToInventory(class UXIInventoryComponent* Inventory);
	virtual FGameplayTagContainer GetCooldownTag();
	virtual float GetCost();

	UFUNCTION(BlueprintCallable, Category = "Item")
	void SetQuantity(const int32 NewQuantity);

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

	/** Whether or not this item can be stacked*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	bool bStackable;

	/** The maximum size that a stack of items can be*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (EditCondition = bStackable))
	int32 MaxStackSize;

	/** The amount of the item*/
	UPROPERTY(ReplicatedUsing = OnRep_Quantity, EditAnywhere, Category = "Item", meta = (UIMin = 1, EditCondition = bStackable))
	int32 Quantity;
	UFUNCTION()
	void OnRep_Quantity();

	UFUNCTION(BlueprintPure, Category = "Item")
	FORCEINLINE int32 GetQuantity() const { return Quantity; }

	UFUNCTION(BlueprintCallable, Category = "Item")
	FORCEINLINE bool IsStackFull() const { return Quantity >= MaxStackSize; }

	/** The item type used for UI*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	EItemType ItemType;

	/** Determines which inventory bucket this item should belong to. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	EInventoryType InventoryType;

	/** Is item Exclusive to the owner */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	bool bIsExclusive;

	/**The Inventory that owns this item*/
	UPROPERTY()
	class UXIInventoryComponent* OwningInventory;

	UPROPERTY(BlueprintAssignable)
	FOnItemModified OnItemModified;

	/**Used to efficiently replicate inventory items*/
	UPROPERTY()
	int32 RepKey;

	/**Mark the object as needing replication. We must call this internally after modifying any replicated properties*/
	void MarkDirtyForReplication();

};
