// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ProgressBar.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "XIAttributeProgressBar.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FValueChanged, float, OldValue, float, NewValue);

/**
 * Sets the percent of the progress bar based on the attributes specified in the editor.
 */
UCLASS()
class XIREMIX_API UXIAttributeProgressBar : public UProgressBar
{
	GENERATED_BODY()

public:

	//Gets the Actors Ability System Component and binds delegates to the attribute changes.
	UFUNCTION(BlueprintCallable, Category = "XIAttributeProgressBar")
	bool SetupAttributeCallback(AActor* Actor);

	UPROPERTY(BlueprintAssignable, Category = "XIAttributeProgressBar")
	FValueChanged OnCurrentValueChanged;
	UPROPERTY(BlueprintAssignable, Category = "XIAttributeProgressBar")
	FValueChanged OnMaxValueChanged;

	UFUNCTION(BlueprintPure, Category = "XIAttributeProgressBar")
	float GetPercentValue() const;

	UFUNCTION(BlueprintPure, Category = "XIAttributeProgressBar")
	float GetCurrentValue() const;

	UFUNCTION(BlueprintPure, Category = "XIAttributeProgressBar")
	float GetMaxValue() const;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "XIAttributeProgressBar")
	AActor* TargetActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XIAttributeProgressBar")
	FGameplayAttribute CurrentValueAttribute;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XIAttributeProgressBar")
	FGameplayAttribute MaxValueAttribute;
	
	UPROPERTY(BlueprintReadOnly, Category = "XIAttributeProgressBar")
	float CurrentValue;

	UPROPERTY(BlueprintReadOnly, Category = "XIAttributeProgressBar")
	float MaxValue;

	UPROPERTY(BlueprintReadOnly, Category = "XIAttributeProgressBar")
	UAbilitySystemComponent* ASC;

	// Attribute delegates
	FDelegateHandle CurrentValueChangedDelegateHandle;
	FDelegateHandle MaxValueChangedDelegateHandle;
	virtual void CurrentValueChanged(const FOnAttributeChangeData& Data);
	virtual void MaxValueChanged(const FOnAttributeChangeData& Data);

};
