// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Components/XIUINavComponentEquipSlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

UXIUINavComponentEquipSlot::UXIUINavComponentEquipSlot(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UXIUINavComponentEquipSlot::NativeConstruct()
{
    if(NavText)
    {
        NavText->SetText(EquipSlotText);
    }
    
    Super::NativeConstruct();
}

void UXIUINavComponentEquipSlot::SetItem(UXIItemEquipment* Item)
{
    ItemRef = Item;
    
    if(ItemRef)
    {
        SetItemThumbnail(ItemRef->Thumbnail);
    }
    else
    {
        SetItemThumbnail(nullptr);
    }
}

void UXIUINavComponentEquipSlot::SetItemThumbnail(UTexture2D* Thumbnail)
{
    ItemThumbnail->SetBrushFromTexture(Thumbnail);
    
    if(Thumbnail)
    {
        ItemThumbnail->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
    }
    else
    {
        ItemThumbnail->SetVisibility(ESlateVisibility::Hidden);
    }
}