// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/XIGameplayAbility.h"
#include "DataAssets/XIJobAbilityData.h"
#include "XIGameplayAbilityHeroJobBase.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIGameplayAbilityHeroJobBase : public UXIGameplayAbility
{
	GENERATED_BODY()

public:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	UPROPERTY(EditAnywhere)
	UXIJobAbilityData* XIJobAbilityData;

};
