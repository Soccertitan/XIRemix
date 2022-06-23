// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Hero/AttributeSetHero.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"
#include "Net/UnrealNetwork.h"
#include "Abilities/XIAbilitySystemComponent.h"


UAttributeSetHero::UAttributeSetHero()
    : EnmityRate(1.0f)
{
}

void UAttributeSetHero::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
    UAbilitySystemComponent* Target = Data.Target.AbilityActorInfo->AbilitySystemComponent.Get();
    UXIAbilitySystemComponent* TargetASC = Cast<UXIAbilitySystemComponent>(Target);

	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer& TargetTags = *Data.EffectSpec.CapturedTargetTags.GetAggregatedTags();

    if (Data.EvaluatedData.Attribute == GetEnmityRateAttribute())
	{
		// Caps Enmity to between generating half the amount to 3x.
		SetEnmityRate(FMath::Clamp(GetEnmityRate(), 0.5f, 3.0f));
	}
}

void UAttributeSetHero::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const 
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    //Basic Jobs
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetHero, WarriorLevel, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetHero, WarriorMaxLevel, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetHero, WarriorEXP, COND_None, REPNOTIFY_Always);

    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetHero, MonkLevel, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetHero, MonkMaxLevel, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetHero, MonkEXP, COND_None, REPNOTIFY_Always);

    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetHero, ThiefLevel, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetHero, ThiefMaxLevel, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetHero, ThiefEXP, COND_None, REPNOTIFY_Always);

    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetHero, RedMageLevel, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetHero, RedMageMaxLevel, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetHero, RedMageEXP, COND_None, REPNOTIFY_Always);

    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetHero, WhiteMageLevel, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetHero, WhiteMageMaxLevel, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetHero, WhiteMageEXP, COND_None, REPNOTIFY_Always);

    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetHero, BlackMageLevel, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetHero, BlackMageMaxLevel, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetHero, BlackMageEXP, COND_None, REPNOTIFY_Always);

    //OtherAttributes
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetHero, EnmityRate, COND_None, REPNOTIFY_Always);
}

#pragma region BasicJobs

void UAttributeSetHero::OnRep_WarriorLevel(const FGameplayAttributeData& OldWarriorLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetHero, WarriorLevel, OldWarriorLevel);
}
void UAttributeSetHero::OnRep_WarriorMaxLevel(const FGameplayAttributeData& OldWarriorMaxLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetHero, WarriorMaxLevel, OldWarriorMaxLevel);
}
void UAttributeSetHero::OnRep_WarriorEXP(const FGameplayAttributeData& OldWarriorEXP) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetHero, WarriorEXP, OldWarriorEXP);
}


void UAttributeSetHero::OnRep_MonkLevel(const FGameplayAttributeData& OldMonkLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetHero, MonkLevel, OldMonkLevel);
}
void UAttributeSetHero::OnRep_MonkMaxLevel(const FGameplayAttributeData& OldMonkMaxLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetHero, MonkMaxLevel, OldMonkMaxLevel);
}
void UAttributeSetHero::OnRep_MonkEXP(const FGameplayAttributeData& OldMonkEXP) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetHero, MonkEXP, OldMonkEXP);
}


void UAttributeSetHero::OnRep_ThiefLevel(const FGameplayAttributeData& OldThiefLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetHero, ThiefLevel, OldThiefLevel);
}
void UAttributeSetHero::OnRep_ThiefMaxLevel(const FGameplayAttributeData& OldThiefMaxLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetHero, ThiefMaxLevel, OldThiefMaxLevel);
}
void UAttributeSetHero::OnRep_ThiefEXP(const FGameplayAttributeData& OldThiefEXP) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetHero, ThiefEXP, OldThiefEXP);
}


void UAttributeSetHero::OnRep_RedMageLevel(const FGameplayAttributeData& OldRedMageLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetHero, RedMageLevel, OldRedMageLevel);
}
void UAttributeSetHero::OnRep_RedMageMaxLevel(const FGameplayAttributeData& OldRedMageMaxLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetHero, RedMageMaxLevel, OldRedMageMaxLevel);
}
void UAttributeSetHero::OnRep_RedMageEXP(const FGameplayAttributeData& OldRedMageEXP) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetHero, RedMageEXP, OldRedMageEXP);
}


void UAttributeSetHero::OnRep_WhiteMageLevel(const FGameplayAttributeData& OldWhiteMageLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetHero, WhiteMageLevel, OldWhiteMageLevel);
}
void UAttributeSetHero::OnRep_WhiteMageMaxLevel(const FGameplayAttributeData& OldWhiteMageMaxLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetHero, WhiteMageMaxLevel, OldWhiteMageMaxLevel);
}
void UAttributeSetHero::OnRep_WhiteMageEXP(const FGameplayAttributeData& OldWhiteMageEXP) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetHero, WhiteMageEXP, OldWhiteMageEXP);
}


void UAttributeSetHero::OnRep_BlackMageLevel(const FGameplayAttributeData& OldBlackMageLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetHero, BlackMageLevel, OldBlackMageLevel);
}
void UAttributeSetHero::OnRep_BlackMageMaxLevel(const FGameplayAttributeData& OldBlackMageMaxLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetHero, BlackMageMaxLevel, OldBlackMageMaxLevel);
}
void UAttributeSetHero::OnRep_BlackMageEXP(const FGameplayAttributeData& OldBlackMageEXP) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetHero, BlackMageEXP, OldBlackMageEXP);
}

#pragma endregion BasicJobs

#pragma region OtherAttributes

void UAttributeSetHero::OnRep_EnmityRate(const FGameplayAttributeData& OldEnmityRate) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetHero, EnmityRate, OldEnmityRate);
}

#pragma endregion OtherAttributes
