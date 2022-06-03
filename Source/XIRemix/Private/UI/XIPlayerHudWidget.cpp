// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XIPlayerHudWidget.h"
#include "UI/Components/XIAttributeProgressBar.h"
#include "Components/TextBlock.h"

void UXIPlayerHudWidget::SetupXIPlayerHudWidget(AActor* Actor)
{
    PlayerActor = Actor;

    HPProgressBar->SetupAttributeCallback(PlayerActor);
    MPProgressBar->SetupAttributeCallback(PlayerActor);
    TPProgressBar->SetupAttributeCallback(PlayerActor);

    HPProgressBar->OnCurrentValueChanged.Clear();
    MPProgressBar->OnCurrentValueChanged.Clear();
    TPProgressBar->OnCurrentValueChanged.Clear();

    HPProgressBar->OnCurrentValueChanged.AddDynamic(this, &UXIPlayerHudWidget::HPAttributeChanged);
    MPProgressBar->OnCurrentValueChanged.AddDynamic(this, &UXIPlayerHudWidget::MPAttributeChanged);
    TPProgressBar->OnCurrentValueChanged.AddDynamic(this, &UXIPlayerHudWidget::TPAttributeChanged);

    HPValue->SetText(FText::AsNumber(HPProgressBar->GetCurrentValue()));
    MPValue->SetText(FText::AsNumber(MPProgressBar->GetCurrentValue()));
    TPValue->SetText(FText::AsNumber(TPProgressBar->GetCurrentValue()));
}

void UXIPlayerHudWidget::HPAttributeChanged(float OldValue, float NewValue)
{
    FText Value = FText::AsNumber(NewValue);
    HPValue->SetText(Value);
    HPValueChanged(NewValue, OldValue);
}

void UXIPlayerHudWidget::MPAttributeChanged(float OldValue, float NewValue)
{
    FText Value = FText::AsNumber(NewValue);
    MPValue->SetText(Value);
    MPValueChanged(NewValue, OldValue);
}

void UXIPlayerHudWidget::TPAttributeChanged(float OldValue, float NewValue)
{
    FText Value = FText::AsNumber(NewValue);
    TPValue->SetText(Value);
    TPValueChanged(NewValue, OldValue);
}