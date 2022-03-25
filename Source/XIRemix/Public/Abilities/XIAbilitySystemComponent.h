// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DataAssets/XIAbilityTagRelationship.h"
#include "DataAssets/XIJobTagRelationship.h"
#include "XIAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReceivedCombatExpDelegate, float, ExpGained);

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	UXIAbilitySystemComponent();
	
	bool CharacterAbilitiesGiven = false;
	bool StartupEffectsApplied = false;

	void GetRelationshipActivationTagRequirements(const FGameplayTagContainer& AbilityTags, FGameplayTagContainer& OutActivationRequired, FGameplayTagContainer& OutActivationBlocked) const;
	virtual void ApplyAbilityBlockAndCancelTags(const FGameplayTagContainer& AbilityTags, UGameplayAbility* RequestingAbility, bool bEnableBlockTags, const FGameplayTagContainer& BlockTags, bool bExecuteCancelTags, const FGameplayTagContainer& CancelTags) override;
	
	FReceivedCombatExpDelegate ReceivedCombatExp;
	virtual void ReceiveCombatExp(float ExpGained);
	virtual void GetXIJobTagRelationship(const FGameplayTag JobTag, FXIJobTagRelationshipItem& JobTagRelationshipItem) const;

protected:
    /* Mapping of Ability Tag to block and cancel tags. */
    UPROPERTY(EditDefaultsOnly, Category = "Abilities|GameplayTags")
    UXIAbilityTagRelationship* AbilityTagRelationship;

	/* Mapping of Job Tags to Attributes*/
	UPROPERTY(EditDefaultsOnly, Category = "Abilities|GameplayTags")
	UXIJobTagRelationship* JobTagRelationship;
};
