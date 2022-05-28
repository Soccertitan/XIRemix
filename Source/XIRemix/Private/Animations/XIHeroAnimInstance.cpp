// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/XIHeroAnimInstance.h"

float UXIHeroAnimInstance::GetSpeed()
{
    return Speed;
}

float UXIHeroAnimInstance::GetDirection()
{
    return Direction;
}

void UXIHeroAnimInstance::SetCombatStyle_Implementation(ECombatStyle InCombatStyle)
{
    CombatStyle = InCombatStyle;

    if(BlendSpaces)
    {
        BlendSpaces->GetCombatBlendSpace(CombatUpperBody, CombatLowerBody, InCombatStyle);
    }
}