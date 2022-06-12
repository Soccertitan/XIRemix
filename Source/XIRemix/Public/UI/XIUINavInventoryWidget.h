// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/XIUINavWidget.h"
#include "Player/XIPlayerStateAction.h"
#include "Components/XIInventoryComponent.h"
#include "XIEnums.h"
#include "UI/Components/XIUINavComponentItemSlot.h"
#include "XIUINavInventoryWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FXIOnItemSelected, class UXIItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FXIOnItemHover, class UXIItem*, Item);

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup = UI)
class XIREMIX_API UXIUINavInventoryWidget : public UXIUINavWidget
{
	GENERATED_BODY()

public:

	UXIUINavInventoryWidget();

	// Use this event to start populating the widget with default inventory items.
	UFUNCTION(BlueprintImplementableEvent, Category = "XIUINavInventoryWidget")
	void ReadyToGenerateInventory();

	// This event is called after GenerateItemsArray. The number of items returned is equal to NumberOfItemsToDisplay.
	UFUNCTION(BlueprintImplementableEvent, Category = "XIUINavInventoryWidget")
	void OnItemsReady(const TArray<UXIItem*>& Items);

	// This event is called after a successful attempt to go to the previous or next item page in the same inventory container.
	UFUNCTION(BlueprintImplementableEvent, Category = "XIUINavInventoryWidget")
	void OnSwitchItemsPage(const TArray<UXIItem*>& Items);

	// Gets all the items that were generated when running GenerateItemsArray function.
	UFUNCTION(BlueprintCallable, Category = "XIUINavInventoryWidget")
	FORCEINLINE TArray<UXIItem*> GetGeneratedItems() const {return ItemsRef;};

	//Generates an array of items from the inventory. Calls OnItemsReady and returns the number of items specified NumberOfItemsToDisplay value.
	UFUNCTION(BlueprintCallable, Category = "XIUINavInventoryWidget")
	void GenerateItemsArray(EInventoryType InventoryType);

	// Goes to the next item page. Returns false if unable to.
	UFUNCTION(BlueprintCallable, Category = "XIUINavInventoryWidget")
	void NextItemPage();

	// Goes to the previous item page. Returns false if unable to.
	UFUNCTION(BlueprintCallable, Category = "XIUINavInventoryWidget")
	void PreviousItemPage();

	UPROPERTY(BlueprintAssignable, Category = "XIUINavInventoryWidget")
	FXIOnItemSelected XIOnItemSelected;

	UPROPERTY(BlueprintAssignable, Category = "XIUINavInventoryWidget")
	FXIOnItemHover XIOnItemHover;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "XIUINavInventoryWidget", meta = (BindWidget, OptionalWidget = true))
	UTextBlock* InventoryCapacityText;

	UPROPERTY(BlueprintReadOnly, Category = "XIUINavInventoryWidget", meta = (BindWidget, OptionalWidget = true))
	UTextBlock* ItemCountText;

	UPROPERTY(BlueprintReadOnly, Category = "XIUINavInventoryWidget", meta = (BindWidget, OptionalWidget = true))
	UTextBlock* CurrentItemPageText;

	UPROPERTY(BlueprintReadOnly, Category = "XIUINavInventoryWidget", meta = (BindWidget, OptionalWidget = true))
	UTextBlock* LastItemPageText;

	UPROPERTY()
	AXIPlayerStateAction* PlayerState;

	UPROPERTY()
	UXIInventoryComponent* InventoryComponentRef;

	UPROPERTY()
	TArray<UXIItem*> ItemsRef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XIUINavInventoryWidget")
	int32 NumberOfItemsToDisplay;

	// Variables used to loop through the array
	int32 FirstIndex;
	int32 LastIndex;
	int32 CurrentItemPage;

	UFUNCTION(BlueprintCallable, Category = "XIUINavInventoryWidget")
	void BindButtonsToEventDispatcher(TArray<UXIUINavComponentItemSlot*> ItemButtons);

	UFUNCTION()
	void OnButtonClicked(class UXIUINavComponent* Button);

	UFUNCTION()
	void OnButtonHover(class UXIUINavComponent* Button);

	//Sets all the text for the optional widgets. Use SetCurrentItemPageText() for that particular textblock.
	void SetOptionalWidgetText();
	void SetCurrentItemPageText();

	virtual void NativeOnInitialized() override;
};
