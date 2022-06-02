// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/XIUserWidget.h"
#include "XITargetPlateWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup = UI)
class XIREMIX_API UXITargetPlateWidget : public UXIUserWidget
{
	GENERATED_BODY()

public:

	//Sets up the widget and binds to the Actor's Ability System Component different events.
	UFUNCTION(BlueprintCallable, Category = "TargetPlateWidget")
	void SetupXITargetPlateWidget(AActor* Actor);

protected:

	UPROPERTY(BlueprintReadOnly, Category = "TargetPlateWidget", meta = (BindWidget))
	class UXIAttributeProgressBar* TargetHPProgressBar;

	UPROPERTY(BlueprintReadOnly, Category = "TargetPlateWidget", meta = (BindWidget))
	class UTextBlock* TargetName;

	UPROPERTY(BlueprintReadOnly, Category = "TargetPlateWidget")
	AActor* TargetedActor;

};
