// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/XIPlayerControllerInterface.h"
#include "Interfaces/XIGameplayControllerInterface.h"
#include "InputActionValue.h"
#include "XIEnums.h"
#include "EnhancedInputSubsystems.h"
#include "UINavPCComponent.h"
#include "UINavPCReceiver.h"
#include "DataAssets/XIActionBarEnhancedInputActions.h"
#include "XIPlayerControllerAction.generated.h"

class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class XIREMIX_API AXIPlayerControllerAction : public APlayerController, public IXIPlayerControllerInterface, public IXIGameplayControllerInterface, public IUINavPCReceiver
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UINavPC, meta = (AllowPrivateAccess = "true"))
	class UUINavPCComponent* UINavPC;

public:

	AXIPlayerControllerAction();

	virtual void CreateHUD() override;

	virtual class UXIPlayerHudWidget* GetHUD() const override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "XIPCInt")
	void SetIsMoveable(bool bIsMoveable); void SetIsMoveable_Implementation(bool bIsMoveable) override;

	void AcknowledgePossession(class APawn* P) override;

protected:
	
#pragma region Widgets

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TSubclassOf<class UXIPlayerHudWidget> XIPlayerHudClass;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class UXIPlayerHudWidget* XIPlayerHudWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TSubclassOf<class UXITargetPlateWidget> TargetPlateWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class UXITargetPlateWidget* TargetPlateWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TSubclassOf<class UXIUINavMainMenuWidget> MainMenuClass;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class UXIUINavMainMenuWidget* MainMenuWidget;

#pragma endregion

	UPROPERTY(BlueprintReadOnly, Category = "TargetSystem")
	class UXITargetSystemComponent* XITargetSystemCompRef;

	UPROPERTY(BlueprintReadOnly)
	class AXICharacterBaseHero* PlayerPawn;

	UPROPERTY(BlueprintReadOnly)
	class UXIAbilitySystemComponent* ASC;

	UPROPERTY(BlueprintReadWrite)
	bool bCanMove = true;

	UPROPERTY(BlueprintReadOnly)
	bool bShoulderButtonHeld = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EXITeamAttitude XITeamAttitude;

#pragma region EnhancedInputs

	void SetupInputComponent() override;

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem;

	//Input Actions
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Actions")
	UInputAction* IAMovement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Actions")
	UInputAction* IACamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Actions")
	UInputAction* IAInteract;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Actions")
	UInputAction* IAConfirm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Actions")
	UInputAction* IACancel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Actions")
	UInputAction* IATargetCycle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Actions")
	UInputAction* IATargetLock;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Actions")
	UInputAction* IAMenuToggle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Actions")
	UXIActionBarEnhancedInputActions* ActionBarEnhancedInputs;

	//Input Mappings

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Mappings")
	UInputMappingContext* ICExploration;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Mappings")
	int32 ICExplorationPriority = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Mappings")
	UInputMappingContext* ICCamera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Mappings")
	int32 ICCameraPriority = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Mappings")
	UInputMappingContext* ICTarget;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Mappings")
	int32 ICTargetPriority = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Mappings")
	UInputMappingContext* ICActionBar;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Mappings")
	int32 ICActionBarPriority = 0;

	// Input Functions
	void EnhancedMovement(const FInputActionValue& Value);
	void EnhancedCamera(const FInputActionValue& Value);
	void EnhancedInteract(const FInputActionValue& Value);
	void EnhancedConfirm(const FInputActionValue& Value);
	void EnhancedCancel(const FInputActionValue& Value);
	void EnhancedTargetCycle(const FInputActionValue& Value);
	void EnhancedTargetLock(const FInputActionValue& Value);
	void EnhancedMenuToggle(const FInputActionValue& Value);

	void EnhancedActionBarShoulderHeld(const FInputActionValue& Value);
	void EnhancedActionBarShoulderReleased(const FInputActionValue& Value);

#pragma endregion

	UFUNCTION()
	void TargetSelected(AActor* Actor);
	UFUNCTION()
	void TargetRemoved(AActor* Actor);

	//Ability task targeting callback.
	UFUNCTION()
	void OnXIStartAbilityTargeting();
	UFUNCTION()
	void OnXIEndAbilityTargeting();

	UPROPERTY()
	bool bIsAbilityTargeting = false;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnRep_PlayerState() override;

	void InitializeTargetSystem();
};
