// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/XIJobTagRelationship.h"

bool UXIJobTagRelationship::GetXIJobTagRelationship(FGameplayTag InJobTag, FXIJobTagRelationshipItem& JobTagRelationship)
{
    for(const FXIJobTagRelationshipItem& Relationship : JobTagRelationships)
    {
        if(InJobTag.MatchesAnyExact(Relationship.JobTags))
        {
            JobTagRelationship = Relationship;
            return true;
        }
    }
    return false;
}