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

	UPROPERTY(BlueprintReadWrite, Category = "TargetSystem")
	class UXITargetSystemComponent* XITargetSystemCompRef;

	UPROPERTY(BlueprintReadWrite)
	APawn* PlayerPawn;

	UPROPERTY(BlueprintReadWrite)
	bool bCanMove = true;

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
	UInputAction* IATargetCycle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Actions")
	UInputAction* IATargetLock;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Actions")
	UInputAction* IAMenuToggle;

	//Input Mappings

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Mappings")
	UInputMappingContext* ICMovement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Mappings")
	int32 ICMovementPriority = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Mappings")
	UInputMappingContext* ICCamera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Mappings")
	int32 ICCameraPriority = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Mappings")
	UInputMappingContext* ICTarget;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Input Mappings")
	int32 ICTargetPriority = 0;

	// Input Functions
	void EnhancedMovement(const FInputActionValue& Value);
	void EnhancedCamera(const FInputActionValue& Value);
	void EnhancedTargetCycle(const FInputActionValue& Value);
	void EnhancedTargetLock(const FInputActionValue& Value);
	void EnhancedMenuToggle(const FInputActionValue& Value);

#pragma endregion

	UFUNCTION()
	void TargetSelected(AActor* Actor);
	UFUNCTION()
	void TargetRemoved(AActor* Actor);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnRep_PlayerState() override;

	void InitializeTargetSystem();
};
