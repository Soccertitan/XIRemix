// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XIItemDetailsWidget.h"
#include "Items/XIItemEquipment.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#define LOCTEXT_NAMESPACE "ItemDetails"

void UXIItemDetailsWidget::SetupItemDetailsWidget(UXIItem* Item)
{
    if(!Item)
    {
        this->SetVisibility(ESlateVisibility::Collapsed);
    }
    else
    {
        ItemThumbnail->SetBrushFromTexture(Item->Thumbnail);
        ItemNameText->SetText(Item->Name);

        switch (Item->ItemType)
        {
            case EItemType::Accessory:
            {
                break;
            }

            case EItemType::Ammo:
            {
                ItemDescriptionText->SetText(GetWeaponText(Item));
                this->SetVisibility(ESlateVisibility::Visible);
                break;
            }

            case EItemType::Armor:
            {
                break;
            }

            case EItemType::Instrument:
            {
                break;
            }

            case EItemType::Shield:
            {
                break;
            }
            
            case EItemType::WeaponMelee:
            {
                ItemDescriptionText->SetText(GetWeaponText(Item));
                this->SetVisibility(ESlateVisibility::Visible);
                break;
            }

            case EItemType::WeaponRange:
            {
                ItemDescriptionText->SetText(GetWeaponText(Item));
                this->SetVisibility(ESlateVisibility::Visible);
                break;
            }

            default:
            {
                ItemDescriptionText->SetText(Item->Description);
                this->SetVisibility(ESlateVisibility::Visible);
                break;
            }
        }
    }
}

FText UXIItemDetailsWidget::GetWeaponText(UXIItem* Item)
{
    UXIItemEquipment* ItemEquipment = Cast<UXIItemEquipment>(Item);
    if(!ItemEquipment || !TextMap)
    {
        return FText();
    }

    FText JobReq = GetJobRequirementText(ItemEquipment->JobRequirements);
    FText WeaponType = TextMap->TagToText.FindRef(ItemEquipment->WeaponType);

    FFormatNamedArguments Args;
    Args.Add(TEXT("Jobs"), JobReq);
    Args.Add(TEXT("WeaponType"), WeaponType);
    Args.Add(TEXT("Damage"), FText::AsNumber(ItemEquipment->Damage));
    Args.Add(TEXT("Delay"), FText::AsNumber(ItemEquipment->Delay));
    Args.Add(TEXT("Level"), FText::AsNumber(ItemEquipment->LevelRequirement));
    Args.Add(TEXT("Description"), ItemEquipment->Description);

    FText FinalText;

    if(ItemEquipment->WeaponType == FGameplayTag::RequestGameplayTag("Weapon.Melee.HandToHand"))
    {
        FinalText = FText::Format(LOCTEXT("WeaponText", "{WeaponType}\nDMG: +{Damage} Delay: +{Delay}\n{Description}\nLV.{Level} {Jobs}"), Args);
    }
    else
    {
       FinalText = FText::Format(LOCTEXT("WeaponText", "{WeaponType}\nDMG: {Damage} Delay: {Delay}\n{Description}\nLV.{Level} {Jobs}"), Args);
    }
    
    return FinalText;
}

FText UXIItemDetailsWidget::GetArmorText(UXIItem* Item)
{
    UXIItemEquipment* ItemEquipment = Cast<UXIItemEquipment>(Item);
    if(!ItemEquipment || !TextMap)
    {
        return FText();
    }

    FText JobReq = GetJobRequirementText(ItemEquipment->JobRequirements);
    EEquipSlot EquipSlot = ItemEquipment->EquipSlot[0];
    // FText ArmorType = FText::FromString();

    FFormatNamedArguments Args;
    Args.Add(TEXT("Jobs"), JobReq);
    // Args.Add(TEXT("WeaponType"), WeaponType);
    Args.Add(TEXT("Damage"), FText::AsNumber(ItemEquipment->Damage));
    Args.Add(TEXT("Delay"), FText::AsNumber(ItemEquipment->Delay));
    Args.Add(TEXT("Level"), FText::AsNumber(ItemEquipment->LevelRequirement));
    Args.Add(TEXT("Description"), ItemEquipment->Description);

    FText FinalText;

    // if(ItemEquipment->WeaponType == FGameplayTag::RequestGameplayTag("Weapon.Melee.HandToHand"))
    // {
    //     FinalText = FText::Format(LOCTEXT("WeaponText", "{WeaponType}\nDMG: +{Damage} Delay: +{Delay}\n{Description}\nLV.{Level} {Jobs}"), Args);
    // }
    // else
    // {
    //    FinalText = FText::Format(LOCTEXT("WeaponText", "{WeaponType}\nDMG: {Damage} Delay: {Delay}\n{Description}\nLV.{Level} {Jobs}"), Args);
    // }
    
    return FinalText;
}

FText UXIItemDetailsWidget::GetJobRequirementText(UXIJobTagCollection* JobTagCollection)
{
    if(!JobTagCollection)
    {
        return FText::FromString(TEXT("All Jobs"));
    }
    
    if(TextMap)
    {
        TArray<FGameplayTag> Tags;
        (JobTagCollection->JobTags).GetGameplayTagArray(Tags);

        FString JobReq;

        for(auto& Tag : Tags)
        {
            FString TempString = (TextMap->TagToText.FindRef(Tag)).ToString();
            if (!TempString.IsEmpty())
            {
                JobReq = JobReq.Append(TempString);
                JobReq = JobReq.Append("/");
            }
        }

        JobReq = JobReq.LeftChop(1);
        return FText::FromString(JobReq);

    }
    return FText();
}

FText UXIItemDetailsWidget::GetAttributeText(UXIItem* Item)
{
    return FText();
}

#undef LOCTEXT_NAMESPACE