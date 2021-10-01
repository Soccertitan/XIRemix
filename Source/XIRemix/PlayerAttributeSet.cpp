// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerAttributeSet.h"
#include "Net/UnrealNetwork.h"

UPlayerAttributeSet::UPlayerAttributeSet() 
{
    
}

void UPlayerAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const 
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    //Basic Jobs  
    DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, WarriorCurrentLevel, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, WarriorMaxLevel, COND_None, REPNOTIFY_Always);

    DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, MonkCurrentLevel, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, MonkMaxLevel, COND_None, REPNOTIFY_Always);

    DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, ThiefCurrentLevel, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, ThiefMaxLevel, COND_None, REPNOTIFY_Always);

    DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, RedMageCurrentLevel, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, RedMageMaxLevel, COND_None, REPNOTIFY_Always);

    DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, WhiteMageCurrentLevel, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, WhiteMageMaxLevel, COND_None, REPNOTIFY_Always);

    DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, BlackMageCurrentLevel, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, BlackMageMaxLevel, COND_None, REPNOTIFY_Always);

    //Currencies
    DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Gil, COND_None, REPNOTIFY_Always);
}

#pragma region BasicJobs

void UPlayerAttributeSet::OnRep_WarriorCurrentLevel(const FGameplayAttributeData& OldWarriorCurrentLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, WarriorCurrentLevel, OldWarriorCurrentLevel);
}

void UPlayerAttributeSet::OnRep_WarriorMaxLevel(const FGameplayAttributeData& OldWarriorMaxLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, WarriorMaxLevel, OldWarriorMaxLevel);
}

void UPlayerAttributeSet::OnRep_MonkCurrentLevel(const FGameplayAttributeData& OldMonkCurrentLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, MonkCurrentLevel, OldMonkCurrentLevel);
}

void UPlayerAttributeSet::OnRep_MonkMaxLevel(const FGameplayAttributeData& OldMonkMaxLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, MonkMaxLevel, OldMonkMaxLevel);
}

void UPlayerAttributeSet::OnRep_ThiefCurrentLevel(const FGameplayAttributeData& OldThiefCurrentLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, ThiefCurrentLevel, OldThiefCurrentLevel);
}

void UPlayerAttributeSet::OnRep_ThiefMaxLevel(const FGameplayAttributeData& OldThiefMaxLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, ThiefMaxLevel, OldThiefMaxLevel);
}

void UPlayerAttributeSet::OnRep_RedMageCurrentLevel(const FGameplayAttributeData& OldRedMageCurrentLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, RedMageCurrentLevel, OldRedMageCurrentLevel);
}

void UPlayerAttributeSet::OnRep_RedMageMaxLevel(const FGameplayAttributeData& OldRedMageMaxLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, RedMageMaxLevel, OldRedMageMaxLevel);
}

void UPlayerAttributeSet::OnRep_WhiteMageCurrentLevel(const FGameplayAttributeData& OldWhiteMageCurrentLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, WhiteMageCurrentLevel, OldWhiteMageCurrentLevel);
}

void UPlayerAttributeSet::OnRep_WhiteMageMaxLevel(const FGameplayAttributeData& OldWhiteMageMaxLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, WhiteMageMaxLevel, OldWhiteMageMaxLevel);
}

void UPlayerAttributeSet::OnRep_BlackMageCurrentLevel(const FGameplayAttributeData& OldBlackMageCurrentLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, BlackMageCurrentLevel, OldBlackMageCurrentLevel);
}

void UPlayerAttributeSet::OnRep_BlackMageMaxLevel(const FGameplayAttributeData& OldBlackMageMaxLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, BlackMageMaxLevel, OldBlackMageMaxLevel);
}

#pragma endregion

#pragma region Currencies

void UPlayerAttributeSet::OnRep_Gil(const FGameplayAttributeData& OldGil) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Gil, OldGil);
}

#pragma endregion
