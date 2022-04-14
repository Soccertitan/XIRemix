// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystem/ItemEquipment.h"

UItemEquipment::UItemEquipment()
{

}

USkeletalMesh* UItemEquipment::GetMesh(ERace Race, bool bWeaponInSubHand = false)
{
    if(bWeaponInSubHand)
    {
        if (SKMeshWeaponSubHand.IsValidIndex(0))
        {
            for (FXISKMeshEquipment& Item : SKMeshWeaponSubHand)
            {
                if (Item.Race == Race)
                {
                    return Item.Mesh;
                }
            }
        }
    }
    else
    {
        if (SKMeshDefault.IsValidIndex(0))
        {
            for (FXISKMeshEquipment& Item : SKMeshDefault)
            {
                if (Item.Race == Race)
                {
                    return Item.Mesh;
                }
            }
        }
    }
    return nullptr;
}