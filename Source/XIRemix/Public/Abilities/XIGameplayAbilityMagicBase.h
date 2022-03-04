// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/XIGameplayAbility.h"
#include "XIGameplayAbilityMagicBase.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIGameplayAbilityMagicBase : public UXIGameplayAbility
{
	GENERATED_BODY()

public:
	UXIGameplayAbilityMagicBase();

	// virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	
	//The type of casting animation to use
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability|Magic")
	EXIMagicType XIMagicType;

	//Gets the Casting Anim Montage based on XIMagicType
	UFUNCTION(BlueprintPure, Category = "XIRemix|Ability")
	UAnimMontage* GetCastingAnimMontage();
};
