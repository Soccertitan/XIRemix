// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XIItemDetailsWidget.h"
#include "Items/XIItemEquipment.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "XIEnums.h"

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
                ItemDescriptionText->SetText(GetArmorText(Item));
                break;
            }

            case EItemType::Ammo:
            {
                ItemDescriptionText->SetText(GetWeaponText(Item));
                break;
            }

            case EItemType::Armor:
            {
                ItemDescriptionText->SetText(GetArmorText(Item));
                break;
            }

            case EItemType::Instrument:
            {
                ItemDescriptionText->SetText(GetArmorText(Item));
                break;
            }

            case EItemType::Shield:
            {
                ItemDescriptionText->SetText(GetArmorText(Item));
                break;
            }
            
            case EItemType::WeaponMelee:
            {
                ItemDescriptionText->SetText(GetWeaponText(Item));
                break;
            }

            case EItemType::WeaponRange:
            {
                ItemDescriptionText->SetText(GetWeaponText(Item));
                break;
            }

            default:
            {
                ItemDescriptionText->SetText(Item->Description);
                break;
            }
        }
        this->SetVisibility(ESlateVisibility::Visible);
    }
}

FText UXIItemDetailsWidget::GetWeaponText(UXIItem* Item)
{
    UXIItemEquipment* ItemEquipment = Cast<UXIItemEquipment>(Item);
    if(!ItemEquipment || !TextMap)
    {
        return FText();
    }

    FText FinalText;

    FFormatNamedArguments Args;
    Args.Add(TEXT("Jobs"), GetJobRequirementText(ItemEquipment->JobRequirements));
    Args.Add(TEXT("WeaponType"), TextMap->TagToText.FindRef(ItemEquipment->WeaponType));
    Args.Add(TEXT("Damage"), FText::AsNumber(ItemEquipment->Damage));
    Args.Add(TEXT("Delay"), FText::AsNumber(ItemEquipment->Delay));
    Args.Add(TEXT("Level"), FText::AsNumber(ItemEquipment->LevelRequirement));
    Args.Add(TEXT("Attributes"), GetAttributeText(ItemEquipment->Attributes));

    FText Description = ItemEquipment->Description;
    if(!Description.IsEmptyOrWhitespace())
    {
        Description = FText::Format(LOCTEXT("Description", "{Description}\n"), Description);
    }
    Args.Add(TEXT("Description"), Description);

    if(ItemEquipment->WeaponType == FGameplayTag::RequestGameplayTag("Weapon.Melee.HandToHand"))
    {
        FinalText = FText::Format(LOCTEXT("WeaponText", "{WeaponType}\nDMG: +{Damage} Delay: +{Delay}\n{Attributes}{Description}LV.{Level} {Jobs}"), Args);
    }
    else
    {
       FinalText = FText::Format(LOCTEXT("WeaponText", "{WeaponType}\nDMG: {Damage} Delay: {Delay}\n{Attributes}{Description}LV.{Level} {Jobs}"), Args);
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

    FText FinalText;

    FFormatNamedArguments Args;
    Args.Add(TEXT("Jobs"), GetJobRequirementText(ItemEquipment->JobRequirements));
    Args.Add(TEXT("ArmorType"), TextMap->EquipSlotToText.FindRef(ItemEquipment->EquipSlot[0]));
    Args.Add(TEXT("Attributes"), GetAttributeText(ItemEquipment->Attributes));
    Args.Add(TEXT("Level"), FText::AsNumber(ItemEquipment->LevelRequirement));

    FText Description = ItemEquipment->Description;
    if(!Description.IsEmptyOrWhitespace())
    {
        Description = FText::Format(LOCTEXT("Description", "\n{Description}"), Description);
    }
    Args.Add(TEXT("Description"), Description);
    
    FinalText = FText::Format(LOCTEXT("ArmorText", "{ArmorType}\n{Attributes}LV.{Level} {Jobs}"), Args);
    
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

FText UXIItemDetailsWidget::GetAttributeText(TArray<FXIItemAttributes> Attributes)
{
    FText FinalText;

    if(TextMap)
    {
        FText DefenseText;
        FText AttributeText;
        FText AttributeCollection;
        float Value = 0;

        FFormatNamedArguments Args;
        Args.Add(TEXT("AttributeCollection"), AttributeCollection);

        for(auto& Attribute : Attributes)
        {
            Value = Attribute.Value;
            Args.Add(TEXT("Value"), FText::AsNumber(Value));

            if(Attribute.AttributeTag == FGameplayTag::RequestGameplayTag("SetByCaller.Attributes.Defense"))
            {
                DefenseText = FText::Format(LOCTEXT("Defense", "DEF:{Value}"), Args);
                Args.Add(TEXT("Defense"), DefenseText);
            }
            else
            {
                AttributeText = TextMap->TagToText.FindRef(Attribute.AttributeTag);
                Args.Add(TEXT("Attribute"), AttributeText);

                if(!AttributeText.IsEmptyOrWhitespace())
                {
                    if (Value > 0)
                    {
                        AttributeCollection = FText::Format(LOCTEXT("Attribute", "{AttributeCollection}{Attribute}+{Value} "), Args);
                    }
                    else
                    {
                        AttributeCollection = FText::Format(LOCTEXT("Attribute", "{AttributeCollection}{Attribute}{Value} "), Args);
                    }
                    Args.Add(TEXT("AttributeCollection"), AttributeCollection);
                }
            }
        }

        if (DefenseText.IsEmptyOrWhitespace() && !AttributeCollection.IsEmptyOrWhitespace())
        {
            FinalText = FText::Format(LOCTEXT("FinalAttributes", "{AttributeCollection}\n"), Args);
        }
        else if (!DefenseText.IsEmptyOrWhitespace() && !AttributeCollection.IsEmptyOrWhitespace())
        {
            FinalText = FText::Format(LOCTEXT("FinalAttributes", "{Defense} {AttributeCollection}\n"), Args);

        }
        else if (!DefenseText.IsEmptyOrWhitespace())
        {
            FinalText = FText::Format(LOCTEXT("FinalAttributes", "{Defense}\n"), Args);
        }
    }
    return FinalText;
}

#undef LOCTEXT_NAMESPACE