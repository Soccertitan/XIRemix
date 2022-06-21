// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GMMCs/XIAttackAggr.h"
#include "Abilities/AttributeSetGlobal.h"
#include "FunctionLibrary/XIGameplayFunctionLibrary.h"
#include "Components/XIEquipmentManagerComponent.h"

UXIAttackAggr::UXIAttackAggr()
{
    STRDef.AttributeToCapture = UAttributeSetGlobal::GetStrengthAttribute();
    STRDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    STRDef.bSnapshot = false;

    AxeDef.AttributeToCapture = UAttributeSetGlobal::GetAxeSkillAttribute();
    AxeDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    AxeDef.bSnapshot = false;
    AxeMaxDef.AttributeToCapture = UAttributeSetGlobal::GetAxeSkillMaxAttribute();
    AxeMaxDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    AxeMaxDef.bSnapshot = false;

    GreatAxeDef.AttributeToCapture = UAttributeSetGlobal::GetGreatAxeSkillAttribute();
    GreatAxeDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    GreatAxeDef.bSnapshot = false;
    GreatAxeMaxDef.AttributeToCapture = UAttributeSetGlobal::GetGreatAxeSkillMaxAttribute();
    GreatAxeMaxDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    GreatAxeMaxDef.bSnapshot = false;

    ClubDef.AttributeToCapture = UAttributeSetGlobal::GetClubSkillAttribute();
    ClubDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    ClubDef.bSnapshot = false;
    ClubMaxDef.AttributeToCapture = UAttributeSetGlobal::GetClubSkillMaxAttribute();
    ClubMaxDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    ClubMaxDef.bSnapshot = false;

    DaggerDef.AttributeToCapture = UAttributeSetGlobal::GetDaggerSkillAttribute();
    DaggerDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    DaggerDef.bSnapshot = false;
    DaggerMaxDef.AttributeToCapture = UAttributeSetGlobal::GetDaggerSkillMaxAttribute();
    DaggerMaxDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    DaggerMaxDef.bSnapshot = false;

    HandToHandDef.AttributeToCapture = UAttributeSetGlobal::GetHandToHandSkillAttribute();
    HandToHandDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    HandToHandDef.bSnapshot = false;
    HandToHandMaxDef.AttributeToCapture = UAttributeSetGlobal::GetHandToHandSkillMaxAttribute();
    HandToHandMaxDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    HandToHandMaxDef.bSnapshot = false;

    KatanaDef.AttributeToCapture = UAttributeSetGlobal::GetKatanaSkillAttribute();
    KatanaDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    KatanaDef.bSnapshot = false;
    KatanaMaxDef.AttributeToCapture = UAttributeSetGlobal::GetKatanaSkillMaxAttribute();
    KatanaMaxDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    KatanaMaxDef.bSnapshot = false;

    GreatKatanaDef.AttributeToCapture = UAttributeSetGlobal::GetGreatKatanaSkillAttribute();
    GreatKatanaDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    GreatKatanaDef.bSnapshot = false;
    GreatKatanaMaxDef.AttributeToCapture = UAttributeSetGlobal::GetGreatKatanaSkillMaxAttribute();
    GreatKatanaMaxDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    GreatKatanaMaxDef.bSnapshot = false;

    PolearmDef.AttributeToCapture = UAttributeSetGlobal::GetPolearmSkillAttribute();
    PolearmDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    PolearmDef.bSnapshot = false;
    PolearmMaxDef.AttributeToCapture = UAttributeSetGlobal::GetPolearmSkillMaxAttribute();
    PolearmMaxDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    PolearmMaxDef.bSnapshot = false;

    ScytheDef.AttributeToCapture = UAttributeSetGlobal::GetScytheSkillAttribute();
    ScytheDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    ScytheDef.bSnapshot = false;
    ScytheMaxDef.AttributeToCapture = UAttributeSetGlobal::GetScytheSkillMaxAttribute();
    ScytheMaxDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    ScytheMaxDef.bSnapshot = false;

    StaffDef.AttributeToCapture = UAttributeSetGlobal::GetStaffSkillAttribute();
    StaffDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    StaffDef.bSnapshot = false;
    StaffMaxDef.AttributeToCapture = UAttributeSetGlobal::GetStaffSkillMaxAttribute();
    StaffMaxDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    StaffMaxDef.bSnapshot = false;

    SwordDef.AttributeToCapture = UAttributeSetGlobal::GetSwordSkillAttribute();
    SwordDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    SwordDef.bSnapshot = false;
    SwordMaxDef.AttributeToCapture = UAttributeSetGlobal::GetSwordSkillMaxAttribute();
    SwordMaxDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    SwordMaxDef.bSnapshot = false;

    GreatSwordDef.AttributeToCapture = UAttributeSetGlobal::GetGreatSwordSkillAttribute();
    GreatSwordDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    GreatSwordDef.bSnapshot = false;
    GreatSwordMaxDef.AttributeToCapture = UAttributeSetGlobal::GetGreatSwordSkillMaxAttribute();
    GreatSwordMaxDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    GreatSwordMaxDef.bSnapshot = false;

    RelevantAttributesToCapture.Add(STRDef);

	RelevantAttributesToCapture.Add(AxeDef);
	RelevantAttributesToCapture.Add(AxeMaxDef);

	RelevantAttributesToCapture.Add(GreatAxeDef);
	RelevantAttributesToCapture.Add(GreatAxeMaxDef);

	RelevantAttributesToCapture.Add(ClubDef);
	RelevantAttributesToCapture.Add(ClubMaxDef);

	RelevantAttributesToCapture.Add(DaggerDef);
	RelevantAttributesToCapture.Add(DaggerMaxDef);

	RelevantAttributesToCapture.Add(HandToHandDef);
	RelevantAttributesToCapture.Add(HandToHandMaxDef);

	RelevantAttributesToCapture.Add(KatanaDef);
	RelevantAttributesToCapture.Add(KatanaMaxDef);

	RelevantAttributesToCapture.Add(GreatKatanaDef);
	RelevantAttributesToCapture.Add(GreatKatanaMaxDef);

	RelevantAttributesToCapture.Add(PolearmDef);
	RelevantAttributesToCapture.Add(PolearmMaxDef);

	RelevantAttributesToCapture.Add(ScytheDef);
	RelevantAttributesToCapture.Add(ScytheMaxDef);

	RelevantAttributesToCapture.Add(StaffDef);
	RelevantAttributesToCapture.Add(StaffMaxDef);

	RelevantAttributesToCapture.Add(SwordDef);
	RelevantAttributesToCapture.Add(SwordMaxDef);

	RelevantAttributesToCapture.Add(GreatSwordDef);
	RelevantAttributesToCapture.Add(GreatSwordMaxDef);
}

