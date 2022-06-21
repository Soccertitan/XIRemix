// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GMMCs/XIAccuracySubHandAggr.h"
#include "Abilities/AttributeSetGlobal.h"
#include "FunctionLibrary/XIGameplayFunctionLibrary.h"
#include "Components/XIEquipmentManagerComponent.h"

UXIAccuracySubHandAggr::UXIAccuracySubHandAggr()
{
    DexDef.AttributeToCapture = UAttributeSetGlobal::GetDexterityAttribute();
    DexDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    DexDef.bSnapshot = false;

    AxeDef.AttributeToCapture = UAttributeSetGlobal::GetAxeSkillAttribute();
    AxeDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    AxeDef.bSnapshot = false;
    AxeMaxDef.AttributeToCapture = UAttributeSetGlobal::GetAxeSkillMaxAttribute();
    AxeMaxDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    AxeMaxDef.bSnapshot = false;

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

    KatanaDef.AttributeToCapture = UAttributeSetGlobal::GetKatanaSkillAttribute();
    KatanaDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    KatanaDef.bSnapshot = false;
    KatanaMaxDef.AttributeToCapture = UAttributeSetGlobal::GetKatanaSkillMaxAttribute();
    KatanaMaxDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    KatanaMaxDef.bSnapshot = false;

    SwordDef.AttributeToCapture = UAttributeSetGlobal::GetSwordSkillAttribute();
    SwordDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    SwordDef.bSnapshot = false;
    SwordMaxDef.AttributeToCapture = UAttributeSetGlobal::GetSwordSkillMaxAttribute();
    SwordMaxDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    SwordMaxDef.bSnapshot = false;

    RelevantAttributesToCapture.Add(DexDef);

	RelevantAttributesToCapture.Add(AxeDef);
	RelevantAttributesToCapture.Add(AxeMaxDef);

	RelevantAttributesToCapture.Add(ClubDef);
	RelevantAttributesToCapture.Add(ClubMaxDef);

	RelevantAttributesToCapture.Add(DaggerDef);
	RelevantAttributesToCapture.Add(DaggerMaxDef);

	RelevantAttributesToCapture.Add(KatanaDef);
	RelevantAttributesToCapture.Add(KatanaMaxDef);

	RelevantAttributesToCapture.Add(SwordDef);
	RelevantAttributesToCapture.Add(SwordMaxDef);
}

float UXIAccuracySubHandAggr::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    FAggregatorEvaluateParameters EvaluationParameters;

    float CurrentSkillLevel = 0.f;
    float MaxSkillLevel = 0.f;
    float Dexterity = 0.f;
    float cDexterity = 0.f;

    GetCapturedAttributeMagnitude(DexDef, Spec, EvaluationParameters, Dexterity);
    cDexterity = FMath::Floor(Dexterity * .75f);

    UXIEquipmentManagerComponent* EMC = UXIGameplayFunctionLibrary::GetXIEquipmentManagerComponent(Spec.GetEffectContext().GetInstigator());

    if(EMC)
    {
        UXIItemEquipment* Weapon = EMC->FindEquippedItemBySlot(EEquipSlot::SubHand);
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
            else if (WeaponType == FGameplayTag::RequestGameplayTag("Weapon.Melee.Katana"))
            {
                GetCapturedAttributeMagnitude(KatanaDef, Spec, EvaluationParameters, CurrentSkillLevel);
                GetCapturedAttributeMagnitude(KatanaMaxDef, Spec, EvaluationParameters, MaxSkillLevel);
            }
            else if (WeaponType == FGameplayTag::RequestGameplayTag("Weapon.Melee.Sword"))
            {
                GetCapturedAttributeMagnitude(SwordDef, Spec, EvaluationParameters, CurrentSkillLevel);
                GetCapturedAttributeMagnitude(SwordMaxDef, Spec, EvaluationParameters, MaxSkillLevel);
            }
        }
    }
    
    float cSkillLevel = FMath::Min(CurrentSkillLevel, MaxSkillLevel);

    float AccFromSkill = FMath::Min(cSkillLevel, 200.f) + FMath::Floor(FMath::Max(cSkillLevel - 200.f, 0) * 0.9f) + FMath::Floor(FMath::Max(cSkillLevel - 400.f, 0) * 0.8f) + FMath::Floor(FMath::Max(cSkillLevel - 600.f, 0) * 0.9f);

    return cDexterity + AccFromSkill;
}
