// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/XIPlayerControllerAction.h"
#include "Characters/XICharacterBaseHero.h"
#include "Interfaces/XICharacterInterface.h"
#include "UI/XIPlayerHudWidget.h"
#include "UI/XITargetPlateWidget.h"
#include "UI/XIUINavMainMenuWidget.h"
#include "FunctionLibrary/XIGameplayFunctionLibrary.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/XITargetSystemComponent.h"
#include "Interfaces/XITargetSystemInterface.h"
#include "Abilities/XIAbilitySystemComponent.h"

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
        EnhancedInputSubsystem->AddMappingContext(ICExploration, ICExplorationPriority);
        EnhancedInputSubsystem->AddMappingContext(ICCamera, ICCameraPriority);
        EnhancedInputSubsystem->AddMappingContext(ICTarget, ICTargetPriority);
        EnhancedInputSubsystem->AddMappingContext(ICActionBar, ICActionBarPriority);
    }

}

void AXIPlayerControllerAction::AcknowledgePossession(class APawn* P)
{
    Super::AcknowledgePossession(P);

    PlayerPawn = Cast<AXICharacterBaseHero>(AcknowledgedPawn.Get());
    
    if(PlayerPawn)
    {
        ASC = Cast<UXIAbilitySystemComponent>(PlayerPawn->GetAbilitySystemComponent());

        if(ASC)
        {
            ASC->OnXIStartAbilityTargeting.AddDynamic(this, &AXIPlayerControllerAction::OnXIStartAbilityTargeting);
            ASC->OnXIEndAbilityTargeting.AddDynamic(this, &AXIPlayerControllerAction::OnXIEndAbilityTargeting);
        }
    }
    
    CreateHUD();
    InitializeTargetSystem();
}

void AXIPlayerControllerAction::CreateHUD()
{
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

    //Create the Widget!
    if(!XIPlayerHudWidget)
    {
        XIPlayerHudWidget = CreateWidget<UXIPlayerHudWidget>(this, XIPlayerHudClass);
    }

    if(XIPlayerHudWidget)
    {
        XIPlayerHudWidget->SetupXIPlayerHudWidget(PlayerPawn);
        XIPlayerHudWidget->AddToViewport();
    }
}

UXIPlayerHudWidget * AXIPlayerControllerAction::GetHUD() const
{
    return XIPlayerHudWidget;
}

void AXIPlayerControllerAction::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
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
        if(IAInteract)
        {
            EnhancedInputComponent->BindAction(IAInteract, ETriggerEvent::Triggered, this, &AXIPlayerControllerAction::EnhancedInteract);
        }
        if(IAConfirm)
        {
            EnhancedInputComponent->BindAction(IAConfirm, ETriggerEvent::Triggered, this, &AXIPlayerControllerAction::EnhancedConfirm);
        }
        if(IACancel)
        {
            EnhancedInputComponent->BindAction(IACancel, ETriggerEvent::Triggered, this, &AXIPlayerControllerAction::EnhancedCancel);
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
        if(ActionBarEnhancedInputs)
        {
            if(ActionBarEnhancedInputs->LeftShoulderHold)
            {
                EnhancedInputComponent->BindAction(ActionBarEnhancedInputs->LeftShoulderHold, ETriggerEvent::Triggered, this, &AXIPlayerControllerAction::EnhancedActionBarShoulderHeld);
                EnhancedInputComponent->BindAction(ActionBarEnhancedInputs->LeftShoulderHold, ETriggerEvent::Completed, this, &AXIPlayerControllerAction::EnhancedActionBarShoulderReleased);  
            }
            if(ActionBarEnhancedInputs->RightShoulderHold)
            {
                EnhancedInputComponent->BindAction(ActionBarEnhancedInputs->RightShoulderHold, ETriggerEvent::Triggered, this, &AXIPlayerControllerAction::EnhancedActionBarShoulderHeld);
                EnhancedInputComponent->BindAction(ActionBarEnhancedInputs->RightShoulderHold, ETriggerEvent::Completed, this, &AXIPlayerControllerAction::EnhancedActionBarShoulderReleased);
            }
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

void AXIPlayerControllerAction::EnhancedInteract(const FInputActionValue& Value)
{
    if(PlayerPawn)
    {
        if(Value.Get<bool>())
        {
            PlayerPawn->BeginInteract();
        }
        else
        {
            PlayerPawn->EndInteract();
        }
    }
}

void AXIPlayerControllerAction::EnhancedConfirm(const FInputActionValue& Value)
{
    if(bShoulderButtonHeld)
    {
        return;
    }

    if(bIsAbilityTargeting && ASC)
    {
        ASC->LocalInputConfirm();
    }
}

void AXIPlayerControllerAction::EnhancedCancel(const FInputActionValue& Value)
{
    if(bShoulderButtonHeld)
    {
        return;
    }

    if(bIsAbilityTargeting && ASC)
    {
        ASC->LocalInputCancel();
    }
    else
    {
        if(XITargetSystemCompRef)
        {
            XITargetSystemCompRef->RemoveTargetedActor();
        }
    }
}

void AXIPlayerControllerAction::EnhancedTargetCycle(const FInputActionValue& Value)
{
    if(bIsAbilityTargeting && ASC)
    {
        ASC->XICycleTarget(Value.GetMagnitude());
    }
    else
    {
        if(XITargetSystemCompRef)
        {
            XITargetSystemCompRef->TargetActor(XITeamAttitude, Value.GetMagnitude());
        }
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
                EnhancedInputSubsystem->AddMappingContext(ICActionBar, ICActionBarPriority);
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
                EnhancedInputSubsystem->RemoveMappingContext(ICActionBar);
            }
            
            MainMenuWidget->AddToViewport();
            
            FInputModeGameAndUI InputMode;
            SetInputMode(InputMode);
            bShowMouseCursor = true;
        }
    }
}

void AXIPlayerControllerAction::EnhancedActionBarShoulderHeld(const FInputActionValue& Value)
{
    bShoulderButtonHeld = true;
    EnhancedInputSubsystem->RemoveMappingContext(ICTarget);
}

void AXIPlayerControllerAction::EnhancedActionBarShoulderReleased(const FInputActionValue& Value)
{
    bShoulderButtonHeld = false;
    EnhancedInputSubsystem->AddMappingContext(ICTarget, ICTargetPriority);
}

#pragma endregion

void AXIPlayerControllerAction::TargetSelected(AActor* Actor)
{
    if(!IsLocalPlayerController())
    {
        return;
    }

    if(!TargetPlateWidget)
    {
        TargetPlateWidget = CreateWidget<UXITargetPlateWidget>(this, TargetPlateWidgetClass);
    }

    if(TargetPlateWidget)
    {
        TargetPlateWidget->SetupXITargetPlateWidget(Actor);
        TargetPlateWidget->AddToViewport();

        UXIGameplayFunctionLibrary::SetMainTarget(PlayerPawn, Actor);
    }
}

void AXIPlayerControllerAction::TargetRemoved(AActor* Actor)
{
    if(TargetPlateWidget && IsLocalPlayerController())
    {
        TargetPlateWidget->RemoveFromParent();
        TargetPlateWidget->SetupXITargetPlateWidget(nullptr);
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

void AXIPlayerControllerAction::OnXIStartAbilityTargeting()
{
    bIsAbilityTargeting = true;
}

void AXIPlayerControllerAction::OnXIEndAbilityTargeting()
{
    bIsAbilityTargeting = false;
}