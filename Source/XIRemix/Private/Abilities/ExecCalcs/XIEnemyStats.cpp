// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/ExecCalcs/XIEnemyStats.h"
#include "Abilities/Enemy/AttributeSetEnemy.h"
#include "Abilities/XIAbilitySystemComponent.h"

struct XIEnemyAttributesStatics
{
    DECLARE_ATTRIBUTE_CAPTUREDEF(Level);

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

    DECLARE_ATTRIBUTE_CAPTUREDEF(WeaponDamage);
    DECLARE_ATTRIBUTE_CAPTUREDEF(RangedWeaponDamage);

    DECLARE_ATTRIBUTE_CAPTUREDEF(Attack);
    DECLARE_ATTRIBUTE_CAPTUREDEF(RangedAttack);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Defense);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Evasion);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Accuracy);
    DECLARE_ATTRIBUTE_CAPTUREDEF(RangedAccuracy);
    DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitRate);
    DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitBonus);
    DECLARE_ATTRIBUTE_CAPTUREDEF(RangedCriticalHitRate);
    DECLARE_ATTRIBUTE_CAPTUREDEF(RangedCriticalHitBonus);
    DECLARE_ATTRIBUTE_CAPTUREDEF(AttackDelay);
    DECLARE_ATTRIBUTE_CAPTUREDEF(AttackSpeed);
    DECLARE_ATTRIBUTE_CAPTUREDEF(RangedAttackDelay);
    DECLARE_ATTRIBUTE_CAPTUREDEF(RangedAttackSpeed);

    DECLARE_ATTRIBUTE_CAPTUREDEF(MagicAttack);
    DECLARE_ATTRIBUTE_CAPTUREDEF(MagicAccuracy);
    DECLARE_ATTRIBUTE_CAPTUREDEF(MagicEvasion);
    DECLARE_ATTRIBUTE_CAPTUREDEF(MagicCriticalHitRate);
    DECLARE_ATTRIBUTE_CAPTUREDEF(MagicCriticalHitBonus);
    DECLARE_ATTRIBUTE_CAPTUREDEF(CastSpeed);

    DECLARE_ATTRIBUTE_CAPTUREDEF(BluntResistance);
    DECLARE_ATTRIBUTE_CAPTUREDEF(PierceResistance);
    DECLARE_ATTRIBUTE_CAPTUREDEF(SlashResistance);

    DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
    DECLARE_ATTRIBUTE_CAPTUREDEF(IceResistance);
    DECLARE_ATTRIBUTE_CAPTUREDEF(WindResistance);
    DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
    DECLARE_ATTRIBUTE_CAPTUREDEF(EarthResistance);
    DECLARE_ATTRIBUTE_CAPTUREDEF(WaterResistance);
    DECLARE_ATTRIBUTE_CAPTUREDEF(LightResistance);
    DECLARE_ATTRIBUTE_CAPTUREDEF(DarkResistance);

    DECLARE_ATTRIBUTE_CAPTUREDEF(AmnesiaResistance);
    DECLARE_ATTRIBUTE_CAPTUREDEF(BindResistance);
    DECLARE_ATTRIBUTE_CAPTUREDEF(BlindResistance);
    DECLARE_ATTRIBUTE_CAPTUREDEF(GravityResistance);
    DECLARE_ATTRIBUTE_CAPTUREDEF(ParalyzeResistance);
    DECLARE_ATTRIBUTE_CAPTUREDEF(PetrifyResistance);
    DECLARE_ATTRIBUTE_CAPTUREDEF(PoisonResistance);
    DECLARE_ATTRIBUTE_CAPTUREDEF(SilenceResistance);
    DECLARE_ATTRIBUTE_CAPTUREDEF(SleepResistance);
    DECLARE_ATTRIBUTE_CAPTUREDEF(SlowResistance);
    DECLARE_ATTRIBUTE_CAPTUREDEF(VirusResistance);

    DECLARE_ATTRIBUTE_CAPTUREDEF(MoveSpeed);
    DECLARE_ATTRIBUTE_CAPTUREDEF(CurePotency);
    DECLARE_ATTRIBUTE_CAPTUREDEF(CureReceivedPotency);
    DECLARE_ATTRIBUTE_CAPTUREDEF(DamageResist);
    DECLARE_ATTRIBUTE_CAPTUREDEF(SpellInterruption);
    
    DECLARE_ATTRIBUTE_CAPTUREDEF(GuardSkill);
    DECLARE_ATTRIBUTE_CAPTUREDEF(GuardSkillMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(ParrySkill);
    DECLARE_ATTRIBUTE_CAPTUREDEF(ParrySkillMax);

    DECLARE_ATTRIBUTE_CAPTUREDEF(ExpBounty);

    XIEnemyAttributesStatics()
    {
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetEnemy, Level, Target, false);

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

        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetEnemy, WeaponDamage, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetEnemy, RangedWeaponDamage, Target, false);

        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Attack, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, RangedAttack, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Defense, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Evasion, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Accuracy, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, RangedAccuracy, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, CriticalHitRate, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, CriticalHitBonus, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, RangedCriticalHitRate, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, RangedCriticalHitBonus, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, AttackDelay, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, AttackSpeed, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, RangedAttackDelay, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, RangedAttackSpeed, Target, false);

        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, MagicAttack, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, MagicAccuracy, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, MagicEvasion, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, MagicCriticalHitRate, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, MagicCriticalHitBonus, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, CastSpeed, Target, false);

        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, BluntResistance, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, PierceResistance, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, SlashResistance, Target, false);

        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, FireResistance, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, IceResistance, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, WindResistance, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, LightningResistance, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, EarthResistance, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, WaterResistance, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, LightResistance, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, DarkResistance, Target, false);

        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, AmnesiaResistance, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, BindResistance, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, BlindResistance, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, GravityResistance, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, ParalyzeResistance, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, PetrifyResistance, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, PoisonResistance, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, SilenceResistance, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, SleepResistance, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, SlowResistance, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, VirusResistance, Target, false);

        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, MoveSpeed, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, CurePotency, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, CureReceivedPotency, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, DamageResist, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, SpellInterruption, Target, false);

        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, GuardSkill, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, GuardSkillMax, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, ParrySkill, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, ParrySkillMax, Target, false);

        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetEnemy, ExpBounty, Target, false);
    }
};

