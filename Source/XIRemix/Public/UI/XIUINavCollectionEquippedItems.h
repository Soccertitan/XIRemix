// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/XIUINavCollection.h"
#include "Components/XIEquipmentManagerComponent.h"
#include "XIUINavCollectionEquippedItems.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup = UI)
class XIREMIX_API UXIUINavCollectionEquippedItems : public UXIUINavCollection
{
	GENERATED_BODY()
	
public:

	UXIUINavCollectionEquippedItems(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void InitializeEquippedItems(class UXIEquipmentManagerComponent* EquipmentComponent);

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentEquipSlot* BTNMain;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentEquipSlot* BTNSub;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentEquipSlot* BTNRange;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentEquipSlot* BTNAmmo;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentEquipSlot* BTNHead;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentEquipSlot* BTNNeck;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentEquipSlot* BTNEar1;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentEquipSlot* BTNEar2;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentEquipSlot* BTNBody;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentEquipSlot* BTNHands;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentEquipSlot* BTNRing1;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentEquipSlot* BTNRing2;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentEquipSlot* BTNBack;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentEquipSlot* BTNWaist;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentEquipSlot* BTNLegs;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentEquipSlot* BTNFeet;

protected:

	UPROPERTY()
	class UXIEquipmentManagerComponent* EMC;

	UPROPERTY()
	FXIEquippedItems EquippedItems;

	UFUNCTION()
	void SetEquippedItems();

};
