// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Components/XIUINavComponentItemEquipSlot.h"
#include "Components/TextBlock.h"

void UXIUINavComponentItemEquipSlot::NativeConstruct()
{
    if(NavText)
    {
        NavText->SetText(EquipSlotText);
    }
    
    Super::NativeConstruct();
}