float UXIAttackAggr::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    FAggregatorEvaluateParameters EvaluationParameters;

    float CurrentSkillLevel = 0.f;
    float MaxSkillLevel = 0.f;

    float Strength = 0.f;
    float cStrength = 0.f;
    GetCapturedAttributeMagnitude(STRDef, Spec, EvaluationParameters, Strength);
    cStrength = FMath::Floor(Strength * .75f);

    UXIEquipmentManagerComponent* EMC = UXIGameplayFunctionLibrary::GetXIEquipmentManagerComponent(Spec.GetEffectContext().GetInstigator());

    if(EMC)
    {
        UXIItemEquipment* Weapon = EMC->FindEquippedItemBySlot(EEquipSlot::MainHand);
        if(Weapon && Weapon->ItemType == EItemType::WeaponMelee)
        {
            FGameplayTag WeaponType = Weapon->WeaponType;
            if (WeaponType == FGameplayTag::RequestGameplayTag("Weapon.Melee.Axe"))
            {
                GetCapturedAttributeMagnitude(AxeDef, Spec, EvaluationParameters, CurrentSkillLevel);
                GetCapturedAttributeMagnitude(AxeMaxDef, Spec, EvaluationParameters, MaxSkillLevel);
            }
            else if (WeaponType == FGameplayTag::RequestGameplayTag("Weapon.Melee.Club"))
            {
                GetCapturedAttributeMagnitude(ClubDef, Spec, EvaluationParameters, CurrentSkillLevel);
                GetCapturedAttributeMagnitude(ClubMaxDef, Spec, EvaluationParameters, MaxSkillLevel);
            }
            else if (WeaponType == FGameplayTag::RequestGameplayTag("Weapon.Melee.Dagger"))
            {
                GetCapturedAttributeMagnitude(DaggerDef, Spec, EvaluationParameters, CurrentSkillLevel);
                GetCapturedAttributeMagnitude(DaggerMaxDef, Spec, EvaluationParameters, MaxSkillLevel);
            }
            else if (WeaponType == FGameplayTag::RequestGameplayTag("Weapon.Melee.GreatAxe"))
            {
                GetCapturedAttributeMagnitude(GreatAxeDef, Spec, EvaluationParameters, CurrentSkillLevel);
                GetCapturedAttributeMagnitude(GreatAxeMaxDef, Spec, EvaluationParameters, MaxSkillLevel);
            }
            else if (WeaponType == FGameplayTag::RequestGameplayTag("Weapon.Melee.GreatKatana"))
            {
                GetCapturedAttributeMagnitude(GreatKatanaDef, Spec, EvaluationParameters, CurrentSkillLevel);
                GetCapturedAttributeMagnitude(GreatKatanaMaxDef, Spec, EvaluationParameters, MaxSkillLevel);
                
            }
            else if (WeaponType == FGameplayTag::RequestGameplayTag("Weapon.Melee.GreatSword"))
            {
                GetCapturedAttributeMagnitude(GreatSwordDef, Spec, EvaluationParameters, CurrentSkillLevel);
                GetCapturedAttributeMagnitude(GreatSwordMaxDef, Spec, EvaluationParameters, MaxSkillLevel);
            }
            else if (WeaponType == FGameplayTag::RequestGameplayTag("Weapon.Melee.HandToHand"))
            {
                GetCapturedAttributeMagnitude(HandToHandDef, Spec, EvaluationParameters, CurrentSkillLevel);
                GetCapturedAttributeMagnitude(HandToHandMaxDef, Spec, EvaluationParameters, MaxSkillLevel);
                cStrength = FMath::Floor(Strength * .625f);
            }
            else if (WeaponType == FGameplayTag::RequestGameplayTag("Weapon.Melee.Katana"))
            {
                GetCapturedAttributeMagnitude(KatanaDef, Spec, EvaluationParameters, CurrentSkillLevel);
                GetCapturedAttributeMagnitude(KatanaMaxDef, Spec, EvaluationParameters, MaxSkillLevel);
            }
            else if (WeaponType == FGameplayTag::RequestGameplayTag("Weapon.Melee.Polearm"))
            {
                GetCapturedAttributeMagnitude(PolearmDef, Spec, EvaluationParameters, CurrentSkillLevel);
                GetCapturedAttributeMagnitude(PolearmMaxDef, Spec, EvaluationParameters, MaxSkillLevel);
            }
            else if (WeaponType == FGameplayTag::RequestGameplayTag("Weapon.Melee.Scythe"))
            {
                GetCapturedAttributeMagnitude(ScytheDef, Spec, EvaluationParameters, CurrentSkillLevel);
                GetCapturedAttributeMagnitude(ScytheMaxDef, Spec, EvaluationParameters, MaxSkillLevel);
            }
            else if (WeaponType == FGameplayTag::RequestGameplayTag("Weapon.Melee.Staff"))
            {
                GetCapturedAttributeMagnitude(StaffDef, Spec, EvaluationParameters, CurrentSkillLevel);
                GetCapturedAttributeMagnitude(StaffMaxDef, Spec, EvaluationParameters, MaxSkillLevel);
            }
            else if (WeaponType == FGameplayTag::RequestGameplayTag("Weapon.Melee.Sword"))
            {
                GetCapturedAttributeMagnitude(SwordDef, Spec, EvaluationParameters, CurrentSkillLevel);
                GetCapturedAttributeMagnitude(SwordMaxDef, Spec, EvaluationParameters, MaxSkillLevel);
            }
        }
        else
        {
            GetCapturedAttributeMagnitude(HandToHandDef, Spec, EvaluationParameters, CurrentSkillLevel);
            GetCapturedAttributeMagnitude(HandToHandMaxDef, Spec, EvaluationParameters, MaxSkillLevel);
            cStrength = FMath::Floor(Strength * .625f);
        }
    }
    else
    {
        GetCapturedAttributeMagnitude(HandToHandDef, Spec, EvaluationParameters, CurrentSkillLevel);
        GetCapturedAttributeMagnitude(HandToHandMaxDef, Spec, EvaluationParameters, MaxSkillLevel);
        cStrength = FMath::Floor(Strength * .625f);
    }

    return 8.f + FMath::Min(CurrentSkillLevel, MaxSkillLevel) + cStrength;
}