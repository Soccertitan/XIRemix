// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/XICharacterBlendSpaces.h"

void UXICharacterBlendSpaces::GetCombatBlendSpace(UBlendSpace*& OutUpperBody, UBlendSpace*& OutLowerBody, ECombatStyle CombatStyle) const
{
    for(auto& Blend : CombatBlendSpaces)
    {
        if (Blend.CombatStyle == CombatStyle)
        {
            OutUpperBody = Blend.UpperBody;
            OutLowerBody = Blend.LowerBody;
            return;
        }
    }
    OutUpperBody = nullptr;
    OutLowerBody = nullptr;
}