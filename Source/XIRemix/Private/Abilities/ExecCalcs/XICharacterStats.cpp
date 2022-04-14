// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/ExecCalcs/XICharacterStats.h"
#include "Abilities/XIAbilitySystemComponent.h"
#include "Abilities/AttributeSetGlobal.h"
#include "Characters/XICharacterBaseHero.h"
#include "DataAssets/XIStatsGrowthData.h"
#include "DataAssets/XIStatsGrowthRank.h"

struct XIBaseAttributesStatics
{
    DECLARE_ATTRIBUTE_CAPTUREDEF(HitPoints);
    DECLARE_ATTRIBUTE_CAPTUREDEF(HitPointsMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(ManaPoints);
    DECLARE_ATTRIBUTE_CAPTUREDEF(ManaPointsMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Strength);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Dexterity);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Vitality);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Agility);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Intelligence);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Mind);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Charisma);

    XIBaseAttributesStatics()
    {
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, HitPoints, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, HitPointsMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, ManaPoints, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, ManaPointsMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Strength, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Dexterity, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Vitality, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Agility, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Intelligence, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Mind, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Charisma, Target, false);
    }
};

static const XIBaseAttributesStatics& BaseAttributesStatics()
{
    static XIBaseAttributesStatics AStatics;
    return AStatics;
}

UXICharacterStats::UXICharacterStats()
{
    RelevantAttributesToCapture.Add(XIBaseAttributesStatics().HitPointsDef);
    RelevantAttributesToCapture.Add(XIBaseAttributesStatics().HitPointsMaxDef);
    RelevantAttributesToCapture.Add(XIBaseAttributesStatics().ManaPointsDef);
    RelevantAttributesToCapture.Add(XIBaseAttributesStatics().ManaPointsMaxDef);
    RelevantAttributesToCapture.Add(XIBaseAttributesStatics().StrengthDef);
    RelevantAttributesToCapture.Add(XIBaseAttributesStatics().DexterityDef);
    RelevantAttributesToCapture.Add(XIBaseAttributesStatics().VitalityDef);
    RelevantAttributesToCapture.Add(XIBaseAttributesStatics().AgilityDef);
    RelevantAttributesToCapture.Add(XIBaseAttributesStatics().IntelligenceDef);
    RelevantAttributesToCapture.Add(XIBaseAttributesStatics().MindDef);
    RelevantAttributesToCapture.Add(XIBaseAttributesStatics().CharismaDef);
}

