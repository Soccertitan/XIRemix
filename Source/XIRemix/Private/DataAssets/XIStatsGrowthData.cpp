// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/XIStatsGrowthData.h"

void UXIStatsGrowthData::GetHitPointsGrowth(EXISkillRank GrowthRank, float& OutHitPointsScale, float& OutHitPointsBase, float& OutHitPointsMultiplier) const
{
    for (const FXIStatsGrowthDataItem& GrowthData : XIStatsGrowthData)
    {
        if(GrowthData.StatGrowthRank == GrowthRank)
        {
            OutHitPointsScale = GrowthData.HitPointsScale;
            OutHitPointsBase = GrowthData.HitPointsBase;
            OutHitPointsMultiplier = GrowthData.HitPointsMultiplier;
            return;
        }
    }

    OutHitPointsScale = 0.f;
    OutHitPointsBase = 0.f;
    OutHitPointsMultiplier = 0.f;
}

void UXIStatsGrowthData::GetManaPointsGrowth(EXISkillRank GrowthRank, float& OutManaPointsScale, float& OutManaPointsBase) const
{
    for (const FXIStatsGrowthDataItem& GrowthData : XIStatsGrowthData)
    {
        if(GrowthData.StatGrowthRank == GrowthRank)
        {
            OutManaPointsBase = GrowthData.ManaPointsBase;
            OutManaPointsScale = GrowthData.ManaPointsScale;
            return;
        }
    }

    OutManaPointsBase = 0.f;
    OutManaPointsScale = 0.f;
}

void UXIStatsGrowthData::GetAttributeGrowth(EXISkillRank GrowthRank, float& OutAttributeScale, float& OutAttributeBase) const
{
    for (const FXIStatsGrowthDataItem& GrowthData : XIStatsGrowthData)
    {
        if(GrowthData.StatGrowthRank == GrowthRank)
        {
            OutAttributeBase = GrowthData.AttributeBase;
            OutAttributeScale = GrowthData.AttributeScale;
            return;
        }
    }

    OutAttributeBase = 0.f;
    OutAttributeScale = 0.f;
}