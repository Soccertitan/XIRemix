// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GameplayAbilityGlobal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"

UGameplayAbilityGlobal::UGameplayAbilityGlobal()
{
    // Default to instance per Actor
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}