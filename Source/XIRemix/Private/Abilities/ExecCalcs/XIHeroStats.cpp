// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/ExecCalcs/XIHeroStats.h"
#include "Abilities/XIAbilitySystemComponent.h"
#include "Abilities/AttributeSetGlobal.h"
#include "Characters/XICharacterBaseHero.h"
#include "DataAssets/XIStatsGrowthData.h"
#include "DataAssets/XIStatsGrowthRank.h"
#include "DataAssets/XICombatSkillsRank.h"

struct XIHeroAttributesStatics
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

    DECLARE_ATTRIBUTE_CAPTUREDEF(AxeSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(GreatAxeSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(ClubSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(DaggerSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(HandToHandSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(KatanaSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(GreatKatanaSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(PolearmSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(ScytheSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(StaffSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(SwordSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(GreatSwordSkillMax);

    DECLARE_ATTRIBUTE_CAPTUREDEF(ArcherySkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(MarksmanshipSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(ThrowingSkillMax);

    DECLARE_ATTRIBUTE_CAPTUREDEF(EvasionSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(GuardSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(ParrySkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(ShieldSkillMax);

    DECLARE_ATTRIBUTE_CAPTUREDEF(BlueMagicSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(DarkMagicSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(DivineMagicSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(ElementalMagicSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(EnfeeblingMagicSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(EnhancingMagicSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(HealingMagicSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(SummoningMagicSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(NinjutsuSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(SingingSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(StringSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(WindSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(GeomancySkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(HandbellSkillMax);

    XIHeroAttributesStatics()
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

        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, AxeSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, GreatAxeSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, ClubSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, DaggerSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, HandToHandSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, KatanaSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, GreatKatanaSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, PolearmSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, ScytheSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, StaffSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, SwordSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, GreatSwordSkillMax, Target, false);

        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, ArcherySkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, MarksmanshipSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, ThrowingSkillMax, Target, false);

        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, EvasionSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, GuardSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, ParrySkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, ShieldSkillMax, Target, false);

        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, BlueMagicSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, DarkMagicSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, DivineMagicSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, ElementalMagicSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, EnfeeblingMagicSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, EnhancingMagicSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, HealingMagicSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, SummoningMagicSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, NinjutsuSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, SingingSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, StringSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, WindSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, GeomancySkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, HandbellSkillMax, Target, false);
    }
};

static const XIHeroAttributesStatics& HeroAttributesStatics()
{
    static XIHeroAttributesStatics AStatics;
    return AStatics;
}

UXIHeroStats::UXIHeroStats()
{
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().HitPointsDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().HitPointsMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().ManaPointsDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().ManaPointsMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().StrengthDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().DexterityDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().VitalityDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().AgilityDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().IntelligenceDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().MindDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().CharismaDef);

    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().AxeSkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().GreatAxeSkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().ClubSkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().DaggerSkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().HandToHandSkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().KatanaSkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().GreatKatanaSkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().PolearmSkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().ScytheSkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().StaffSkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().SwordSkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().GreatSwordSkillMaxDef);

    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().ArcherySkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().MarksmanshipSkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().ThrowingSkillMaxDef);

    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().EvasionSkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().GuardSkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().ParrySkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().ShieldSkillMaxDef);

    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().BlueMagicSkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().DarkMagicSkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().DivineMagicSkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().ElementalMagicSkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().EnfeeblingMagicSkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().EnhancingMagicSkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().HealingMagicSkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().SummoningMagicSkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().NinjutsuSkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().SingingSkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().StringSkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().WindSkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().GeomancySkillMaxDef);
    RelevantAttributesToCapture.Add(XIHeroAttributesStatics().HandbellSkillMaxDef);
}

void UXIHeroStats::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
    AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

    AXICharacterBaseHero* XICharacter = Cast<AXICharacterBaseHero>(TargetActor);
    UXIAbilitySystemComponent* XIASC = Cast<UXIAbilitySystemComponent>(TargetAbilitySystemComponent);
    if(!XICharacter || !XIASC)
    {
        UE_LOG(LogTemp, Error, TEXT("XIHeroStats Exec Calc: Target actor is not an XICharacterBaseHero."));
        return;
    }

    UXIStatsGrowthData* RaceStatsGrowthData = XICharacter->GetXIStatsGrowthData();
    UXIStatsGrowthRank* RaceStatsGrowthRank = XICharacter->GetXIStatsGrowthRank();
    UCurveTable* SkillRankCT = XICharacter->GetSkillRankCurveTable();

    if(!RaceStatsGrowthData || !RaceStatsGrowthRank || !SkillRankCT)
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

    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().HitPointsMaxProperty, EGameplayModOp::Override, HPAttribute));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().HitPointsProperty, EGameplayModOp::Override, HPAttribute));

    /*
    // Calculate MP
    */
    HeroCharacterJobs.MainJobTag.IsValid() ? RaceStatsGrowthData->GetManaPointsGrowth(MainJobTagRelationship.StatsGrowthRank->ManaPoints, MJScale, MJBase) : nullptr;
    HeroCharacterJobs.SubJobTag.IsValid() ? RaceStatsGrowthData->GetManaPointsGrowth(SubJobTagRelationship.StatsGrowthRank->ManaPoints, SJScale, SJBase) : nullptr;
    RaceStatsGrowthData->GetManaPointsGrowth(RaceStatsGrowthRank->ManaPoints, RaceScale, RaceBase);
    float MPAttribute = CalculateMPAttribute(HeroCharacterJobs.MainJobLevel, HeroCharacterJobs.SubJobLevel, RaceScale, RaceBase, MJScale, MJBase, SJScale, SJBase);

    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().ManaPointsMaxProperty, EGameplayModOp::Override, MPAttribute));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().ManaPointsProperty, EGameplayModOp::Override, MPAttribute));
    
    /*
    // Calculate Basic Attributes
    */
    float AttributeTotal;

    HeroCharacterJobs.MainJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(MainJobTagRelationship.StatsGrowthRank->Strength, MJScale, MJBase) : nullptr;
    HeroCharacterJobs.SubJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(SubJobTagRelationship.StatsGrowthRank->Strength, SJScale, SJBase) : nullptr;
    RaceStatsGrowthData->GetAttributeGrowth(RaceStatsGrowthRank->Strength, RaceScale, RaceBase);
    AttributeTotal = CalculateBasicAttribute(HeroCharacterJobs.MainJobLevel, HeroCharacterJobs.SubJobLevel, RaceScale, RaceBase, MJScale, MJBase, SJScale, SJBase);
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().StrengthProperty, EGameplayModOp::Override, AttributeTotal));

    HeroCharacterJobs.MainJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(MainJobTagRelationship.StatsGrowthRank->Dexterity, MJScale, MJBase) : nullptr;
    HeroCharacterJobs.SubJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(SubJobTagRelationship.StatsGrowthRank->Dexterity, SJScale, SJBase) : nullptr;
    RaceStatsGrowthData->GetAttributeGrowth(RaceStatsGrowthRank->Dexterity, RaceScale, RaceBase);
    AttributeTotal = CalculateBasicAttribute(HeroCharacterJobs.MainJobLevel, HeroCharacterJobs.SubJobLevel, RaceScale, RaceBase, MJScale, MJBase, SJScale, SJBase);
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().DexterityProperty, EGameplayModOp::Override, AttributeTotal));

    HeroCharacterJobs.MainJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(MainJobTagRelationship.StatsGrowthRank->Vitality, MJScale, MJBase) : nullptr;
    HeroCharacterJobs.SubJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(SubJobTagRelationship.StatsGrowthRank->Vitality, SJScale, SJBase) : nullptr;
    RaceStatsGrowthData->GetAttributeGrowth(RaceStatsGrowthRank->Vitality, RaceScale, RaceBase);
    AttributeTotal = CalculateBasicAttribute(HeroCharacterJobs.MainJobLevel, HeroCharacterJobs.SubJobLevel, RaceScale, RaceBase, MJScale, MJBase, SJScale, SJBase);
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().VitalityProperty, EGameplayModOp::Override, AttributeTotal));

    HeroCharacterJobs.MainJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(MainJobTagRelationship.StatsGrowthRank->Agility, MJScale, MJBase) : nullptr;
    HeroCharacterJobs.SubJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(SubJobTagRelationship.StatsGrowthRank->Agility, SJScale, SJBase) : nullptr;
    RaceStatsGrowthData->GetAttributeGrowth(RaceStatsGrowthRank->Agility, RaceScale, RaceBase);
    AttributeTotal = CalculateBasicAttribute(HeroCharacterJobs.MainJobLevel, HeroCharacterJobs.SubJobLevel, RaceScale, RaceBase, MJScale, MJBase, SJScale, SJBase);
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().AgilityProperty, EGameplayModOp::Override, AttributeTotal));

    HeroCharacterJobs.MainJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(MainJobTagRelationship.StatsGrowthRank->Intelligence, MJScale, MJBase) : nullptr;
    HeroCharacterJobs.SubJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(SubJobTagRelationship.StatsGrowthRank->Intelligence, SJScale, SJBase) : nullptr;
    RaceStatsGrowthData->GetAttributeGrowth(RaceStatsGrowthRank->Intelligence, RaceScale, RaceBase);
    AttributeTotal = CalculateBasicAttribute(HeroCharacterJobs.MainJobLevel, HeroCharacterJobs.SubJobLevel, RaceScale, RaceBase, MJScale, MJBase, SJScale, SJBase);
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().IntelligenceProperty, EGameplayModOp::Override, AttributeTotal));

    HeroCharacterJobs.MainJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(MainJobTagRelationship.StatsGrowthRank->Mind, MJScale, MJBase) : nullptr;
    HeroCharacterJobs.SubJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(SubJobTagRelationship.StatsGrowthRank->Mind, SJScale, SJBase) : nullptr;
    RaceStatsGrowthData->GetAttributeGrowth(RaceStatsGrowthRank->Mind, RaceScale, RaceBase);
    AttributeTotal = CalculateBasicAttribute(HeroCharacterJobs.MainJobLevel, HeroCharacterJobs.SubJobLevel, RaceScale, RaceBase, MJScale, MJBase, SJScale, SJBase);
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().MindProperty, EGameplayModOp::Override, AttributeTotal));

    HeroCharacterJobs.MainJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(MainJobTagRelationship.StatsGrowthRank->Charisma, MJScale, MJBase) : nullptr;
    HeroCharacterJobs.SubJobTag.IsValid() ? RaceStatsGrowthData->GetAttributeGrowth(SubJobTagRelationship.StatsGrowthRank->Charisma, SJScale, SJBase) : nullptr;
    RaceStatsGrowthData->GetAttributeGrowth(RaceStatsGrowthRank->Charisma, RaceScale, RaceBase);
    AttributeTotal = CalculateBasicAttribute(HeroCharacterJobs.MainJobLevel, HeroCharacterJobs.SubJobLevel, RaceScale, RaceBase, MJScale, MJBase, SJScale, SJBase);
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().CharismaProperty, EGameplayModOp::Override, AttributeTotal));

    /*
    // Get the Combat skill ranking for MainJob and SubJob and take the highest value.
    */
    //Melee Combat Skills
    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Axe));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Axe));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().AxeSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));

    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->GreatAxe));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->GreatAxe));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().GreatAxeSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));

    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Club));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Club));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().ClubSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));

    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Dagger));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Dagger));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().DaggerSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));

    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->HandToHand));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->HandToHand));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().HandToHandSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));

    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Katana));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Katana));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().KatanaSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));

    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->GreatKatana));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->GreatKatana));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().GreatKatanaSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));

    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Polearm));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Polearm));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().PolearmSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));

    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Scythe));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Scythe));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().ScytheSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));

    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Staff));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Staff));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().StaffSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));

    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Sword));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Sword));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().SwordSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));

    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->GreatSword));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->GreatSword));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().GreatSwordSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));


    //Ranged Combat Skills
    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Archery));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Archery));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().ArcherySkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));
    
    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Marksmanship));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Marksmanship));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().MarksmanshipSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));
    
    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Throwing));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Throwing));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().ThrowingSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));


    //Defensive Combat Skills
    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Evasion));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Evasion));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().EvasionSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));
    
    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Guard));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Guard));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().GuardSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));
    
    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Parry));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Parry));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().ParrySkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));
    
    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Shield));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Shield));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().ShieldSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));

    
    //Special Combat Skills
    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Blue));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Blue));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().BlueMagicSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));

    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Dark));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Dark));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().DarkMagicSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));

    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Divine));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Divine));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().DivineMagicSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));

    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Elemental));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Elemental));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().ElementalMagicSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));

    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Enfeebling));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Enfeebling));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().EnfeeblingMagicSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));

    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Enhancing));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Enhancing));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().EnhancingMagicSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));

    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Healing));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Healing));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().HealingMagicSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));

    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Summoning));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Summoning));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().SummoningMagicSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));

    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Ninjutsu));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Ninjutsu));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().NinjutsuSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));

    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Singing));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Singing));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().SingingSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));

    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->String));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->String));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().StringSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));

    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Wind));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Wind));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().WindSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));

    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Geomancy));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Geomancy));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().GeomancySkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));

    if(HeroCharacterJobs.MainJobTag.IsValid()) MJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.MainJobLevel, *SkillRankNameMap.Find(MainJobTagRelationship.CombatSkillsRank->Handbell));
    if(HeroCharacterJobs.SubJobTag.IsValid()) SJBase = GetSkillRankValue(SkillRankCT, HeroCharacterJobs.SubJobLevel, *SkillRankNameMap.Find(SubJobTagRelationship.CombatSkillsRank->Handbell));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HeroAttributesStatics().HandbellSkillMaxProperty, EGameplayModOp::Override, FMath::Max(MJBase, SJBase)));
}

