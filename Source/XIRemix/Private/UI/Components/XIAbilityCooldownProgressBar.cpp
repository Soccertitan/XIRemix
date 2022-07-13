// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Components/XIAbilityCooldownProgressBar.h"
#include "AbilitySystemInterface.h"

bool UXIAbilityCooldownProgressBar::SetupCooldownCallback(AActor* Actor, FGameplayTagContainer InCooldownTags)
{
    if (IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(Actor))
    {
        UAbilitySystemComponent* InASC = ASI->GetAbilitySystemComponent();

        return SetupCooldownCallback(InASC, InCooldownTags);
    }
    return false;
}

bool UXIAbilityCooldownProgressBar::SetupCooldownCallback(UAbilitySystemComponent* InASC, FGameplayTagContainer InCooldownTags)
{
    ClearCooldownCallback();

    if(IsValid(InASC))
    {
        CooldownTags = InCooldownTags;
        ASC = InASC;

        ASC->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(this, &UXIAbilityCooldownProgressBar::OnActiveGameplayEffectAddedCallback);
        
        TArray<FGameplayTag> CooldownTagArray;
	    CooldownTags.GetGameplayTagArray(CooldownTagArray);
	
	    for (FGameplayTag CooldownTag : CooldownTagArray)
	    {
		    ASC->RegisterGameplayTagEvent(CooldownTag, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &UXIAbilityCooldownProgressBar::CooldownTagChanged);
	    }

        TimeRemaining = 0.0f;
        Duration = 0.0f;
        
        GetCooldownRemainingForTag(CooldownTags, TimeRemaining, Duration);
        if(TimeRemaining > 0)
        {
            GetWorld()->GetTimerManager().SetTimer(TimerHandle_RefreshPercent, this, &UXIAbilityCooldownProgressBar::RefreshProgressBarPercent, RefreshRate, true);
        }
    }
    return false;
}

void UXIAbilityCooldownProgressBar::OnActiveGameplayEffectAddedCallback(UAbilitySystemComponent * Target, const FGameplayEffectSpec & SpecApplied, FActiveGameplayEffectHandle ActiveHandle)
{
	FGameplayTagContainer AssetTags;
	SpecApplied.GetAllAssetTags(AssetTags);
	
	FGameplayTagContainer GrantedTags;
	SpecApplied.GetAllGrantedTags(GrantedTags);

	TArray<FGameplayTag> CooldownTagArray;
	CooldownTags.GetGameplayTagArray(CooldownTagArray);

	for (FGameplayTag CooldownTag : CooldownTagArray)
	{
		if (AssetTags.HasTagExact(CooldownTag) || GrantedTags.HasTagExact(CooldownTag))
		{
			TimeRemaining = 0.0f;
			Duration = 0.0f;
			// Expecting cooldown tag to always be first tag
			FGameplayTagContainer CooldownTagContainer(GrantedTags.GetByIndex(0));
			GetCooldownRemainingForTag(CooldownTagContainer, TimeRemaining, Duration);
            GetWorld()->GetTimerManager().SetTimer(TimerHandle_RefreshPercent, this, &UXIAbilityCooldownProgressBar::RefreshProgressBarPercent, RefreshRate, true);

			if (ASC->GetOwnerRole() == ROLE_Authority)
			{
				// Player is Server
				OnCooldownBegin.Broadcast(CooldownTag, TimeRemaining, Duration);
			}
			else if (!bUseServerCooldown && SpecApplied.GetContext().GetAbilityInstance_NotReplicated())
			{
				// Client using predicted cooldown
				OnCooldownBegin.Broadcast(CooldownTag, TimeRemaining, Duration);
			}
			else if (bUseServerCooldown && SpecApplied.GetContext().GetAbilityInstance_NotReplicated() == nullptr)
			{
				// Client using Server's cooldown. This is Server's corrective cooldown GE.
				OnCooldownBegin.Broadcast(CooldownTag, TimeRemaining, Duration);
			}
			else if (bUseServerCooldown && SpecApplied.GetContext().GetAbilityInstance_NotReplicated())
			{
				// Client using Server's cooldown but this is predicted cooldown GE.
				// This can be useful to gray out abilities until Server's cooldown comes in.
				OnCooldownBegin.Broadcast(CooldownTag, -1.0f, -1.0f);
			}
		}
	}
}

void UXIAbilityCooldownProgressBar::CooldownTagChanged(const FGameplayTag InCooldownTag, int32 NewCount)
{
	if (NewCount == 0)
	{
        this->SetPercent(1.f);
		OnCooldownEnd.Broadcast(InCooldownTag, -1.0f, -1.0f);
	}
}

bool UXIAbilityCooldownProgressBar::GetCooldownRemainingForTag(FGameplayTagContainer InCooldownTags, float & OutTimeRemaining, float & OutCooldownDuration)
{
	if (IsValid(ASC))
	{
		OutTimeRemaining = 0.f;
		OutCooldownDuration = 0.f;

		FGameplayEffectQuery const Query = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(InCooldownTags);
		TArray< TPair<float, float> > DurationAndTimeRemaining = ASC->GetActiveEffectsTimeRemainingAndDuration(Query);
		if (DurationAndTimeRemaining.Num() > 0)
		{
			int32 BestIdx = 0;
			float LongestTime = DurationAndTimeRemaining[0].Key;
			for (int32 Idx = 1; Idx < DurationAndTimeRemaining.Num(); ++Idx)
			{
				if (DurationAndTimeRemaining[Idx].Key > LongestTime)
				{
					LongestTime = DurationAndTimeRemaining[Idx].Key;
					BestIdx = Idx;
				}
			}

			OutTimeRemaining = DurationAndTimeRemaining[BestIdx].Key;
			OutCooldownDuration = DurationAndTimeRemaining[BestIdx].Value;

			return true;
		}
	}
	return false;
}

void UXIAbilityCooldownProgressBar::RefreshProgressBarPercent()
{
    this->SetPercent(1.f - (TimeRemaining / FMath::Max(Duration, 0.01f)));
    TimeRemaining = TimeRemaining - RefreshRate;

    OnPercentUpdated.Broadcast(CooldownTags.GetByIndex(0), TimeRemaining, Duration);

    if(TimeRemaining <= 0)
    {
        GetWorld()->GetTimerManager().ClearTimer(TimerHandle_RefreshPercent);
    }
}

void UXIAbilityCooldownProgressBar::ClearCooldownCallback()
{
    if (IsValid(ASC))
	{
		ASC->OnActiveGameplayEffectAddedDelegateToSelf.RemoveAll(this);
		
        TArray<FGameplayTag> CooldownTagArray;
		CooldownTags.GetGameplayTagArray(CooldownTagArray);

		for (FGameplayTag CooldownTag : CooldownTagArray)
		{
			ASC->RegisterGameplayTagEvent(CooldownTag, EGameplayTagEventType::NewOrRemoved).RemoveAll(this);
		}
	}
}

void UXIAbilityCooldownProgressBar::UpdateImage(UTexture2D* Image)
{
    if(Image)
    {
        FSlateBrush Brush = WidgetStyle.BackgroundImage;
        Brush.SetResourceObject(Image);
        WidgetStyle.SetBackgroundImage(Brush);

        Brush = WidgetStyle.FillImage;
        Brush.SetResourceObject(Image);
        WidgetStyle.SetFillImage(Brush);
        this->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        this->SetVisibility(ESlateVisibility::Hidden);
    }
}