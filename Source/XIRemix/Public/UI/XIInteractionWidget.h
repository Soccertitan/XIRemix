// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/XIUserWidget.h"
#include "XIInteractionWidget.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIInteractionWidget : public UXIUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Interaction")	
	void UpdateInteractionWidget(class UXIInteractionComponent* InteractionComponent);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUpdateInteractionWidget();

	UPROPERTY(BlueprintReadOnly, Category = "Interaction", meta = (ExposeOnSpawn))
	class UXIInteractionComponent* OwningInteractionComponent;

};
