// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Hero/HeroAttributeSet.h"
#include "Net/UnrealNetwork.h"


UHeroAttributeSet::UHeroAttributeSet() 
{

}


void UHeroAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const 
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    //Basic Jobs
    DOREPLIFETIME_CONDITION_NOTIFY(UHeroAttributeSet, WarriorLevel, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UHeroAttributeSet, WarriorMaxLevel, COND_None, REPNOTIFY_Always);

    DOREPLIFETIME_CONDITION_NOTIFY(UHeroAttributeSet, MonkLevel, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UHeroAttributeSet, MonkMaxLevel, COND_None, REPNOTIFY_Always);

    DOREPLIFETIME_CONDITION_NOTIFY(UHeroAttributeSet, ThiefLevel, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UHeroAttributeSet, ThiefMaxLevel, COND_None, REPNOTIFY_Always);

    DOREPLIFETIME_CONDITION_NOTIFY(UHeroAttributeSet, RedMageLevel, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UHeroAttributeSet, RedMageMaxLevel, COND_None, REPNOTIFY_Always);

    DOREPLIFETIME_CONDITION_NOTIFY(UHeroAttributeSet, WhiteMageLevel, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UHeroAttributeSet, WhiteMageMaxLevel, COND_None, REPNOTIFY_Always);

    DOREPLIFETIME_CONDITION_NOTIFY(UHeroAttributeSet, BlackMageLevel, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UHeroAttributeSet, BlackMageMaxLevel, COND_None, REPNOTIFY_Always);

    //Currencies
    DOREPLIFETIME_CONDITION_NOTIFY(UHeroAttributeSet, Gil, COND_None, REPNOTIFY_Always);
}

#pragma region BasicJobs

void UHeroAttributeSet::OnRep_WarriorLevel(const FGameplayAttributeData& OldWarriorLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UHeroAttributeSet, WarriorLevel, OldWarriorLevel);
}

void UHeroAttributeSet::OnRep_WarriorMaxLevel(const FGameplayAttributeData& OldWarriorMaxLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UHeroAttributeSet, WarriorMaxLevel, OldWarriorMaxLevel);
}

void UHeroAttributeSet::OnRep_MonkLevel(const FGameplayAttributeData& OldMonkLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UHeroAttributeSet, MonkLevel, OldMonkLevel);
}

void UHeroAttributeSet::OnRep_MonkMaxLevel(const FGameplayAttributeData& OldMonkMaxLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UHeroAttributeSet, MonkMaxLevel, OldMonkMaxLevel);
}

void UHeroAttributeSet::OnRep_ThiefLevel(const FGameplayAttributeData& OldThiefLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UHeroAttributeSet, ThiefLevel, OldThiefLevel);
}

void UHeroAttributeSet::OnRep_ThiefMaxLevel(const FGameplayAttributeData& OldThiefMaxLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UHeroAttributeSet, ThiefMaxLevel, OldThiefMaxLevel);
}

void UHeroAttributeSet::OnRep_RedMageLevel(const FGameplayAttributeData& OldRedMageLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UHeroAttributeSet, RedMageLevel, OldRedMageLevel);
}

void UHeroAttributeSet::OnRep_RedMageMaxLevel(const FGameplayAttributeData& OldRedMageMaxLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UHeroAttributeSet, RedMageMaxLevel, OldRedMageMaxLevel);
}

void UHeroAttributeSet::OnRep_WhiteMageLevel(const FGameplayAttributeData& OldWhiteMageLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UHeroAttributeSet, WhiteMageLevel, OldWhiteMageLevel);
}

void UHeroAttributeSet::OnRep_WhiteMageMaxLevel(const FGameplayAttributeData& OldWhiteMageMaxLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UHeroAttributeSet, WhiteMageMaxLevel, OldWhiteMageMaxLevel);
}

void UHeroAttributeSet::OnRep_BlackMageLevel(const FGameplayAttributeData& OldBlackMageLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UHeroAttributeSet, BlackMageLevel, OldBlackMageLevel);
}

void UHeroAttributeSet::OnRep_BlackMageMaxLevel(const FGameplayAttributeData& OldBlackMageMaxLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UHeroAttributeSet, BlackMageMaxLevel, OldBlackMageMaxLevel);
}

#pragma endregion

#pragma region Currencies

void UHeroAttributeSet::OnRep_Gil(const FGameplayAttributeData& OldGil) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UHeroAttributeSet, Gil, OldGil);
}

#pragma endregion