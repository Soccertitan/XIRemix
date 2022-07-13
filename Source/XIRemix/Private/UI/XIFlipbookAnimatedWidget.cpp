// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XIFlipbookAnimatedWidget.h"
#include "Components/Image.h"
#include "PaperSprite.h"
#include "Brushes/SlateNoResource.h"

void UXIFlipbookAnimatedWidget::NativeConstruct()
{
    Super::NativeConstruct();
    InitializeTimer();
}

void UXIFlipbookAnimatedWidget::InitializeTimer()
{
    if (!FlipbookAnimation) return;
    
    Delay = 1.f / FlipbookAnimation->GetFramesPerSecond();
    TotalFrames = FlipbookAnimation->GetNumFrames();

    GetWorld()->GetTimerManager().SetTimer(TimerHandle_UpdateImage, this, &UXIFlipbookAnimatedWidget::UpdateImage, Delay, true);
}

void UXIFlipbookAnimatedWidget::UpdateImage()
{
    if(CurrentFrame < TotalFrames)
    {
        if(FlipbookAnimation)
        {
            NewSprite = FlipbookAnimation->GetSpriteAtFrame(CurrentFrame);
            NewBrush = MakeBrushFromSprite(NewSprite, 0, 0);
            IconImage->SetBrush(NewBrush);
            CurrentFrame++;
        }
    }
    else
    {
        CurrentFrame = 0;
        UpdateImage();
    }
}

FSlateBrush UXIFlipbookAnimatedWidget::MakeBrushFromSprite(UPaperSprite* Sprite, int32 Width, int32 Height)
{
    if ( Sprite )
	{
		const FSlateAtlasData SpriteAtlasData = Sprite->GetSlateAtlasData();
		const FVector2D SpriteSize = SpriteAtlasData.GetSourceDimensions();

		FSlateBrush Brush;
		Brush.SetResourceObject(Sprite);
		Width = ( Width > 0 ) ? Width : SpriteSize.X;
		Height = ( Height > 0 ) ? Height : SpriteSize.Y;
		Brush.ImageSize = FVector2D(Width, Height);
		return Brush;
	}

    return FSlateNoResource();
}