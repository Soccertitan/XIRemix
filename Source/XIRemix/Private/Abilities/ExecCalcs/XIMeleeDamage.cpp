// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/ExecCalcs/XIMeleeDamage.h"
#include "Abilities/XIAbilitySystemComponent.h"
#include "Abilities/AttributeSetGlobal.h"
#include "Abilities/Hero/AttributeSetHero.h"
#include "Abilities/Enemy/AttributeSetEnemy.h"
#include "Abilities/XIAbilityTypes.h"
#include "Interfaces/XIThreatTableInterface.h"
#include "AIController.h"
#include "Components/XIThreatTableComponent.h"
#include "FunctionLibrary/XIGameplayFunctionLibrary.h"
#include "FunctionLibrary/XIMathFunctionLibrary.h"
#include "Components/XIEquipmentManagerComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

struct XIMeleeStatics
{
    DECLARE_ATTRIBUTE_CAPTUREDEF(DamageHP);
    DECLARE_ATTRIBUTE_CAPTUREDEF(RecoverTP);

    DECLARE_ATTRIBUTE_CAPTUREDEF(WeaponDamage);

    DECLARE_ATTRIBUTE_CAPTUREDEF(HitPointsMax);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Attack);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Strength)
    DECLARE_ATTRIBUTE_CAPTUREDEF(Accuracy);
    DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitRate);
    DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitBonus);
    DECLARE_ATTRIBUTE_CAPTUREDEF(EnmityRate);
    DECLARE_ATTRIBUTE_CAPTUREDEF(AttackDelay);

    DECLARE_ATTRIBUTE_CAPTUREDEF(Defense);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Vitality);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Evasion);

    XIMeleeStatics()
    {
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, DamageHP, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, RecoverTP, Target, false);

        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetEnemy, WeaponDamage, Source, false);

        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, HitPointsMax, Source, true);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Attack, Source, true);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Strength, Source, true);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Accuracy, Source, true);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, CriticalHitRate, Source, true);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, CriticalHitBonus, Source, true);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetHero, EnmityRate, Source, true);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, AttackDelay, Source, true);

        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Defense, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Vitality, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetGlobal, Evasion, Target, false);
    }
};

static const XIMeleeStatics& MeleeStatics()
{
    static XIMeleeStatics MStatics;
    return MStatics;
}

UXIMeleeDamage::UXIMeleeDamage()
{
    RelevantAttributesToCapture.Add(MeleeStatics().DamageHPDef);
    RelevantAttributesToCapture.Add(MeleeStatics().RecoverTPDef);

    RelevantAttributesToCapture.Add(MeleeStatics().WeaponDamageDef);

    RelevantAttributesToCapture.Add(MeleeStatics().HitPointsMaxDef);
    RelevantAttributesToCapture.Add(MeleeStatics().AttackDef);
    RelevantAttributesToCapture.Add(MeleeStatics().StrengthDef);
    RelevantAttributesToCapture.Add(MeleeStatics().AccuracyDef);
    RelevantAttributesToCapture.Add(MeleeStatics().CriticalHitRateDef);
    RelevantAttributesToCapture.Add(MeleeStatics().CriticalHitBonusDef);
    RelevantAttributesToCapture.Add(MeleeStatics().EnmityRateDef);
    RelevantAttributesToCapture.Add(MeleeStatics().AttackDelayDef);

    RelevantAttributesToCapture.Add(MeleeStatics().DefenseDef);
    RelevantAttributesToCapture.Add(MeleeStatics().VitalityDef);
    RelevantAttributesToCapture.Add(MeleeStatics().EvasionDef);
}

void UXIMeleeDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    OutExecutionOutput.MarkGameplayCuesHandledManually();
    FGameplayCueParameters GCParam;

    UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->GetAvatarActor() : nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

	FGameplayEffectSpec* Spec = ExecutionParams.GetOwningSpecForPreExecuteMod();
    FXIGameplayEffectContext* XIContext = static_cast<FXIGameplayEffectContext*>(Spec->GetContext().Get());

	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* SourceTags = Spec->CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec->CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

    APawn* AsPawn = Cast<APawn>(TargetActor);
    const IXIThreatTableInterface* XIThreatIntTarget = Cast<IXIThreatTableInterface>(Cast<AAIController>(AsPawn->GetController()));
    AsPawn = Cast<APawn>(SourceActor);
    const IXIThreatTableInterface* XIThreatIntSource = Cast<IXIThreatTableInterface>(Cast<AAIController>(AsPawn->GetController()));

    float Damage = 0.f;
    float Attack = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MeleeStatics().AttackDef, EvaluationParameters, Attack);
    float Strength = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MeleeStatics().StrengthDef, EvaluationParameters, Strength);
    float Accuracy = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MeleeStatics().AccuracyDef, EvaluationParameters, Accuracy);
    float CritChance = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MeleeStatics().CriticalHitRateDef, EvaluationParameters, CritChance);
    float CritBonus = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MeleeStatics().CriticalHitBonusDef, EvaluationParameters, CritBonus);
    float EnmityRate = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MeleeStatics().EnmityRateDef, EvaluationParameters, EnmityRate);
    float Defense = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MeleeStatics().DefenseDef, EvaluationParameters, Defense);
    float Vitality = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MeleeStatics().VitalityDef, EvaluationParameters, Vitality);
    float Evasion = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MeleeStatics().EvasionDef, EvaluationParameters, Evasion);
    FGameplayTag WeaponType = FGameplayTag::RequestGameplayTag("Weapon.Melee.HandToHand");
    float LevelDif = UXIGameplayFunctionLibrary::GetCharacterLevel(TargetActor) - UXIGameplayFunctionLibrary::GetCharacterLevel(SourceActor);

    float HitRate = UXIMathFunctionLibrary::HitRate(Accuracy, Evasion, LevelDif);

    if (FMath::RandRange(0.f, 1.f) <= HitRate)
    {
        //True we hit the target!
        float WeaponDamage = 0.f;
        ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MeleeStatics().WeaponDamageDef, EvaluationParameters, WeaponDamage);
        if(WeaponDamage == 0.f)
        {
            WeaponDamage = GetWeaponBaseDamage(SourceActor, WeaponType);
        }

        if(SourceTags->HasTag(FGameplayTag::RequestGameplayTag("Weapon.Melee.HandToHand")))
        {
            Damage = (WeaponDamage + UXIMathFunctionLibrary::fSTRMelee(Strength, Vitality, WeaponDamage, true));
        }
        else
        {
            Damage = (WeaponDamage + UXIMathFunctionLibrary::fSTRMelee(Strength, Vitality, WeaponDamage, false));
        }

        bool bIsCriticalHit = false;
        if(SourceTags->HasTag(FGameplayTag::RequestGameplayTag("State.Const.Monster")))
        {
            Damage = FMath::Max(FMath::Floor(Damage * UXIMathFunctionLibrary::pDIF(Attack, Defense, LevelDif, CritChance, CritBonus, WeaponType, true, bIsCriticalHit)), 0.f);
        }
        else
        {
            Damage = FMath::Max(FMath::Floor(Damage * UXIMathFunctionLibrary::pDIF(Attack, Defense, LevelDif, CritChance, CritBonus, WeaponType, false, bIsCriticalHit)), 0.f);
        }

        if(XIThreatIntTarget)
        {
            // Add enmity on the target actor caused by the source actor.
            UXIThreatTableComponent* ThreatTableComponent = XIThreatIntTarget->GetXIThreatTableComponent();
            ThreatTableComponent->ApplyDamageEnmity(SourceActor, Damage, EnmityRate);
        }

        if(XIThreatIntSource)
        {
            //Remove enmity from the source actor that dealt damage tot he target actor.
            float HitPointsMax = 1.f;
            ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MeleeStatics().HitPointsMaxDef, EvaluationParameters, HitPointsMax);
            UXIThreatTableComponent* ThreatTableComponent = XIThreatIntSource->GetXIThreatTableComponent();
            ThreatTableComponent->ApplyDamageTakenEnmity(TargetActor, Damage, HitPointsMax);
        }

        OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(MeleeStatics().DamageHPProperty, EGameplayModOp::Additive, Damage));
        
        XIContext->SetIsCriticalHit(bIsCriticalHit);
        GCParam.RawMagnitude = Damage;
        
        
        if (Damage > 0)
        {
            float Delay = 480.f;
            ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MeleeStatics().AttackDelayDef, EvaluationParameters, Delay);
            Delay = UXIMathFunctionLibrary::TPGained(Delay);
            FGameplayEventData Payload;
            Payload.EventMagnitude = Delay;
            UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(SourceActor, FGameplayTag::RequestGameplayTag("Event.Gameplay.RecoverTP"), Payload);
            
            //TP gained by the attacked target.
            OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(MeleeStatics().RecoverTPProperty, EGameplayModOp::Additive, FMath::Floor(Delay * 0.33f)));
        }
    }
    else
    {
        // WE missed :(
        XIContext->SetIsEvaded(true);
    }
    
    GCParam.EffectContext = ExecutionParams.GetOwningSpec().GetEffectContext();
    TargetAbilitySystemComponent->ExecuteGameplayCue(FGameplayTag::RequestGameplayTag("GameplayCue.Attack.Melee"), GCParam);
}

float UXIMeleeDamage::GetWeaponBaseDamage(AActor* Actor, FGameplayTag OutWeaponTag) const
{
    UXIEquipmentManagerComponent* EMC = UXIGameplayFunctionLibrary::GetXIEquipmentManagerComponent(Actor);
    if(EMC)
    {
        UXIItemEquipment* Weapon = EMC->FindEquippedItemBySlot(EEquipSlot::MainHand);
        if(Weapon)
        {
            OutWeaponTag = Weapon->WeaponType;
            return Weapon->Damage;
        }
    }
    return 0.f;
}