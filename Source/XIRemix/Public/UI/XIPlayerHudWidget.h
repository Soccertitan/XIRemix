// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/XIUserWidget.h"
#include "XIPlayerHudWidget.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIPlayerHudWidget : public UXIUserWidget
{
	GENERATED_BODY()

public:
	
	/**
	* Attribute setters
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetHitPoints(float Value);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetHitPointsMax(float Value);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetManaPoints(float Value);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetManaPointsMax(float Value);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetTacticalPoints(float Value);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetTacticalPointsMax(float Value);

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes")
	float HitPoints;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes")
	float HitPointsMax;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes")
	float ManaPoints;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes")
	float ManaPointsMax;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes")
	float TacticalPoints;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes")
	float TacticalPointsMax;

};
