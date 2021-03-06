// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "XIAbilityTagRelationship.generated.h"

/*
 * Defines the relationship between different ability tags
 */
USTRUCT()
struct FXIAbilityTagRelationshipItem
{
    GENERATED_BODY()
 
    /* The tag that this relationship is about. */
    UPROPERTY(EditAnywhere, Category = Ability)
    FGameplayTag AbilityTag;
 
    /* This ability tag will block abilities matching these tags */
    UPROPERTY(EditAnywhere, Category = Tags)
    FGameplayTagContainer AbilityTagsToBlock;
 
    /* This ability tag will cancel abilities matching these tags */
    UPROPERTY(EditAnywhere, Category = Tags)
    FGameplayTagContainer AbilityTagsToCancel;
 
    /* This ability tag will add these tags to the Activation Required Tags */
    UPROPERTY(EditAnywhere, Category = Tags)
    FGameplayTagContainer ActivationRequiredTags;
 
    /* This ability tag will add these tags to the Activation Blocked Tags */
    UPROPERTY(EditAnywhere, Category = Tags)
    FGameplayTagContainer ActivationBlockedTags;
 
};

/**
 * Mapping of how ability tags block or cancel other abilities, and additional activation
 * required and blocked tags. 
 */
UCLASS()
class XIREMIX_API UXIAbilityTagRelationship : public UDataAsset
{
	GENERATED_BODY()
	
public:
    /* Fill out tags to block and cancel matching the AbilityTags passed in */
    void GetAbilityTagsToBlockAndCancel(const FGameplayTagContainer& AbilityTags, FGameplayTagContainer* OutTagsToBlock, FGameplayTagContainer* OutTagsToCancel) const;
 
    /* Add additional required and blocking tags matching the passed in AbilityTags */
    void GetActivationRequiredAndBlockedTags(const FGameplayTagContainer& AbilityTags, FGameplayTagContainer* OutActivationRequired, FGameplayTagContainer* OutActivationBlocked) const;
 
private:
    /* The list of relationships between different ability gameplay tags */
    UPROPERTY(EditAnywhere)
    TArray<FXIAbilityTagRelationshipItem> AbilityTagRelationships;
};
