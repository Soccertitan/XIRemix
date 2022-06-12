// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Components/XIUINavComponentItemSlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UXIUINavComponentItemSlot::SetItem(UXIItem* Item)
{
    ItemRef = Item;

    if(ItemRef)
    {
        SetItemThumbnail(ItemRef->Thumbnail);
        SetItemName(ItemRef->Name);
    }
    else
    {
        SetItemThumbnail(nullptr);
        SetItemName(FText());
    }
}

void UXIUINavComponentItemSlot::SetItemThumbnail(UTexture2D* Thumbnail)
{
    if(ItemThumbnail)
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
}

void UXIUINavComponentItemSlot::SetItemName(FText Name)
{
    if(ItemName)
    {
        ItemName->SetText(Name);
    }
}