float UXIHeroStats::CalculateHPAttribute(float MainJobLevel, float SubJobLevel, float RaceHPScale, float RaceHPBase, float RaceHPMultiplier, float MJHPScale, float MJHPBase, float MJHPMulitiplier, float SJHPScale, float SJHPBase) const
{
    float RaceHP = FMath::Floor((RaceHPScale * (MainJobLevel - 1.f)) + RaceHPBase + (2.f * FMath::Max(MainJobLevel - 10.f, 0.f)) + (RaceHPMultiplier * FMath::Max(MainJobLevel - 30.f, 0.f)));
    float MJHP = FMath::Floor(MJHPScale * (MainJobLevel - 1.f)) + MJHPBase + (MJHPMulitiplier * FMath::Max(MainJobLevel - 30.f, 0.f));
    float SJHP = FMath::Floor(((SJHPScale * (SubJobLevel - 1.f) + SJHPBase + FMath::Max(SubJobLevel - 10.f, 0.f)) / 2.f));
    
    return RaceHP + MJHP + SJHP;
}

float UXIHeroStats::CalculateMPAttribute(float MainJobLevel, float SubJobLevel, float RaceMPScale, float RaceMPBase, float MJMPScale, float MJMPBase, float SJMPScale, float SJMPBase) const
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

