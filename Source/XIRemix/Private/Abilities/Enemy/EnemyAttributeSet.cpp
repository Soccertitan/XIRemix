// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Enemy/EnemyAttributeSet.h"
#include "Net/UnrealNetwork.h"

UEnemyAttributeSet::UEnemyAttributeSet() 
{

}


void UEnemyAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const 
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // Enemy Unique Attributes
    DOREPLIFETIME_CONDITION_NOTIFY(UEnemyAttributeSet, Level, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UEnemyAttributeSet, ExpBounty, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UEnemyAttributeSet, GilBounty, COND_None, REPNOTIFY_Always);
}

void UEnemyAttributeSet::OnRep_Level(const FGameplayAttributeData& OldLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UEnemyAttributeSet, Level, OldLevel);
}

void UEnemyAttributeSet::OnRep_ExpBounty(const FGameplayAttributeData& OldExpBounty) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UEnemyAttributeSet, ExpBounty, OldExpBounty);
}

void UEnemyAttributeSet::OnRep_GilBounty(const FGameplayAttributeData& OldGilBounty) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UEnemyAttributeSet, GilBounty, OldGilBounty);
}