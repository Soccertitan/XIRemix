// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/XIGameplayAbility.h"

UXIGameplayAbility::UXIGameplayAbility()
{
    // Default to instance per Actor
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    Range = 250.0f;
    Angle = 35.0f;
}