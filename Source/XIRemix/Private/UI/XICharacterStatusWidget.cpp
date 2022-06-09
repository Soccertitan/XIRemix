// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XICharacterStatusWidget.h"
#include "GameplayTagContainer.h"
#include "Blueprint/WidgetTree.h"
#include "Characters/XICharacterBaseHero.h"
#include "FunctionLibrary/XIGameplayFunctionLibrary.h"

void UXICharacterStatusWidget::NativeOnInitialized()
{
    GetAttributeTextBlocks();

    Super::NativeOnInitialized();
}

void UXICharacterStatusWidget::SetupXICharacterStatusWidget(AActor* Actor)
{
    TargetActor = Actor;

    SetupMainSubJobValues(TargetActor);
    SetupAttributeBindings();

    if(CharacterNameText)
    {
        CharacterNameText->SetText(UXIGameplayFunctionLibrary::GetCharacterName(TargetActor));
    }
}

void UXICharacterStatusWidget::SetupMainSubJobValues(AActor* Actor)
{
    AXICharacterBaseHero* HeroCharacter = Cast<AXICharacterBaseHero>(Actor);

    if(HeroCharacter)
    {
        FXICharacterHeroActiveJobsLevels CharacterJobs = HeroCharacter->GetCharacterActiveJobsAndLevels();

        const FRegexPattern Pattern(TEXT("[a-zA-Z]*$"));

        if(MainJobText)
        {
            FRegexMatcher Matcher(Pattern, CharacterJobs.MainJobTag.ToString());
            if(Matcher.FindNext() && CharacterJobs.MainJobTag.IsValid())
            {
                int32 StartMatch = Matcher.GetMatchBeginning();
	            int32 EndMatch = Matcher.GetMatchEnding();

                FText JobText = FText::FromString((CharacterJobs.MainJobTag.ToString()).RightChop(StartMatch));

                MainJobText->SetText(JobText);
                MainJobText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
            }
            else
            {
                MainJobText->SetVisibility(ESlateVisibility::Hidden);
            }
        }

        if(MainJobLv)
        {
            if(CharacterJobs.MainJobLevel != 0)
            {
                MainJobLv->SetText(FText::AsNumber(CharacterJobs.MainJobLevel));
                MainJobLv->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
            }
            else
            {
                MainJobLv->SetVisibility(ESlateVisibility::Hidden);
            }
        }

        if(SubJobText)
        {
            FRegexMatcher Matcher(Pattern, CharacterJobs.SubJobTag.ToString());
            if(Matcher.FindNext() && CharacterJobs.SubJobTag.IsValid())
            {
                int32 StartMatch = Matcher.GetMatchBeginning();
	            int32 EndMatch = Matcher.GetMatchEnding();

                FText JobText = FText::FromString((CharacterJobs.SubJobTag.ToString()).RightChop(StartMatch));

                SubJobText->SetText(JobText);
                SubJobText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
            }
            else
            {
                SubJobText->SetVisibility(ESlateVisibility::Hidden);
            }

        }

        if(SubJobLv)
        {
            if(CharacterJobs.SubJobLevel != 0)
            {
                SubJobLv->SetText(FText::AsNumber(CharacterJobs.SubJobLevel));
                SubJobLv->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
            }
            else
            {
                SubJobLv->SetVisibility(ESlateVisibility::Hidden);
            }
        }
    }
}

void UXICharacterStatusWidget::SetupAttributeBindings()
{
    for(auto& TextBlock : AttributeTextBlocks)
    {
        TextBlock->SetupAttributeCallback(TargetActor);
    }
}

void UXICharacterStatusWidget::GetAttributeTextBlocks()
{
    TArray<UWidget*> Widgets;
    this->WidgetTree->GetAllWidgets(Widgets);

    for(auto& Widget : Widgets)
    {
        UXIAttributeTextBlock* ATB = Cast<UXIAttributeTextBlock>(Widget);
        if(ATB)
        {
            AttributeTextBlocks.AddUnique(ATB);
        }
    }
}