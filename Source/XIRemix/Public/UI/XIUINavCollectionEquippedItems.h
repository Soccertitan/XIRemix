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
	class UXIUINavComponentItemEquipSlot* BTNMain;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentItemEquipSlot* BTNSub;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentItemEquipSlot* BTNRange;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentItemEquipSlot* BTNAmmo;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentItemEquipSlot* BTNHead;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentItemEquipSlot* BTNNeck;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentItemEquipSlot* BTNEar1;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentItemEquipSlot* BTNEar2;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentItemEquipSlot* BTNBody;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentItemEquipSlot* BTNHands;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentItemEquipSlot* BTNRing1;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentItemEquipSlot* BTNRing2;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentItemEquipSlot* BTNBack;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentItemEquipSlot* BTNWaist;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentItemEquipSlot* BTNLegs;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquippedItems", meta = (BindWidget))
	class UXIUINavComponentItemEquipSlot* BTNFeet;

protected:

	UPROPERTY()
	class UXIEquipmentManagerComponent* EMC;

	UPROPERTY()
	FXIEquippedItems EquippedItems;

	UFUNCTION()
	void SetEquippedItems();

};
