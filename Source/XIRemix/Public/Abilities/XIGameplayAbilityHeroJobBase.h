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
	UXIGameplayAbilityHeroJobBase();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	//A Data Asset containing an array of abilities and passives to grant the hero.
	UPROPERTY(EditAnywhere, Category = "Ability|Job")
	UXIJobAbilityData* XIJobAbilityData;

	//An instant GE with an execution class to set the characters attributes.
	UPROPERTY(EditAnywhere, Category = "Ability|Job")
	TSubclassOf<class UGameplayEffect> AttributeGE;

	//An infinite duration GE that temporarily sets the SubJob Level.
	UPROPERTY(EditAnywhere, Category = "Ability|Job")
	TSubclassOf<class UGameplayEffect> LevelAdjustmentGE;

	FActiveGameplayEffectHandle LevelAdjustmentHandle;

	float GetCharacterLevel();

};
