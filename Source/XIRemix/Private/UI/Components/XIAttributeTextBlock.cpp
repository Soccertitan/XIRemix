// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Components/XIAttributeTextBlock.h"
#include "AbilitySystemInterface.h"

UXIAttributeTextBlock::UXIAttributeTextBlock()
{
    FormatOptions.SetMaximumFractionalDigits(MaxFractionalDigits);
}

bool UXIAttributeTextBlock::SetupAttributeCallback(AActor* Actor)
{
    //Removes any existing attribute callbacks
    if(ASC)
    {
        ASC->GetGameplayAttributeValueChangeDelegate(ValueAttribute).RemoveAll(this);
    }
    
    if (IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(Actor))
    {
        ASC = ASI->GetAbilitySystemComponent();

        if(!ASC)
        {
            return false;
        }

        ValueChangedDelegateHandle = ASC->GetGameplayAttributeValueChangeDelegate(ValueAttribute).AddUObject(this, &UXIAttributeTextBlock::ValueChanged);

        bool bFoundAttribute;
        Value = ASC->GetGameplayAttributeValue(ValueAttribute, bFoundAttribute);
        SetValueText();
    }
    else
    {
        return false;
    }

    return true;
}

void UXIAttributeTextBlock::ValueChanged(const FOnAttributeChangeData& Data)
{
    Value = Data.NewValue;
    SetValueText();
}

void UXIAttributeTextBlock::SetValueText()
{
    UE_LOG(LogTemp, Warning, TEXT("Value: %f"), Value);
    this->SetText(FText::AsNumber(Value, &FormatOptions));
}