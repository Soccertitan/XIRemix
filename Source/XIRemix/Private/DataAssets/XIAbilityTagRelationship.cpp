// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/XIAbilityTagRelationship.h"

void UXIAbilityTagRelationship::GetAbilityTagsToBlockAndCancel(const FGameplayTagContainer& AbilityTags, FGameplayTagContainer* OutTagsToBlock, FGameplayTagContainer* OutTagsToCancel) const
{
    for (const FXIAbilityTagRelationshipItem& Relationship : AbilityTagRelationships)
    {
        if (AbilityTags.HasTag(Relationship.AbilityTag))
        {
            if (OutTagsToBlock)
            {
                OutTagsToBlock->AppendTags(Relationship.AbilityTagsToBlock);
            }
             
            if (OutTagsToCancel)
            {
                OutTagsToCancel->AppendTags(Relationship.AbilityTagsToCancel);
            }
        }
    }
}
 
void UXIAbilityTagRelationship::GetActivationRequiredAndBlockedTags(const FGameplayTagContainer& AbilityTags, FGameplayTagContainer* OutActivationRequired, FGameplayTagContainer* OutActivationBlocked) const
{
    for (const FXIAbilityTagRelationshipItem& Relationship : AbilityTagRelationships)
    {
        if (AbilityTags.HasTag(Relationship.AbilityTag))
        {
            if (OutActivationRequired)
            {
                OutActivationRequired->AppendTags(Relationship.ActivationRequiredTags);
            }
 
            if (OutActivationBlocked)
            {
                OutActivationBlocked->AppendTags(Relationship.ActivationBlockedTags);
            }
        }
    }
}