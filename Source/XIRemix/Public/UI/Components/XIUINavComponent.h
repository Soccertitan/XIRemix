// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UINavComponent.h"
#include "XIUINavComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FXIOnButtonHover, class UXIUINavComponent*, Button);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FXIOnButtonUnHover, class UXIUINavComponent*, Button);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FXIOnButtonClicked, class UXIUINavComponent*, Button);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FXIOnButtonPress, class UXIUINavComponent*, Button);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FXIOnButtonRelease, class UXIUINavComponent*, Button);

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup = UI)
class XIREMIX_API UXIUINavComponent : public UUINavComponent
{
	GENERATED_BODY()

public:
	
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintAssignable)
	FXIOnButtonHover OnButtonHover;

	UPROPERTY(BlueprintAssignable)
	FXIOnButtonUnHover OnButtonUnHover;

	UPROPERTY(BlueprintAssignable)
	FXIOnButtonClicked OnButtonClicked;

	UPROPERTY(BlueprintAssignable)
	FXIOnButtonPress OnButtonPress;

	UPROPERTY(BlueprintAssignable)
	FXIOnButtonRelease OnButtonRelease;

protected:

	UFUNCTION()
	virtual void OnHover();

	UFUNCTION()
	virtual void OnUnhover();

	UFUNCTION()
	virtual void OnClick();

	UFUNCTION()
	virtual void OnPress();

	UFUNCTION()
	virtual void OnRelease();
};
