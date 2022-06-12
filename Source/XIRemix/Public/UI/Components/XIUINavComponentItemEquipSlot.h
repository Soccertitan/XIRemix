// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Components/XIUINavComponentItemSlot.h"
#include "XIUINavComponentItemEquipSlot.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup = UI)
class XIREMIX_API UXIUINavComponentItemEquipSlot : public UXIUINavComponentItemSlot
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintPure, Category = "XIUINavComponentEquipSlot")
	FORCEINLINE EEquipSlot GetEquipSlot() const {return EquipSlot;};

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XIUINavComponentItemEquipSlot")
	EEquipSlot EquipSlot;

	//Sets the NavText to this value.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XIUINavComponentItemEquipSlot")
	FText EquipSlotText;	
};
