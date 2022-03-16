// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/XIAbilitySystemComponent.h"

void UXIAbilitySystemComponent::ReceiveCombatExp(float ExpGained)
{
    ReceivedCombatExp.Broadcast(ExpGained);
}

void UXIAbilitySystemComponent::CheckLevelUp()
{
    // HasMatchingGameplayTag();
}