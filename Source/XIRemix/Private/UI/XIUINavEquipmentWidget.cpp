// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XIUINavEquipmentWidget.h"
#include "UI/XIUINavCollectionEquippedItems.h"
#include "UI/Components/XIUINavComponentItemEquipSlot.h"
#include "UI/XICharacterStatusWidget.h"
#include "UI/XIItemDetailsWidget.h"
#include "UI/XIUINavInventoryWidget.h"
#include "Characters/XICharacterBaseHero.h"

void UXIUINavEquipmentWidget::NativeOnInitialized()
{
    HeroCharacter = Cast<AXICharacterBaseHero>(GetOwningPlayerPawn());

    SetupEquippedItems();
    SetupCharacterStatus();

    Super::NativeOnInitialized();
}

void UXIUINavEquipmentWidget::NativeConstruct()
{
    SetupCharacterStatus();

    Super::NativeConstruct();
}

void UXIUINavEquipmentWidget::SetupEquippedItems()
{
    if(HeroCharacter)
    {
        EquipmentManagerRef = HeroCharacter->GetXIEquipmentManagerComponent();
        EquippedItemsCollection->InitializeEquippedItems(EquipmentManagerRef);

        EquippedItemsCollection->BTNMain->OnButtonHover.AddUniqueDynamic(this, &UXIUINavEquipmentWidget::OnEquipSlotHovered);
        EquippedItemsCollection->BTNSub->OnButtonHover.AddUniqueDynamic(this, &UXIUINavEquipmentWidget::OnEquipSlotHovered);
        EquippedItemsCollection->BTNRange->OnButtonHover.AddUniqueDynamic(this, &UXIUINavEquipmentWidget::OnEquipSlotHovered);
        EquippedItemsCollection->BTNAmmo->OnButtonHover.AddUniqueDynamic(this, &UXIUINavEquipmentWidget::OnEquipSlotHovered);
        EquippedItemsCollection->BTNHead->OnButtonHover.AddUniqueDynamic(this, &UXIUINavEquipmentWidget::OnEquipSlotHovered);
        EquippedItemsCollection->BTNNeck->OnButtonHover.AddUniqueDynamic(this, &UXIUINavEquipmentWidget::OnEquipSlotHovered);
        EquippedItemsCollection->BTNEar1->OnButtonHover.AddUniqueDynamic(this, &UXIUINavEquipmentWidget::OnEquipSlotHovered);
        EquippedItemsCollection->BTNEar2->OnButtonHover.AddUniqueDynamic(this, &UXIUINavEquipmentWidget::OnEquipSlotHovered);
        EquippedItemsCollection->BTNBody->OnButtonHover.AddUniqueDynamic(this, &UXIUINavEquipmentWidget::OnEquipSlotHovered);
        EquippedItemsCollection->BTNHands->OnButtonHover.AddUniqueDynamic(this, &UXIUINavEquipmentWidget::OnEquipSlotHovered);
        EquippedItemsCollection->BTNRing1->OnButtonHover.AddUniqueDynamic(this, &UXIUINavEquipmentWidget::OnEquipSlotHovered);
        EquippedItemsCollection->BTNRing2->OnButtonHover.AddUniqueDynamic(this, &UXIUINavEquipmentWidget::OnEquipSlotHovered);
        EquippedItemsCollection->BTNBack->OnButtonHover.AddUniqueDynamic(this, &UXIUINavEquipmentWidget::OnEquipSlotHovered);
        EquippedItemsCollection->BTNWaist->OnButtonHover.AddUniqueDynamic(this, &UXIUINavEquipmentWidget::OnEquipSlotHovered);
        EquippedItemsCollection->BTNLegs->OnButtonHover.AddUniqueDynamic(this, &UXIUINavEquipmentWidget::OnEquipSlotHovered);
        EquippedItemsCollection->BTNFeet->OnButtonHover.AddUniqueDynamic(this, &UXIUINavEquipmentWidget::OnEquipSlotHovered);

        InventoryWidget->XIOnItemSelected.AddUniqueDynamic(this, &UXIUINavEquipmentWidget::OnItemSelected);
        InventoryWidget->XIOnItemHover.AddUniqueDynamic(this, &UXIUINavEquipmentWidget::OnItemHovered);
    }
}

void UXIUINavEquipmentWidget::OnEquipSlotHovered(UXIUINavComponent* XIComponentWidget)
{
    UXIUINavComponentItemEquipSlot* EquipSlotComponent = Cast<UXIUINavComponentItemEquipSlot>(XIComponentWidget);
    if(EquipSlotComponent)
    {
        EquipSlotReference = EquipSlotComponent->GetEquipSlot();
        ItemDetails->SetupItemDetailsWidget(EquipSlotComponent->GetItem());

        if(EquipSlotReference == EEquipSlot::MainHand || EquipSlotReference == EEquipSlot::SubHand)
        {
            InventoryWidget->GenerateItemsArray(EInventoryType::Melee);
        }
        else if (EquipSlotReference == EEquipSlot::Ranged || EquipSlotReference == EEquipSlot::Ammo)
        {
            InventoryWidget->GenerateItemsArray(EInventoryType::Ranged);
        }
        else if (EquipSlotReference == EEquipSlot::Body || EquipSlotReference == EEquipSlot::Head || EquipSlotReference == EEquipSlot::Hands || EquipSlotReference == EEquipSlot::Legs || EquipSlotReference == EEquipSlot::Feet)
        {
            InventoryWidget->GenerateItemsArray(EInventoryType::Armor);
        }
        else
        {
            InventoryWidget->GenerateItemsArray(EInventoryType::Accessory);
        }
    }
}

void UXIUINavEquipmentWidget::SetupCharacterStatus()
{
    CharacterStatus->SetupXICharacterStatusWidget(HeroCharacter);
    CharacterStatusSub->SetupXICharacterStatusWidget(HeroCharacter);
}

void UXIUINavEquipmentWidget::OnItemHovered(UXIItem* Item)
{
    ItemDetails->SetupItemDetailsWidget(Item);
}

void UXIUINavEquipmentWidget::OnItemSelected(UXIItem* Item)
{
    if(EquipmentManagerRef)
    {
        EquipmentManagerRef->EquipItem(Item, EquipSlotReference);
    }
}