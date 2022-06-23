// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/XICharacterAnimMontages.h"

UAnimMontage* UXICharacterAnimMontages::GetAutoAttackMontage(ECombatStyle CombatStyle, float Speed, float Direction) const
{
    for(auto& Montage : CombatMontages)
    {
        if(Montage.CombatStyle == CombatStyle)
        {
            // Stationary Attack
		    if(FMath::IsNearlyZero(Speed))
		    {
                if (!Montage.BasicAttacks.IsValidIndex(0))
                {
                    return nullptr;
                }
                int number = FMath::RandRange(0, Montage.BasicAttacks.Num() - 1);
                return Montage.BasicAttacks[number];
            }
            
            // Moving Right Attack Montage
		    else if((Direction > 40) & (Direction < 140))
		    {
                return Montage.AtkRight;
            }

            // Moving Left Attack Montage
            else if((Direction > -140) & (Direction < -40))
            {
                return Montage.AtkLeft;
            }

            // Moving Backwards Attack Montage
		    else if((Direction >= 140) | (Direction <= -140))
		    {
                return Montage.AtkBw;
            }

            // Moving Forwards Attack Montage
		    else
		    {
                return Montage.AtkFw;
            }
        }
    }
    return nullptr;
}

UAnimMontage* UXICharacterAnimMontages::GetRangedMontage(FGameplayTag RangedWeapon) const
{
    for(auto& Montage : RangedMontages)
    {
        if(Montage.RangedWeapon.MatchesTag(RangedWeapon))
        {
            return Montage.AnimMontage;
        }
    }
    return DefaultRanged;
}

UAnimMontage* UXICharacterAnimMontages::GetMagicMontage(EXIMagicType MagicType) const
{
    for(auto& Montage : MagicMontages)
    {
        if(Montage.MagicType == MagicType)
        {
            return Montage.AnimMontage;
        }
    }
    return DefaultMagic;
}

UAnimMontage* UXICharacterAnimMontages::GetJobAbilityMontage(bool bIsWeaponOut) const
{
    if(bIsWeaponOut)
    {
        return JobAbilityCombat;
    }
    else
    {
        return JobAbility;
    }
}

UAnimMontage* UXICharacterAnimMontages::GetSheatheWeaponMontage(EXISheatheStyle SheatheStyle) const
{
    for(auto& Montage : SheatheMontages)
    {
        if(Montage.SheatheStyle == SheatheStyle)
        {
            return Montage.SheatheWeapon;
        }
    }

    return DefaultSheatheWeapon;
}

UAnimMontage* UXICharacterAnimMontages::GetDrawWeaponMontage(EXISheatheStyle SheatheStyle) const
{
    for(auto& Montage : SheatheMontages)
    {
        if(Montage.SheatheStyle == SheatheStyle)
        {
            return Montage.DrawWeapon;
        }
    }

    return DefaultDrawWeapon;
}