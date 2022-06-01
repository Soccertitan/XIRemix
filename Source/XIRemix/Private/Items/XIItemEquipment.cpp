// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/XIItemEquipment.h"

UXIItemEquipment::UXIItemEquipment()
{

}

USkeletalMesh* UXIItemEquipment::GetMesh(ERace Race)
{
    return GetMesh(Race, false);
}

USkeletalMesh* UXIItemEquipment::GetMesh(ERace Race, bool bWeaponInSubHand = false)
{
    
    if (SKMeshMap.IsValidIndex(0))
    {
        for (auto& Item : SKMeshMap)
        {
            if (Item.Race == Race)
            {
                if (bWeaponInSubHand)
                {
                    return Item.SubHand;
                }
                else
                {
                    return Item.Default;
                }
            }
        }
    }
    return nullptr;
}