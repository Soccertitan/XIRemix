// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystem/ItemEquipment.h"

UItemEquipment::UItemEquipment()
{

}

USkeletalMesh* UItemEquipment::GetMesh(ERace Race, bool bWeaponInSubHand = false)
{
    
    if (SKMesh.IsValidIndex(0))
    {
        for (FXISKMeshEquipment& Item : SKMesh)
        {
            if (Item.Race == Race)
            {
                if (bWeaponInSubHand)
                {
                    return Item.MeshSecondary;
                }
                else
                {
                    return Item.MeshDefault;
                }
            }
        }
    }
    return nullptr;
}