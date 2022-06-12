// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Components/XIUINavComponent.h"
#include "Items/XIItem.h"
#include "XIEnums.h"
#include "XIUINavComponentItemSlot.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup = UI)
class XIREMIX_API UXIUINavComponentItemSlot : public UXIUINavComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "XIUINavComponentItemSlot")
	FORCEINLINE UXIItem* GetItem() const {return ItemRef;};

	UFUNCTION(BlueprintCallable, Category = "XIUINavComponentItemSlot")
	virtual void SetItem(UXIItem* Item);

protected:

	UPROPERTY(BlueprintReadOnly, Category = "XIUINavComponentItemSlot")
	UXIItem* ItemRef;

	UPROPERTY(BlueprintReadOnly, Category = "XIUINavComponentItemSlot", meta = (BindWidget, OptionalWidget = true))
	class UImage* ItemThumbnail;

	UPROPERTY(BlueprintReadOnly, Category = "XIUINavComponentItemSlot", meta = (BindWidget, OptionalWidget = true))
	class UTextBlock* ItemName;

	// A Null Thumbnail image will hide the image component.
	void SetItemThumbnail(UTexture2D* Thumbnail);

	void SetItemName(FText Name);
};
