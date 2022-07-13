// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ProgressBar.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "XIAbilityCooldownProgressBar.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FXIOnCooldownChanged, FGameplayTag, CooldownTag, float, TimeRemaining, float, Duration);

/**
 * Binds to the ability systemc component gameplay tag events to track cooldowns. Will automatically update this widget's percent value!
 */
UCLASS()
class XIREMIX_API UXIAbilityCooldownProgressBar : public UProgressBar
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FXIOnCooldownChanged OnCooldownBegin;

	UPROPERTY(BlueprintAssignable)
	FXIOnCooldownChanged OnCooldownEnd;

	UPROPERTY(BlueprintAssignable)
	FXIOnCooldownChanged OnPercentUpdated;

	//Gets the Actors Ability System Component and calls the internal SetupCooldownCallback C++ function. To bind to the delegates.
	UFUNCTION(BlueprintCallable, Category = "XIAbilityCooldownProgressBar")
	bool SetupCooldownCallback(AActor* Actor, FGameplayTagContainer CooldownTags);

	//Unbinds to an existing delegate before attempting to bind to a new one.
	bool SetupCooldownCallback(UAbilitySystemComponent* ASC, FGameplayTagContainer CooldownTags);

	//Clears the binding to the Ability System Component.
	UFUNCTION(BlueprintCallable, Category = "XIAbilityCooldownProgressBar")
	void ClearCooldownCallback();

	FORCEINLINE void SetUseServerCooldown(bool bInUseServerCooldown) {bUseServerCooldown = bInUseServerCooldown;}

	UFUNCTION(BlueprintCallable, Category = "XIAbilityCooldownProgressBar")
	bool GetCooldownRemainingForTag(FGameplayTagContainer CooldownTags, float& TimeRemaining, float& CooldownDuration);

	//Hides the widget if the image is null.
	UFUNCTION(BlueprintCallable, Category = "XIAbilityCooldownProgressBar")
	void UpdateImage(UTexture2D* Image);

protected:

	UPROPERTY()
	UAbilitySystemComponent* ASC;

	UPROPERTY()
	FGameplayTagContainer CooldownTags;

	UPROPERTY(EditAnywhere)
	bool bUseServerCooldown = true;

	//How often refresh the widget's percent value in seconds.
	UPROPERTY(EditAnywhere, meta = (ClampMin="0.01"))
	float RefreshRate = 0.1f;

	FTimerHandle TimerHandle_RefreshPercent;
	float TimeRemaining;
	float Duration;

	virtual void OnActiveGameplayEffectAddedCallback(UAbilitySystemComponent* Target, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle);
	virtual void CooldownTagChanged(const FGameplayTag CooldownTag, int32 NewCount);

	void RefreshProgressBarPercent();
};
