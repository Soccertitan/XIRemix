// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XIUINavEquipmentWidget.h"
#include "UI/XIUINavCollectionEquippedItems.h"
#include "UI/Components/XIUINavComponentEquipSlot.h"
#include "UI/XICharacterStatusWidget.h"
#include "UI/XIItemDetailsWidget.h"
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
        EquippedItemsCollection->InitializeEquippedItems(HeroCharacter->GetXIEquipmentManagerComponent());

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
    }
}

void UXIUINavEquipmentWidget::OnEquipSlotHovered(UXIUINavComponent* XIComponentWidget)
{
    UXIUINavComponentEquipSlot* EquipSlotComponent = Cast<UXIUINavComponentEquipSlot>(XIComponentWidget);
    if(EquipSlotComponent)
    {
        EquipSlotReference = EquipSlotComponent->GetEquipSlot();
        ItemDetails->SetupItemDetailsWidget(EquipSlotComponent->GetItem());
    }
}

void UXIUINavEquipmentWidget::SetupCharacterStatus()
{
    CharacterStatus->SetupXICharacterStatusWidget(HeroCharacter);
    CharacterStatusSub->SetupXICharacterStatusWidget(HeroCharacter);
}