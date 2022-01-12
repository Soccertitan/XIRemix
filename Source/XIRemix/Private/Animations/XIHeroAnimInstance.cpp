// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/XIHeroAnimInstance.h"

float UXIHeroAnimInstance::GetSpeed_Implementation()
{
    return Speed;
}

float UXIHeroAnimInstance::GetDirection_Implementation()
{
    return Direction;
}

void UXIHeroAnimInstance::SetCombatStyle_Implementation(ECombatStyle CStyle)
{
    CombatStyle = CStyle;
}