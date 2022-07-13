// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/XIUserWidget.h"
#include "PaperFlipbook.h"
#include "XIFlipbookAnimatedWidget.generated.h"

/**
 * Functionality to support a flipbook for an animating widget.
 */
UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup = UI)
class XIREMIX_API UXIFlipbookAnimatedWidget : public UXIUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, Category = "XIFlipbookAnimatedWidget", meta = (BindWidget))
	class UImage* IconImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XIFlipbookAnimatedWidget")
	UPaperFlipbook* FlipbookAnimation;

protected:

	void InitializeTimer();
	void UpdateImage();
	static FSlateBrush MakeBrushFromSprite(UPaperSprite* Sprite, int32 Width, int32 Height);

	FTimerHandle TimerHandle_UpdateImage;
	UPaperSprite* NewSprite;
	FSlateBrush NewBrush;

private:

	int32 CurrentFrame;
	int32 TotalFrames;
	float Delay;	
};
