// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/XIUserWidget.h"
#include "UI/Components/XIAttributeTextBlock.h"
#include "XICharacterStatusWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup = UI)
class XIREMIX_API UXICharacterStatusWidget : public UXIUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "XICharacterStatusWidget")
	void SetupXICharacterStatusWidget(AActor* Actor);

protected:

	UPROPERTY(BlueprintReadOnly, Category = "XICharacterStatusWidget")
	AActor* TargetActor;

	UPROPERTY(BlueprintReadOnly, Category = "XICharacterStatusWidget", meta = (BindWidget, OptionalWidget = true))
	class UTextBlock* CharacterNameText;
	UPROPERTY(BlueprintReadOnly, Category = "XICharacterStatusWidget", meta = (BindWidget, OptionalWidget = true))
	class UTextBlock* MainJobText;
	UPROPERTY(BlueprintReadOnly, Category = "XICharacterStatusWidget", meta = (BindWidget, OptionalWidget = true))
	class UTextBlock* SubJobText;
	UPROPERTY(BlueprintReadOnly, Category = "XICharacterStatusWidget", meta = (BindWidget, OptionalWidget = true))
	class UTextBlock* MainJobLv;
	UPROPERTY(BlueprintReadOnly, Category = "XICharacterStatusWidget", meta = (BindWidget, OptionalWidget = true))
	class UTextBlock* SubJobLv;

	// All the XIAttributeTextBlocks in this widget.
	UPROPERTY(BlueprintReadOnly, Category = "XICharacterStatusWidget")
	TArray<UXIAttributeTextBlock*> AttributeTextBlocks;

	void GetAttributeTextBlocks();

	// Casts the actor an XICharacterBaseHero to retrieve their level and job.
	void SetupMainSubJobValues(AActor* Actor);

	void SetupAttributeBindings();

	virtual void NativeOnInitialized() override;
};