static const XIEnemyAttributesStatics& EnemyAttributesStatics()
{
    static XIEnemyAttributesStatics AStatics;
    return AStatics;
}

UXIEnemyStats::UXIEnemyStats()
{
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().LevelDef);

    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().HitPointsDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().HitPointsMaxDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().ManaPointsDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().ManaPointsMaxDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().StrengthDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().DexterityDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().VitalityDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().AgilityDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().IntelligenceDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().MindDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().CharismaDef);

    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().WeaponDamageDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().RangedWeaponDamageDef);

    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().AttackDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().RangedAttackDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().DefenseDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().EvasionDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().AccuracyDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().RangedAccuracyDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().CriticalHitRateDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().CriticalHitBonusDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().RangedCriticalHitRateDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().RangedCriticalHitBonusDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().AttackDelayDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().AttackSpeedDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().RangedAttackDelayDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().RangedAttackSpeedDef);

    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().MagicAttackDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().MagicAccuracyDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().MagicEvasionDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().MagicCriticalHitRateDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().MagicCriticalHitBonusDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().CastSpeedDef);

    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().BluntResistanceDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().PierceResistanceDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().SlashResistanceDef);

    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().FireResistanceDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().IceResistanceDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().WindResistanceDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().LightningResistanceDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().EarthResistanceDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().WaterResistanceDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().LightResistanceDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().DarkResistanceDef);

    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().AmnesiaResistanceDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().BindResistanceDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().BlindResistanceDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().GravityResistanceDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().ParalyzeResistanceDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().PetrifyResistanceDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().PoisonResistanceDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().SilenceResistanceDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().SleepResistanceDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().SlowResistanceDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().VirusResistanceDef);

    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().MoveSpeedDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().CurePotencyDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().CureReceivedPotencyDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().DamageResistDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().SpellInterruptionDef);

    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().GuardSkillDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().GuardSkillMaxDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().ParrySkillDef);
    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().ParrySkillMaxDef);

    RelevantAttributesToCapture.Add(XIEnemyAttributesStatics().ExpBountyDef);
}

