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
}

void UAttributeSetEnemy::OnRep_Level(const FGameplayAttributeData& OldLevel) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetEnemy, Level, OldLevel);
}