float UXIHeroStats::CalculateBasicAttribute(float MainJobLevel, float SubJobLevel, float RaceScale, float RaceBase, float MJScale, float MJBase, float SJScale, float SJBase) const
{
    float Race = FMath::Floor(RaceScale * (MainJobLevel - 1.f) + RaceBase);
    float MJ = FMath::Floor(MJScale * (MainJobLevel - 1.f) + MJBase);
    float SJ = FMath::Floor((SJScale * (SubJobLevel - 1.f) + SJBase) / 2.f);

    return Race + MJ + SJ;
}

float UXIHeroStats::GetSkillRankValue(UCurveTable* CurveTable, float Level, FName RowName) const
{
    static const FString ContextString(TEXT("Getting Skill Rank Value"));
    float Value = 0.f;

    FCurveTableRowHandle SkillRankHandle;
    SkillRankHandle.CurveTable = CurveTable;
    SkillRankHandle.RowName = RowName;

    SkillRankHandle.Eval(Level, &Value,ContextString);

    return Value;
}

const TMap<EXISkillRank, FName> UXIHeroStats::SkillRankNameMap = {
    {EXISkillRank::APlus, "APlus"},
    {EXISkillRank::A, "A"},
    {EXISkillRank::AMinus, "AMinus"},
    {EXISkillRank::BPlus, "BPlus"},
    {EXISkillRank::B, "B"},
    {EXISkillRank::BMinus, "BMinus"},
    {EXISkillRank::CPlus, "CPlus"},
    {EXISkillRank::C, "C"},
    {EXISkillRank::CMinus, "CMinus"},
    {EXISkillRank::D, "D"},
    {EXISkillRank::E, "E"},
    {EXISkillRank::F, "F"},
    {EXISkillRank::G, "G"},
    {EXISkillRank::H, "H"}
};
