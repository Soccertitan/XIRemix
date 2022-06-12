// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/XIUserWidget.h"
#include "DataAssets/XIKeyToTextMap.h"
#include "DataAssets/XIJobTagCollection.h"
#include "Items/XIItemEquipment.h"
#include "XIItemDetailsWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup = UI)
class XIREMIX_API UXIItemDetailsWidget : public UXIUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "XIItemDetailsWidget")
	void SetupItemDetailsWidget(UXIItem* Item);

	UPROPERTY(BlueprintReadOnly, Category = "XIItemDetailsWidget", meta = (BindWidget))
	class UTextBlock* ItemNameText;

	UPROPERTY(BlueprintReadOnly, Category = "XIItemDetailsWidget", meta = (BindWidget))
	class UTextBlock* ItemDescriptionText;

	UPROPERTY(BlueprintReadOnly, Category = "XIItemDetailsWidget", meta = (BindWidget))
	class UImage* ItemThumbnail;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XIItemDetailsWidget")
	UXIKeyToTextMap* TextMap;

	FText GetWeaponText(UXIItem* Item);
	FText GetArmorText(UXIItem* Item);
	FText GetJobRequirementText(UXIJobTagCollection* JobTagCollection);
	FText GetAttributeText(TArray<FXIItemAttributes> Attributes);
};