// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GMMCs/XIDefenseAggr.h"
#include "Abilities/AttributeSetGlobal.h"
#include "Interfaces/XICharacterInterface.h"

UXIDefenseAggr::UXIDefenseAggr()
{
    VitalityDef.AttributeToCapture = UAttributeSetGlobal::GetVitalityAttribute();
    VitalityDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    VitalityDef.bSnapshot = false;

    RelevantAttributesToCapture.Add(VitalityDef);
}

float UXIDefenseAggr::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    FAggregatorEvaluateParameters EvaluationParameters;
    float Level = 0;
    
    IXICharacterInterface* XIInt = Cast<IXICharacterInterface>(Spec.GetEffectContext().GetInstigator());
    if(XIInt)
    {
        Level = XIInt->GetCharacterLevel();
    }

    float Vitality = 0.f;
    GetCapturedAttributeMagnitude(VitalityDef, Spec, EvaluationParameters, Vitality);
    
    return FMath::Floor(FMath::Max((Vitality / 2.f) + 8 + Level + FMath::Clamp(Level - 50.f, 0.f, 10.f), 0.f));
}