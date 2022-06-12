// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XIUINavInventoryWidget.h"
#include "Items/XIItem.h"
#include "Components/Textblock.h"

UXIUINavInventoryWidget::UXIUINavInventoryWidget()
{
    NumberOfItemsToDisplay = 20;
}

void UXIUINavInventoryWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    PlayerState = Cast<AXIPlayerStateAction>(GetOwningPlayerState());

    if(PlayerState)
    {
        ReadyToGenerateInventory();
    }
}

void UXIUINavInventoryWidget::GenerateItemsArray(EInventoryType InventoryType)
{
    TArray<UXIItem*> TempItems;

    if(PlayerState)
    {
        UXIInventoryComponent* InvCompRefTemp = PlayerState->GetInventory(InventoryType);
        if (InvCompRefTemp == InventoryComponentRef)
        {
            return;
        }
        
        InventoryComponentRef = InvCompRefTemp;
        FirstIndex = 0;
        LastIndex = NumberOfItemsToDisplay - 1;

        if(InventoryComponentRef)
        {
            ItemsRef = InventoryComponentRef->GetItems();
            
            for(int32 i = FirstIndex; i <= LastIndex; i++)
            {
                if(ItemsRef.IsValidIndex(i))
                {
                    TempItems.Add(ItemsRef[i]);
                }
            }
            CurrentItemPage = 1;
            SetCurrentItemPageText();
            SetOptionalWidgetText();
            OnItemsReady(TempItems);
        }
    }
}

void UXIUINavInventoryWidget::NextItemPage()
{
    // If we are not at the end of the array.
    if (!((ItemsRef.Num() -1 ) <= LastIndex))
    {
        FirstIndex += NumberOfItemsToDisplay;
        LastIndex += NumberOfItemsToDisplay;
        CurrentItemPage += 1;

        TArray<UXIItem*> TempItems;
        for(int32 i = FirstIndex; i <= LastIndex; i++)
        {
            if(ItemsRef.IsValidIndex(i))
            {
                TempItems.Add(ItemsRef[i]);
            }
        }

        SetCurrentItemPageText();
        OnSwitchItemsPage(TempItems);
    }
}

void UXIUINavInventoryWidget::PreviousItemPage()
{
    // If we are not at the start of the array.
    if (!(FirstIndex <= 0))
    {
        FirstIndex -= NumberOfItemsToDisplay;
        LastIndex -= NumberOfItemsToDisplay;
        CurrentItemPage -= 1;

        TArray<UXIItem*> TempItems;
        for(int32 i = FirstIndex; i <= LastIndex; i++)
        {
            if(ItemsRef.IsValidIndex(i))
            {
                TempItems.Add(ItemsRef[i]);
            }
        }

        SetCurrentItemPageText();
        OnSwitchItemsPage(TempItems);
    }
}

void UXIUINavInventoryWidget::SetOptionalWidgetText()
{
    if(InventoryCapacityText)
    {
        if(InventoryComponentRef)
        {
            InventoryCapacityText->SetText(FText::AsNumber(InventoryComponentRef->GetCapacity()));
        }
    }

    if(ItemCountText)
    {
        ItemCountText->SetText(FText::AsNumber(ItemsRef.Num()));
    }

    if(LastItemPageText)
    {
        float Pages = ItemsRef.Num() / NumberOfItemsToDisplay;
        LastItemPageText->SetText(FText::AsNumber(FMath::CeilToInt(Pages + 1)));
    }
}

void UXIUINavInventoryWidget::SetCurrentItemPageText()
{
    if(CurrentItemPageText)
    {
        CurrentItemPageText->SetText(FText::AsNumber(CurrentItemPage));
    }
}

void UXIUINavInventoryWidget::BindButtonsToEventDispatcher(TArray<UXIUINavComponentItemSlot*> ItemButtons)
{
    // Do I need to remove old delegates or does UE garbage collection do this for us?
    if(!ItemButtons.IsEmpty())
    {
        for(auto& Button : ItemButtons)
        {
            Button->OnButtonClicked.AddUniqueDynamic(this, &UXIUINavInventoryWidget::OnButtonClicked);
            Button->OnButtonHover.AddUniqueDynamic(this, &UXIUINavInventoryWidget::OnButtonHover);
        }
    }
}

void UXIUINavInventoryWidget::OnButtonClicked(class UXIUINavComponent* Button)
{
    UXIUINavComponentItemSlot* ItemButton = Cast<UXIUINavComponentItemSlot>(Button);
    if(ItemButton)
    {
        XIOnItemSelected.Broadcast(ItemButton->GetItem());
    }
}

void UXIUINavInventoryWidget::OnButtonHover(class UXIUINavComponent* Button)
{
    UXIUINavComponentItemSlot* ItemButton = Cast<UXIUINavComponentItemSlot>(Button);
    if(ItemButton)
    {
        XIOnItemHover.Broadcast(ItemButton->GetItem());
    }
}