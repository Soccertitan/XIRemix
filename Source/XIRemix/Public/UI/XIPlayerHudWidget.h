// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/XIUserWidget.h"
#include "XIPlayerHudWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup = UI)
class XIREMIX_API UXIPlayerHudWidget : public UXIUserWidget
{
	GENERATED_BODY()

public:
	
	//Sets up the widget and binds to the Actor's Ability System Component different events.
	UFUNCTION(BlueprintCallable, Category = "XIPlayerHudWidget")
	void SetupXIPlayerHudWidget(AActor* Actor);

	UFUNCTION(BlueprintImplementableEvent, Category = "XIPlayerHudWidget")
	void HPValueChanged(float OldValue, float NewValue);

	UFUNCTION(BlueprintImplementableEvent, Category = "XIPlayerHudWidget")
	void MPValueChanged(float OldValue, float NewValue);

	UFUNCTION(BlueprintImplementableEvent, Category = "XIPlayerHudWidget")
	void TPValueChanged(float OldValue, float NewValue);

protected:

	UPROPERTY(BlueprintReadOnly, Category = "XIPlayerHudWidget", meta = (BindWidget))
	class UXIAttributeProgressBar* HPProgressBar;

	UPROPERTY(BlueprintReadOnly, Category = "XIPlayerHudWidget", meta = (BindWidget))
	class UXIAttributeProgressBar* MPProgressBar;

	UPROPERTY(BlueprintReadOnly, Category = "XIPlayerHudWidget", meta = (BindWidget))
	class UXIAttributeProgressBar* TPProgressBar;

	UPROPERTY(BlueprintReadOnly, Category = "XIPlayerHudWidget", meta = (BindWidget))
	class UTextBlock* HPValue;

	UPROPERTY(BlueprintReadOnly, Category = "XIPlayerHudWidget", meta = (BindWidget))
	class UTextBlock* MPValue;

	UPROPERTY(BlueprintReadOnly, Category = "XIPlayerHudWidget", meta = (BindWidget))
	class UTextBlock* TPValue;

	UPROPERTY(BlueprintReadOnly, Category = "XIPlayerHudWidget")
	AActor* PlayerActor;

	UFUNCTION()
	void HPAttributeChanged(float OldValue, float NewValue);

	UFUNCTION()
	void MPAttributeChanged(float OldValue, float NewValue);

	UFUNCTION()
	void TPAttributeChanged(float OldValue, float NewValue);

};
