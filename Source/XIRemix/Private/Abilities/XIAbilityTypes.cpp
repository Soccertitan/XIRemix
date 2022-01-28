// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/XIAbilityTypes.h"


bool FGameplayAbilitySingleTargetData::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
    Ar << TargetActor;
    Ar << AttackMontage;
    Ar << UniqueID;
    bOutSuccess = true;
    return true;
}