// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/XIPlayerControllerAction.h"
#include "Interfaces/XICharacterInterface.h"
#include "UI/XIPlayerHUD.h"

void AXIPlayerControllerAction::BeginPlay()
{
    Super::BeginPlay();
    PlayerPawn = GetPawn();
}

void AXIPlayerControllerAction::CreateHUD()
{
    // Only Create Once
    if(UIHUDWidget)
    {
        return;
    }

    if (!UIHUDWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing UIHUDWidgetClass. Please fill in on the Blueprint of the PlayerController."), *FString(__FUNCTION__));
		return;
	}

    // Only create a HUD for local player and Pawn is valid
    if (!IsLocalPlayerController() | !PlayerPawn)
    {
        return;
    }

    // Implemented the XICharacterInterface
    IXICharacterInterface* XICharInt = Cast<IXICharacterInterface>(PlayerPawn);
    if(!XICharInt)
    {
        UE_LOG(LogTemp, Error, TEXT("%s() PlayerPawn doesn't implemented interface"), *FString(__FUNCTION__));
        return;
    }

    //Create the Widget!
    UIHUDWidget = CreateWidget<UXIPlayerHUD>(this, UIHUDWidgetClass);
    UIHUDWidget->AddToViewport();

    //Set Attributes
    UIHUDWidget->SetHitPoints(XICharInt->GetHitPoints());
    UIHUDWidget->SetHitPointsMax(XICharInt->GetHitPointsMax());
    UIHUDWidget->SetManaPoints(XICharInt->GetManaPoints());
    UIHUDWidget->SetManaPointsMax(XICharInt->GetManaPointsMax());
    UIHUDWidget->SetTacticalPoints(XICharInt->GetTacticalPoints());
    UIHUDWidget->SetTacticalPointsMax(XICharInt->GetTacticalPointsMax());
}

UXIPlayerHUD * AXIPlayerControllerAction::GetHUD() const
{
    return UIHUDWidget;
}

void AXIPlayerControllerAction::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// For edge cases where the PlayerState is repped before the Hero is possessed.
	CreateHUD();
}