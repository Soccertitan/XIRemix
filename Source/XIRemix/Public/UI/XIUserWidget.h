// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XIUserWidget.generated.h"

/**
 * The user widget that should be subclassed that do not need navigation.
 */
UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup = UI)
class XIREMIX_API UXIUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
};
