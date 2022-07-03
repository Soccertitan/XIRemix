// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "XIActionBarEnhancedInputActions.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class XIREMIX_API UXIActionBarEnhancedInputActions : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Modifier")
	UInputAction* LeftShoulderHold;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Modifier")
	UInputAction* RightShoulderHold;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	UInputAction* LeftShoulderDPadDown;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	UInputAction* LeftShoulderDPadLeft;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	UInputAction* LeftShoulderDPadRright;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	UInputAction* LeftShoulderDPadUp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	UInputAction* LeftShoulderFaceButtonDown;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	UInputAction* LeftShoulderFaceButtonLeft;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	UInputAction* LeftShoulderFaceButtonRright;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	UInputAction* LeftShoulderFaceButtonUp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	UInputAction* RightShoulderDPadDown;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	UInputAction* RightShoulderDPadLeft;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	UInputAction* RightShoulderDPadRright;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	UInputAction* RightShoulderDPadUp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	UInputAction* RightShoulderFaceButtonDown;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	UInputAction* RightShoulderFaceButtonLeft;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	UInputAction* RightShoulderFaceButtonRright;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	UInputAction* RightShoulderFaceButtonUp;

};
