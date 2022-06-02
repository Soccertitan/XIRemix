// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Components/XIAttributeProgressBar.h"
#include "AbilitySystemInterface.h"

bool UXIAttributeProgressBar::SetupAttributeCallback(AActor* Actor)
{
    //Removes any existing attribute callbacks
    if(ASC)
    {
        ASC->GetGameplayAttributeValueChangeDelegate(CurrentValueAttribute).RemoveAll(this);
        ASC->GetGameplayAttributeValueChangeDelegate(MaxValueAttribute).RemoveAll(this);
    }
    
    if (IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(Actor))
    {
        ASC = ASI->GetAbilitySystemComponent();

        if(!ASC)
        {
            return false;
        }

        CurrentValueChangedDelegateHandle = ASC->GetGameplayAttributeValueChangeDelegate(CurrentValueAttribute).AddUObject(this, &UXIAttributeProgressBar::CurrentValueChanged);
        MaxValueChangedDelegateHandle = ASC->GetGameplayAttributeValueChangeDelegate(MaxValueAttribute).AddUObject(this, &UXIAttributeProgressBar::MaxValueChanged);

        bool bFoundAttribute;
        CurrentValue = ASC->GetGameplayAttributeValue(CurrentValueAttribute, bFoundAttribute);
        MaxValue = ASC->GetGameplayAttributeValue(MaxValueAttribute, bFoundAttribute);
        this->SetPercent(GetPercentValue());
    }
    else
    {
        return false;
    }

    return true;
}

float UXIAttributeProgressBar::GetPercentValue()
{
    return CurrentValue / FMath::Max(MaxValue, 1.f);
}

void UXIAttributeProgressBar::CurrentValueChanged(const FOnAttributeChangeData& Data)
{
    CurrentValue = Data.NewValue;
    this->SetPercent(GetPercentValue());
    OnCurrentValueChanged.Broadcast(Data.OldValue, Data.NewValue);
}

void UXIAttributeProgressBar::MaxValueChanged(const FOnAttributeChangeData& Data)
{
    MaxValue = Data.NewValue;
    this->SetPercent(GetPercentValue());
    OnMaxValueChanged.Broadcast(Data.OldValue, Data.NewValue);
}