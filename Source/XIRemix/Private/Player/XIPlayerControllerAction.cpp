// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/XIPlayerControllerAction.h"
#include "Interfaces/XICharacterInterface.h"
#include "UI/XIPlayerHudWidget.h"
#include "UI/XITargetPlateWidget.h"
#include "UI/XIUINavMainMenuWidget.h"
#include "FunctionLibrary/XIGameplayFunctionLibrary.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/XITargetSystemComponent.h"
#include "Interfaces/XITargetSystemInterface.h"

AXIPlayerControllerAction::AXIPlayerControllerAction()
{
    UINavPC = CreateDefaultSubobject<UUINavPCComponent>("UINavPC");
}

void AXIPlayerControllerAction::BeginPlay()
{
    Super::BeginPlay();

    EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer());

    if (EnhancedInputSubsystem)
    {
        EnhancedInputSubsystem->AddMappingContext(ICMovement, ICMovementPriority);
        EnhancedInputSubsystem->AddMappingContext(ICCamera, ICCameraPriority);
        EnhancedInputSubsystem->AddMappingContext(ICTarget, ICTargetPriority);
    }

}

void AXIPlayerControllerAction::AcknowledgePossession(class APawn* P)
{
    Super::AcknowledgePossession(P);

    PlayerPawn = AcknowledgedPawn.Get();
    
    CreateHUD();
    InitializeTargetSystem();
}

void AXIPlayerControllerAction::CreateHUD()
{
    // Only Create Once
    if(XIPlayerHudWidget)
    {
        return;
    }

    if (!XIPlayerHudClass)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing XIPlayerHudClass. Please fill in on the Blueprint of the PlayerController."), *FString(__FUNCTION__));
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
        UE_LOG(LogTemp, Error, TEXT("%s() PlayerPawn doesn't implement interface XICharacterInterface"), *FString(__FUNCTION__));
        return;
    }

    //Create the Widget!
    XIPlayerHudWidget = CreateWidget<UXIPlayerHudWidget>(this, XIPlayerHudClass);
    XIPlayerHudWidget->AddToViewport();

    //Set Attributes
    XIPlayerHudWidget->SetHitPoints(XICharInt->GetHitPoints());
    XIPlayerHudWidget->SetHitPointsMax(XICharInt->GetHitPointsMax());
    XIPlayerHudWidget->SetManaPoints(XICharInt->GetManaPoints());
    XIPlayerHudWidget->SetManaPointsMax(XICharInt->GetManaPointsMax());
    XIPlayerHudWidget->SetTacticalPoints(XICharInt->GetTacticalPoints());
    XIPlayerHudWidget->SetTacticalPointsMax(XICharInt->GetTacticalPointsMax());
}

UXIPlayerHudWidget * AXIPlayerControllerAction::GetHUD() const
{
    return XIPlayerHudWidget;
}

void AXIPlayerControllerAction::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// For edge cases where the PlayerState is repped before the Hero is possessed.
	CreateHUD();
}

void AXIPlayerControllerAction::SetIsMoveable_Implementation(bool bIsMoveable)
{
    bCanMove = bIsMoveable;
}

#pragma region EnhancedInput

void AXIPlayerControllerAction::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        if(IAMovement)
        {
            EnhancedInputComponent->BindAction(IAMovement, ETriggerEvent::Triggered, this, &AXIPlayerControllerAction::EnhancedMovement);
        }
        if(IACamera)
        {
            EnhancedInputComponent->BindAction(IACamera, ETriggerEvent::Triggered, this, &AXIPlayerControllerAction::EnhancedCamera);
        }
        if(IATargetCycle)
        {
            EnhancedInputComponent->BindAction(IATargetCycle, ETriggerEvent::Triggered, this, &AXIPlayerControllerAction::EnhancedTargetCycle);
        }
        if(IATargetLock)
        {
            EnhancedInputComponent->BindAction(IATargetLock, ETriggerEvent::Triggered, this, &AXIPlayerControllerAction::EnhancedTargetLock);
        }
        if(IAMenuToggle)
        {
            EnhancedInputComponent->BindAction(IAMenuToggle, ETriggerEvent::Triggered, this, &AXIPlayerControllerAction::EnhancedMenuToggle);
        }
    }
}

