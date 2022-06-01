// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/XIPlayerStateAction.h"

AXIPlayerStateAction::AXIPlayerStateAction()
{
    InventoryMelee = CreateDefaultSubobject<UXIInventoryComponent>("MeleeItems");
    InventoryRanged = CreateDefaultSubobject<UXIInventoryComponent>("RangedItems");
    InventoryArmor = CreateDefaultSubobject<UXIInventoryComponent>("ArmorItems");
    InventoryAccessories = CreateDefaultSubobject<UXIInventoryComponent>("AccessoryItems");
    InventoryConsumables = CreateDefaultSubobject<UXIInventoryComponent>("ConsumableItems");
    InventoryMaterials = CreateDefaultSubobject<UXIInventoryComponent>("MaterialsItems");
    InventoryKeyItems = CreateDefaultSubobject<UXIInventoryComponent>("KeyItems");
}

UXIInventoryComponent* AXIPlayerStateAction::GetInventory(EItemType ItemType)
{
    if(ItemType == EItemType::WeaponMelee || ItemType == EItemType::Shield)
    {
        return InventoryMelee;
    }
    return nullptr;
}