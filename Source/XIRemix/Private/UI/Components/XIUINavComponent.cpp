// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Components/XIUINavComponent.h"
#include "UINavButton.h"

void UXIUINavComponent::NativeConstruct()
{
    NavButton->OnHovered.AddUniqueDynamic(this, &UXIUINavComponent::OnHover);
    NavButton->OnUnhovered.AddUniqueDynamic(this, &UXIUINavComponent::OnUnhover);
    NavButton->OnClicked.AddUniqueDynamic(this, &UXIUINavComponent::OnClick);
    NavButton->OnPressed.AddUniqueDynamic(this, &UXIUINavComponent::OnPress);
    NavButton->OnReleased.AddUniqueDynamic(this, &UXIUINavComponent::OnRelease);

    Super::NativeConstruct();
}

void UXIUINavComponent::OnHover()
{
    OnButtonHover.Broadcast(this);
}

void UXIUINavComponent::OnUnhover()
{
    OnButtonUnHover.Broadcast(this);
}

void UXIUINavComponent::OnClick()
{
    OnButtonClicked.Broadcast(this);
}

void UXIUINavComponent::OnPress()
{
    OnButtonPress.Broadcast(this);
}

void UXIUINavComponent::OnRelease()
{
    OnButtonRelease.Broadcast(this);
}