void AXIPlayerControllerAction::EnhancedMovement(const FInputActionValue& Value)
{
    if(PlayerPawn && bCanMove)
    {
        FRotator Rotation = PlayerPawn->GetControlRotation();
        FVector ForwardVector = UKismetMathLibrary::GetForwardVector(FRotator(0,Rotation.Yaw,0));
        FVector RightVector = UKismetMathLibrary::GetRightVector(FRotator(0,Rotation.Yaw,0));
        PlayerPawn->AddMovementInput(ForwardVector, Value[1], false);
        PlayerPawn->AddMovementInput(RightVector, Value[0], false);
    }
}

void AXIPlayerControllerAction::EnhancedCamera(const FInputActionValue& Value)
{
    if(PlayerPawn)
    {
        PlayerPawn->AddControllerPitchInput(Value[1]);
        PlayerPawn->AddControllerYawInput(Value[0]);
    }
}

void AXIPlayerControllerAction::EnhancedTargetCycle(const FInputActionValue& Value)
{
    if(XITargetSystemCompRef)
    {
        XITargetSystemCompRef->TargetActor(XITeamAttitude, Value.GetMagnitude());
    }
}

void AXIPlayerControllerAction::EnhancedTargetLock(const FInputActionValue& Value)
{
    if(XITargetSystemCompRef)
    {
        XITargetSystemCompRef->LockCamera();
    }
}

void AXIPlayerControllerAction::EnhancedMenuToggle(const FInputActionValue& Value)
{
    if(!MainMenuWidget)
    {
        MainMenuWidget = CreateWidget<UXIUINavMainMenuWidget>(this, MainMenuClass);
    }

    if(MainMenuWidget)
    {
        if(MainMenuWidget->IsInViewport())
        {
            UINavPC->GetActiveWidget()->ReturnToParent(true);

            if(EnhancedInputSubsystem)
            {
                EnhancedInputSubsystem->AddMappingContext(ICTarget, ICTargetPriority);
            }

            FInputModeGameOnly InputMode;
            SetInputMode(InputMode);
            bShowMouseCursor = false;
        }
        else
        {
            if(EnhancedInputSubsystem)
            {
                EnhancedInputSubsystem->RemoveMappingContext(ICTarget);
            }
            
            MainMenuWidget->AddToViewport();
            
            FInputModeGameAndUI InputMode;
            SetInputMode(InputMode);
            bShowMouseCursor = true;
        }
    }
}

#pragma endregion

void AXIPlayerControllerAction::TargetSelected(AActor* Actor)
{
    if(!TargetPlateWidget && IsLocalPlayerController())
    {
        TargetPlateWidget = CreateWidget<UXITargetPlateWidget>(this, TargetPlateWidgetClass);
        if(TargetPlateWidget)
        {
            TargetPlateWidget->TargetedActor = Actor;
            TargetPlateWidget->AddToViewport();

            UXIGameplayFunctionLibrary::SetMainTarget(PlayerPawn, Actor);
        }
    }
}

void AXIPlayerControllerAction::TargetRemoved(AActor* Actor)
{
    if(TargetPlateWidget && IsLocalPlayerController())
    {
        TargetPlateWidget->RemoveFromParent();
        TargetPlateWidget = nullptr;
        UXIGameplayFunctionLibrary::SetMainTarget(PlayerPawn, nullptr);
    }
}

void AXIPlayerControllerAction::InitializeTargetSystem()
{
    IXITargetSystemInterface* XITargetInt = Cast<IXITargetSystemInterface>(PlayerPawn);
    if(XITargetInt)
    {
        XITargetSystemCompRef = XITargetInt->GetXITargetSystemComponent();

        if(XITargetSystemCompRef)
        {
            XITargetSystemCompRef->OnTargetSelected.AddDynamic(this, &AXIPlayerControllerAction::TargetSelected);
            XITargetSystemCompRef->OnTargetRemoved.AddDynamic(this, &AXIPlayerControllerAction::TargetRemoved);
        }
    }
}