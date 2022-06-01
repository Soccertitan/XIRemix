// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XIInteractionWidget.h"
#include "Components/XIInteractionComponent.h"

void UXIInteractionWidget::UpdateInteractionWidget(class UXIInteractionComponent* InteractionComponent)
{
    OwningInteractionComponent = InteractionComponent;
    OnUpdateInteractionWidget();
}
