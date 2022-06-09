// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/XIUINavWidget.h"
#include "XIEnums.h"
#include "XIUINavEquipmentWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup = UI)
class XIREMIX_API UXIUINavEquipmentWidget : public UXIUINavWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquipmentWidget", meta = (BindWidget))
	class UXIUINavCollectionEquippedItems* EquippedItemsCollection;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquipmentWidget", meta = (BindWidget))
	class UXICharacterStatusWidget* CharacterStatus;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquipmentWidget", meta = (BindWidget))
	class UXICharacterStatusWidget* CharacterStatusSub;

	UPROPERTY(BlueprintReadOnly, Category = "XIEquipmentWidget", meta = (BindWidget))
	class UXIItemDetailsWidget* ItemDetails;

	UFUNCTION()
	void OnEquipSlotHovered(UXIUINavComponent* XIComponentWidget);

protected:

	UPROPERTY(BlueprintReadOnly)
	AXICharacterBaseHero* HeroCharacter;

	UPROPERTY()
	EEquipSlot EquipSlotReference;

	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void SetupEquippedItems();

	UFUNCTION()
	void SetupCharacterStatus();
};
