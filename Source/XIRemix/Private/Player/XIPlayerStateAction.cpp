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

UXIInventoryComponent* AXIPlayerStateAction::GetInventory(EInventoryType InventoryType)
{
    if(InventoryType == EInventoryType::Melee) return InventoryMelee;
    if(InventoryType == EInventoryType::Ranged) return InventoryRanged;
    if(InventoryType == EInventoryType::Armor) return InventoryArmor;
    if(InventoryType == EInventoryType::Accessory) return InventoryAccessories;
    if(InventoryType == EInventoryType::Consumable) return InventoryConsumables;
    if(InventoryType == EInventoryType::Material) return InventoryMaterials;
    if(InventoryType == EInventoryType::KeyItem) return InventoryKeyItems;

    return nullptr;
}