void UXIEnemyStats::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
    AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
    FAggregatorEvaluateParameters EvaluationParameters;

	UXIAbilitySystemComponent* XIASC = Cast<UXIAbilitySystemComponent>(TargetAbilitySystemComponent);
    if(!XIASC)
    {
        UE_LOG(LogTemp, Error, TEXT("XIEnemyStats: The AbilitySystemComponent is not of type XIAbilitySystemComponent."));
        return;
    }

    UCurveTable* SkillRankCT = XIASC->GetAttributesCurveTable();

    if(!SkillRankCT)
    {
        UE_LOG(LogTemp, Error, TEXT("The AttributesCurveTable on the actors ASC is missing! %s"), *TargetActor->GetName());
        return;
    }

    float Level = 0.f;
    float Value = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(EnemyAttributesStatics().LevelDef, EvaluationParameters, Level);

    /*
    // Sets basic attributes
    */
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("HitPoints"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().HitPointsMaxProperty, EGameplayModOp::Override, Value));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().HitPointsProperty, EGameplayModOp::Override, Value));

    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("ManaPoints"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().ManaPointsMaxProperty, EGameplayModOp::Override, Value));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().ManaPointsProperty, EGameplayModOp::Override, Value));

    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("Strength"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().StrengthProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("Dexterity"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().DexterityProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("Agility"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().AgilityProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("Vitality"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().VitalityProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("Intelligence"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().IntelligenceProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("Mind"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().MindProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("Charisma"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().CharismaProperty, EGameplayModOp::Override, Value));

    /*
    // Sets physicial Attributes
    */
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("WeaponDamage"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().WeaponDamageProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("RangedWeaponDamage"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().RangedWeaponDamageProperty, EGameplayModOp::Override, Value));

    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("Attack"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().AttackProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("RangedAttack"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().RangedAttackProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("Defense"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().DefenseProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("Evasion"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().EvasionProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("Accuracy"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().AccuracyProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("RangedAccuracy"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().RangedAccuracyProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("CriticalHitRate"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().CriticalHitRateProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("CriticalHitBonus"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().CriticalHitBonusProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("RangedCriticalHitRate"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().RangedCriticalHitRateProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("RangedCriticalHitBonus"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().RangedCriticalHitBonusProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("AttackDelay"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().AttackDelayProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("AttackSpeed"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().AttackSpeedProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("RangedAttackDelay"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().RangedAttackDelayProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("RangedAttackSpeed"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().RangedAttackSpeedProperty, EGameplayModOp::Override, Value));

    /*
    // Set Magical attributes
    */
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("MagicAttack"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().MagicAttackProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("MagicAccuracy"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().MagicAccuracyProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("MagicEvasion"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().MagicEvasionProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("MagicCriticalHitRate"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().MagicCriticalHitRateProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("MagicCriticalHitBonus"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().MagicCriticalHitBonusProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("CastSpeed"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().CastSpeedProperty, EGameplayModOp::Override, Value));

    /*
    // Set Resistance Attributes
    */
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("BluntResistance"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().BluntResistanceProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("PierceResistance"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().PierceResistanceProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("SlashResistance"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().SlashResistanceProperty, EGameplayModOp::Override, Value));

    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("FireResistance"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().FireResistanceProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("IceResistance"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().IceResistanceProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("WindResistance"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().WindResistanceProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("LightningResistance"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().LightningResistanceProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("EarthResistance"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().EarthResistanceProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("WaterResistance"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().WaterResistanceProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("LightResistance"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().LightResistanceProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("DarkResistance"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().DarkResistanceProperty, EGameplayModOp::Override, Value));

    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("AmnesiaResistance"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().AmnesiaResistanceProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("BindResistance"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().BindResistanceProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("BlindResistance"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().BlindResistanceProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("GravityResistance"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().GravityResistanceProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("ParalyzeResistance"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().ParalyzeResistanceProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("PetrifyResistance"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().PetrifyResistanceProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("PoisonResistance"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().PoisonResistanceProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("SilenceResistance"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().SilenceResistanceProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("SleepResistance"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().SleepResistanceProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("SlowResistance"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().SlowResistanceProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("VirusResistance"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().VirusResistanceProperty, EGameplayModOp::Override, Value));

    /*
    // Misc Attributes
    */
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("MoveSpeed"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().MoveSpeedProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("CurePotency"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().CurePotencyProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("CureReceivedPotency"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().CureReceivedPotencyProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("DamageResist"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().DamageResistProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("SpellInterruption"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().SpellInterruptionProperty, EGameplayModOp::Override, Value));

    /*
    // Combat Skills
    */
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("GuardSkill"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().GuardSkillProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("GuardSkill"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().GuardSkillMaxProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("ParrySkill"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().ParrySkillProperty, EGameplayModOp::Override, Value));
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("ParrySkill"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().ParrySkillMaxProperty, EGameplayModOp::Override, Value));

    // Enemy Attributes
    Value = GetSkillRankValue(SkillRankCT, Level, FName::FName("ExpBounty"));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(EnemyAttributesStatics().ExpBountyProperty, EGameplayModOp::Override, Value));
}

float UXIEnemyStats::GetSkillRankValue(UCurveTable* CurveTable, float Level, FName RowName) const
{
    static const FString ContextString(TEXT("Getting Attribute Value"));
    float Value = 0.f;

    FCurveTableRowHandle SkillRankHandle;
    SkillRankHandle.CurveTable = CurveTable;
    SkillRankHandle.RowName = RowName;

    SkillRankHandle.Eval(Level, &Value,ContextString);

    return Value;
}