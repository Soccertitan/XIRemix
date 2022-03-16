// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/XIPlayerControllerInterface.h"
#include "Interfaces/XIGameplayControllerInterface.h"
#include "XIPlayerControllerAction.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API AXIPlayerControllerAction : public APlayerController, public IXIPlayerControllerInterface, public IXIGameplayControllerInterface
{
	GENERATED_BODY()

public:

	virtual void CreateHUD() override;

	virtual class UXIPlayerHUD* GetHUD() const override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "XIPCInt")
	void SetIsMoveable(bool bIsMoveable); void SetIsMoveable_Implementation(bool bIsMoveable) override; 

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "XICharacter|UI")
	TSubclassOf<class UXIPlayerHUD> UIHUDWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "XICharacter|UI")
	class UXIPlayerHUD* UIHUDWidget;

	UPROPERTY(BlueprintReadWrite, Category = "XICharacter")
	APawn* PlayerPawn;

	UPROPERTY(BlueprintReadWrite)
	bool bCanMove = true;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnRep_PlayerState() override;
};
