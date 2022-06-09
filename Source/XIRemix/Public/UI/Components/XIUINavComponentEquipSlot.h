// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Components/XIUINavComponent.h"
#include "Items/XIItemEquipment.h"
#include "XIEnums.h"
#include "XIUINavComponentEquipSlot.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup = UI)
class XIREMIX_API UXIUINavComponentEquipSlot : public UXIUINavComponent
{
	GENERATED_BODY()

public:

	UXIUINavComponentEquipSlot(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintPure, Category = "XIUINavComponentEquipSlot")
	FORCEINLINE UXIItemEquipment* GetItem() const {return ItemRef;};
	UFUNCTION(BlueprintPure, Category = "XIUINavComponentEquipSlot")
	FORCEINLINE EEquipSlot GetEquipSlot() const {return EquipSlot;};

	void SetItem(UXIItemEquipment* Item);

protected:

	// A Null Thumbnail image will hide the image component.
	void SetItemThumbnail(UTexture2D* Thumbnail);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XIUINavComponentEquipSlot")
	EEquipSlot EquipSlot;

	//Sets the NavText to this value.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XIUINavComponentEquipSlot")
	FText EquipSlotText;

	UPROPERTY(BlueprintReadOnly, Category = "XIUINavComponentEquipSlot")
	UXIItemEquipment* ItemRef;

	UPROPERTY(BlueprintReadOnly, Category = "XIUINavComponentEquipSlot", meta = (BindWidget))
	class UImage* ItemThumbnail;

};
