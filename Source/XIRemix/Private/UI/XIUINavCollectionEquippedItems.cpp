// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XIUINavCollectionEquippedItems.h"
#include "Items/XIItemEquipment.h"
#include "UI/Components/XIUINavComponentEquipSlot.h"

UXIUINavCollectionEquippedItems::UXIUINavCollectionEquippedItems(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
}

void UXIUINavCollectionEquippedItems::InitializeEquippedItems(class UXIEquipmentManagerComponent* EquipmentComponent)
{
    if(EMC)
    {
        EMC->OnEquipmentUpdated.RemoveAll(this);
    }
    
    EMC = EquipmentComponent;

    if(EMC)
    {
        EMC->OnEquipmentUpdated.AddDynamic(this, &UXIUINavCollectionEquippedItems::SetEquippedItems);
        SetEquippedItems();
    }
}

void UXIUINavCollectionEquippedItems::SetEquippedItems()
{
    if(EMC)
    {
        EquippedItems = EMC->GetEquippedItems();

        BTNMain->SetItem(EquippedItems.MainHand);
        BTNSub->SetItem(EquippedItems.SubHand);
        BTNRange->SetItem(EquippedItems.Ranged);
        BTNAmmo->SetItem(EquippedItems.Ammo);
        BTNHead->SetItem(EquippedItems.Head);
        BTNNeck->SetItem(EquippedItems.Neck);
        BTNEar1->SetItem(EquippedItems.Ear1);
        BTNEar2->SetItem(EquippedItems.Ear2);
        BTNBody->SetItem(EquippedItems.Body);
        BTNHands->SetItem(EquippedItems.Hands);
        BTNRing1->SetItem(EquippedItems.Ring1);
        BTNRing2->SetItem(EquippedItems.Ring2);
        BTNBack->SetItem(EquippedItems.Back);
        BTNWaist->SetItem(EquippedItems.Waist);
        BTNLegs->SetItem(EquippedItems.Legs);
        BTNFeet->SetItem(EquippedItems.Feet);
    }
}