void UXICharacterStats::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
    AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

    // Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.TargetTags = TargetTags;

    AXICharacterBaseHero* XICharacter = Cast<AXICharacterBaseHero>(TargetActor);
    UXIAbilitySystemComponent* XIASC = Cast<UXIAbilitySystemComponent>(TargetAbilitySystemComponent);
    if(!XICharacter || !XIASC)
    {
        UE_LOG(LogTemp, Error, TEXT("XICharacterStats Exec Calc: Target actor is not an XICharacter."));
        return;
    }

    UXIStatsGrowthData* RaceStatsGrowthData = XICharacter->GetXIStatsGrowthData();
    UXIStatsGrowthRank* RaceStatsGrowthRank = XICharacter->GetXIStatsGrowthRank();

    if(!RaceStatsGrowthData || !RaceStatsGrowthRank)
    {
        return;
    }

    FXICharacterHeroActiveJobsLevels HeroCharacterJobs = XICharacter->GetCharacterActiveJobsAndLevels();
    FXIJobTagRelationshipItem MainJobTagRelationship;
    FXIJobTagRelationshipItem SubJobTagRelationship;

    if (HeroCharacterJobs.MainJobTag.IsValid())
    {
        XIASC->GetXIJobTagRelationship(HeroCharacterJobs.MainJobTag, MainJobTagRelationship);
    }
    if (HeroCharacterJobs.SubJobTag.IsValid())
    {
        XIASC->GetXIJobTagRelationship(HeroCharacterJobs.SubJobTag, SubJobTagRelationship);
    }

    float MJScale = 0;
    float MJBase = 0;
    float MJMultiplier = 0;

    float SJScale = 0;
    float SJBase = 0;
    float SJMultiplier = 0;

    float RaceScale = 0;
    float RaceBase = 0;
    float RaceMultiplier = 0;

    /*
    // Calculate HP
    */
    HeroCharacterJobs.MainJobTag.IsValid() ? RaceStatsGrowthData->GetHitPointsGrowth(MainJobTagRelationship.StatsGrowthRank->HitPoints, MJScale, MJBase, MJMultiplier) : nullptr;
    HeroCharacterJobs.SubJobTag.IsValid() ? RaceStatsGrowthData->GetHitPointsGrowth(SubJobTagRelationship.StatsGrowthRank->HitPoints, SJScale, SJBase, SJMultiplier) : nullptr;
    RaceStatsGrowthData->GetHitPointsGrowth(RaceStatsGrowthRank->HitPoints, RaceScale, RaceBase, RaceMultiplier);
    float HPAttribute = CalculateHPAttribute(HeroCharacterJobs.MainJobLevel, HeroCharacterJobs.SubJobLevel, RaceScale, RaceBase, RaceMultiplier, MJScale, MJBase, MJMultiplier, SJScale, SJBase);

    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(BaseAttributesStatics().HitPointsMaxProperty, EGameplayModOp::Override, HPAttribute));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(BaseAttributesStatics().HitPointsProperty, EGameplayModOp::Override, HPAttribute));

    /*
    // Calculate MP
    */
    HeroCharacterJobs.MainJobTag.IsValid() ? RaceStatsGrowthData->GetManaPointsGrowth(MainJobTagRelationship.StatsGrowthRank->ManaPoints, MJScale, MJBase) : nullptr;
    HeroCharacterJobs.SubJobTag.IsValid() ? RaceStatsGrowthData->GetManaPointsGrowth(SubJobTagRelationship.StatsGrowthRank->ManaPoints, SJScale, SJBase) : nullptr;
    RaceStatsGrowthData->GetManaPointsGrowth(RaceStatsGrowthRank->ManaPoints, RaceScale, RaceBase);
    float MPAttribute = CalculateMPAttribute(HeroCharacterJobs.MainJobLevel, HeroCharacterJobs.SubJobLevel, RaceScale, RaceBase, MJScale, MJBase, SJScale, SJBase);

    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(BaseAttributesStatics().ManaPointsMaxProperty, EGameplayModOp::Override, MPAttribute));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(BaseAttributesStatics().ManaPointsProperty, EGameplayModOp::Override, MPAttribute));
    
    
    /*
    // Calculate Basic Attributes
    */
    float AttributeTotal;

    HeroCharacterJobs.MainJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(MainJobTagRelationship.StatsGrowthRank->Strength, MJScale, MJBase) : nullptr;
    HeroCharacterJobs.SubJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(SubJobTagRelationship.StatsGrowthRank->Strength, SJScale, SJBase) : nullptr;
    RaceStatsGrowthData->GetAttributeGrowth(RaceStatsGrowthRank->Strength, RaceScale, RaceBase);
    AttributeTotal = CalculateBasicAttribute(HeroCharacterJobs.MainJobLevel, HeroCharacterJobs.SubJobLevel, RaceScale, RaceBase, MJScale, MJBase, SJScale, SJBase);
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(BaseAttributesStatics().StrengthProperty, EGameplayModOp::Override, AttributeTotal));

    HeroCharacterJobs.MainJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(MainJobTagRelationship.StatsGrowthRank->Dexterity, MJScale, MJBase) : nullptr;
    HeroCharacterJobs.SubJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(SubJobTagRelationship.StatsGrowthRank->Dexterity, SJScale, SJBase) : nullptr;
    RaceStatsGrowthData->GetAttributeGrowth(RaceStatsGrowthRank->Dexterity, RaceScale, RaceBase);
    AttributeTotal = CalculateBasicAttribute(HeroCharacterJobs.MainJobLevel, HeroCharacterJobs.SubJobLevel, RaceScale, RaceBase, MJScale, MJBase, SJScale, SJBase);
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(BaseAttributesStatics().DexterityProperty, EGameplayModOp::Override, AttributeTotal));

    HeroCharacterJobs.MainJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(MainJobTagRelationship.StatsGrowthRank->Vitality, MJScale, MJBase) : nullptr;
    HeroCharacterJobs.SubJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(SubJobTagRelationship.StatsGrowthRank->Vitality, SJScale, SJBase) : nullptr;
    RaceStatsGrowthData->GetAttributeGrowth(RaceStatsGrowthRank->Vitality, RaceScale, RaceBase);
    AttributeTotal = CalculateBasicAttribute(HeroCharacterJobs.MainJobLevel, HeroCharacterJobs.SubJobLevel, RaceScale, RaceBase, MJScale, MJBase, SJScale, SJBase);
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(BaseAttributesStatics().VitalityProperty, EGameplayModOp::Override, AttributeTotal));

    HeroCharacterJobs.MainJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(MainJobTagRelationship.StatsGrowthRank->Agility, MJScale, MJBase) : nullptr;
    HeroCharacterJobs.SubJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(SubJobTagRelationship.StatsGrowthRank->Agility, SJScale, SJBase) : nullptr;
    RaceStatsGrowthData->GetAttributeGrowth(RaceStatsGrowthRank->Agility, RaceScale, RaceBase);
    AttributeTotal = CalculateBasicAttribute(HeroCharacterJobs.MainJobLevel, HeroCharacterJobs.SubJobLevel, RaceScale, RaceBase, MJScale, MJBase, SJScale, SJBase);
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(BaseAttributesStatics().AgilityProperty, EGameplayModOp::Override, AttributeTotal));

    HeroCharacterJobs.MainJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(MainJobTagRelationship.StatsGrowthRank->Intelligence, MJScale, MJBase) : nullptr;
    HeroCharacterJobs.SubJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(SubJobTagRelationship.StatsGrowthRank->Intelligence, SJScale, SJBase) : nullptr;
    RaceStatsGrowthData->GetAttributeGrowth(RaceStatsGrowthRank->Intelligence, RaceScale, RaceBase);
    AttributeTotal = CalculateBasicAttribute(HeroCharacterJobs.MainJobLevel, HeroCharacterJobs.SubJobLevel, RaceScale, RaceBase, MJScale, MJBase, SJScale, SJBase);
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(BaseAttributesStatics().IntelligenceProperty, EGameplayModOp::Override, AttributeTotal));

    HeroCharacterJobs.MainJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(MainJobTagRelationship.StatsGrowthRank->Mind, MJScale, MJBase) : nullptr;
    HeroCharacterJobs.SubJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(SubJobTagRelationship.StatsGrowthRank->Mind, SJScale, SJBase) : nullptr;
    RaceStatsGrowthData->GetAttributeGrowth(RaceStatsGrowthRank->Mind, RaceScale, RaceBase);
    AttributeTotal = CalculateBasicAttribute(HeroCharacterJobs.MainJobLevel, HeroCharacterJobs.SubJobLevel, RaceScale, RaceBase, MJScale, MJBase, SJScale, SJBase);
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(BaseAttributesStatics().MindProperty, EGameplayModOp::Override, AttributeTotal));

    HeroCharacterJobs.MainJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(MainJobTagRelationship.StatsGrowthRank->Charisma, MJScale, MJBase) : nullptr;
    HeroCharacterJobs.SubJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(SubJobTagRelationship.StatsGrowthRank->Charisma, SJScale, SJBase) : nullptr;
    RaceStatsGrowthData->GetAttributeGrowth(RaceStatsGrowthRank->Charisma, RaceScale, RaceBase);
    AttributeTotal = CalculateBasicAttribute(HeroCharacterJobs.MainJobLevel, HeroCharacterJobs.SubJobLevel, RaceScale, RaceBase, MJScale, MJBase, SJScale, SJBase);
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(BaseAttributesStatics().CharismaProperty, EGameplayModOp::Override, AttributeTotal));
}

