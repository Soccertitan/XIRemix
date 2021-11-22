// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Enemy/AttributeSetEnemy.h"
#include "Net/UnrealNetwork.h"

UAttributeSetEnemy::UAttributeSetEnemy() 
{

}


void UAttributeSetEnemy::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const 
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // Enemy Unique Attributes
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetEnemy, Level, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetEnemy, ExpBounty, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetEnemy, GilBounty, COND_None, REPNOTIFY_Always);
}

void UAttributeSetEnemy::OnRep_Level(const FGameplayAttributeData& OldLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetEnemy, Level, OldLevel);
}

void UAttributeSetEnemy::OnRep_ExpBounty(const FGameplayAttributeData& OldExpBounty) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetEnemy, ExpBounty, OldExpBounty);
}

void UAttributeSetEnemy::OnRep_GilBounty(const FGameplayAttributeData& OldGilBounty) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetEnemy, GilBounty, OldGilBounty);
}