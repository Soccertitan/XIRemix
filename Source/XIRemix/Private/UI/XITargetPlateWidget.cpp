// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XITargetPlateWidget.h"
#include "Abilities/XIAbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Abilities/AttributeSetGlobal.h"
#include "UI/Components/XIAttributeProgressBar.h"
#include "Components/TextBlock.h"
#include "FunctionLibrary/XIGameplayFunctionLibrary.h"

void UXITargetPlateWidget::SetupXITargetPlateWidget(AActor* Actor)
{
    TargetedActor = Actor;
    TargetHPProgressBar->SetupAttributeCallback(Actor);

    if(TargetedActor)
    {
        TargetName->SetText(UXIGameplayFunctionLibrary::GetCharacterName(TargetedActor));
    }
}