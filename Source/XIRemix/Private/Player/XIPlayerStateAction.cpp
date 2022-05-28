// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/XIPlayerStateAction.h"

AXIPlayerStateAction::AXIPlayerStateAction()
{
    InventoryMelee = CreateDefaultSubobject<UInventoryComponent>("MeleeItems");
    InventoryRanged = CreateDefaultSubobject<UInventoryComponent>("RangedItems");
    InventoryArmor = CreateDefaultSubobject<UInventoryComponent>("ArmorItems");
    InventoryAccessories = CreateDefaultSubobject<UInventoryComponent>("AccessoryItems");
    InventoryConsumables = CreateDefaultSubobject<UInventoryComponent>("ConsumableItems");
    InventoryMaterials = CreateDefaultSubobject<UInventoryComponent>("MaterialsItems");
    InventoryKeyItems = CreateDefaultSubobject<UInventoryComponent>("KeyItems");
}

UInventoryComponent* AXIPlayerStateAction::GetInventory(EItemType ItemType)
{
    if(ItemType == EItemType::WeaponMelee || ItemType == EItemType::Shield)
    {
        return InventoryMelee;
    }
    return nullptr;
}