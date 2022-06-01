// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UINavWidget.h"
#include "XIUINavWidget.generated.h"

/**
 * The UINavWidget that this project should make subclasses from for navigatable widgets with controller, keyboard, and mouse.
 */
UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup = UI)
class XIREMIX_API UXIUINavWidget : public UUINavWidget
{
	GENERATED_BODY()
	
};