float UXICharacterStats::CalculateHPAttribute(float MainJobLevel, float SubJobLevel, float RaceHPScale, float RaceHPBase, float RaceHPMultiplier, float MJHPScale, float MJHPBase, float MJHPMulitiplier, float SJHPScale, float SJHPBase) const
{
    float RaceHP = FMath::Floor((RaceHPScale * (MainJobLevel - 1.f)) + RaceHPBase + (2.f * FMath::Max(MainJobLevel - 10.f, 0.f)) + (RaceHPMultiplier * FMath::Max(MainJobLevel - 30.f, 0.f)));
    float MJHP = FMath::Floor(MJHPScale * (MainJobLevel - 1.f)) + MJHPBase + (MJHPMulitiplier * FMath::Max(MainJobLevel - 30.f, 0.f));
    float SJHP = FMath::Floor(((SJHPScale * (SubJobLevel - 1.f) + SJHPBase + FMath::Max(SubJobLevel - 10.f, 0.f)) / 2.f));
    
    return RaceHP + MJHP + SJHP;
}

float UXICharacterStats::CalculateMPAttribute(float MainJobLevel, float SubJobLevel, float RaceMPScale, float RaceMPBase, float MJMPScale, float MJMPBase, float SJMPScale, float SJMPBase) const
{
    float RaceMP;
    float MJMP;
    float SJMP;

    if (MJMPScale == 0.f && SJMPScale == 0.f)
    {
        RaceMP = 0.f;
    }
    else if (MJMPScale > 0.f)
    {
        RaceMP = FMath::Floor(RaceMPScale * (MainJobLevel - 1.f) + RaceMPBase);
    }
    else
    {
        RaceMP = FMath::Floor((RaceMPScale * (SubJobLevel - 1.f) + RaceMPBase) / 2.f);
    }
    
    MJMP = FMath::Floor(MJMPScale * (MainJobLevel - 1.f) + MJMPBase);
    SJMP = FMath::Floor((SJMPScale * (SubJobLevel - 1.f) + SJMPBase) / 2.f);

    return RaceMP + MJMP + SJMP;
}

float UXICharacterStats::CalculateBasicAttribute(float MainJobLevel, float SubJobLevel, float RaceScale, float RaceBase, float MJScale, float MJBase, float SJScale, float SJBase) const
{
    float Race = FMath::Floor(RaceScale * (MainJobLevel - 1.f) + RaceBase);
    float MJ = FMath::Floor(MJScale * (MainJobLevel - 1.f) + MJBase);
    float SJ = FMath::Floor((SJScale * (SubJobLevel - 1.f) + SJBase) / 2.f);

    return Race + MJ + SJ;
}