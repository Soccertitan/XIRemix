// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/XIAbilitySystemComponent.h"
#include "Abilities/XIGameplayAbility.h"
#include "GameplayTagsManager.h"
#include "AbilitySystemGlobals.h"
#include "GameplayCueManager.h"

UXIAbilitySystemComponent::UXIAbilitySystemComponent()
{
    static ConstructorHelpers::FObjectFinder<UXIAbilityTagRelationship> AbilityTagRelationshipObj(TEXT("XIAbilityTagRelationship'/Game/XIRemix/Core/DataAssets/DA_XIGameplayTagRelationships.DA_XIGameplayTagRelationships'"));
    if(AbilityTagRelationshipObj.Succeeded())
    {
        AbilityTagRelationship = AbilityTagRelationshipObj.Object;
    }

    static ConstructorHelpers::FObjectFinder<UXIJobTagRelationship> JobTagRelationshipObj(TEXT("XIJobTagRelationship'/Game/XIRemix/Core/DataAssets/DA_XIJobTagRelationships.DA_XIJobTagRelationships'"));
    if(JobTagRelationshipObj.Succeeded())
    {
        JobTagRelationship = JobTagRelationshipObj.Object;
    }
}

void UXIAbilitySystemComponent::GetRelationshipActivationTagRequirements(const FGameplayTagContainer& AbilityTags, FGameplayTagContainer& OutActivationRequired, FGameplayTagContainer& OutActivationBlocked) const
{
    if (AbilityTagRelationship)
    {
        AbilityTagRelationship->GetActivationRequiredAndBlockedTags(AbilityTags, &OutActivationRequired, &OutActivationBlocked);
    }
}
 
void UXIAbilitySystemComponent::ApplyAbilityBlockAndCancelTags(const FGameplayTagContainer& AbilityTags, UGameplayAbility* RequestingAbility, bool bEnableBlockTags, const FGameplayTagContainer& BlockTags, bool bExecuteCancelTags,
    const FGameplayTagContainer& CancelTags)
{
    FGameplayTagContainer AbilityBlockTags = BlockTags;
    FGameplayTagContainer AbilityCancelTags = CancelTags;
     
    if (AbilityTagRelationship)
    {
        AbilityTagRelationship->GetAbilityTagsToBlockAndCancel(AbilityTags, &AbilityBlockTags, &AbilityCancelTags);
    }
 
    Super::ApplyAbilityBlockAndCancelTags(AbilityTags, RequestingAbility, bEnableBlockTags, AbilityBlockTags, bExecuteCancelTags, AbilityCancelTags);
}

void UXIAbilitySystemComponent::LevelUp()
{
    OnLevelUp.Broadcast();
}

void UXIAbilitySystemComponent::GetXIJobTagRelationship(const FGameplayTag JobTag, FXIJobTagRelationshipItem& JobTagRelationshipItem) const
{
    if(!JobTagRelationship)
    {
        return;
    }

    JobTagRelationship->GetXIJobTagRelationship(JobTag, JobTagRelationshipItem);
}

void UXIAbilitySystemComponent::ExecuteGameplayCueLocal(const FGameplayTag GameplayCueTag, const FGameplayCueParameters & GameplayCueParameters)
{
	UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(GetOwner(), GameplayCueTag, EGameplayCueEvent::Type::Executed, GameplayCueParameters);
}

void UXIAbilitySystemComponent::AddGameplayCueLocal(const FGameplayTag GameplayCueTag, const FGameplayCueParameters & GameplayCueParameters)
{
	UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(GetOwner(), GameplayCueTag, EGameplayCueEvent::Type::OnActive, GameplayCueParameters);
	UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(GetOwner(), GameplayCueTag, EGameplayCueEvent::Type::WhileActive, GameplayCueParameters);
}

void UXIAbilitySystemComponent::RemoveGameplayCueLocal(const FGameplayTag GameplayCueTag, const FGameplayCueParameters & GameplayCueParameters)
{
	UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(GetOwner(), GameplayCueTag, EGameplayCueEvent::Type::Removed, GameplayCueParameters);
}

void UXIAbilitySystemComponent::XICycleTarget(float Direction)
{
    OnXICycleTarget.Broadcast(Direction);
}
void UXIAbilitySystemComponent::XIStartAbilityTargeting()
{
    OnXIStartAbilityTargeting.Broadcast();
}
void UXIAbilitySystemComponent::XIEndAbilityTargeting()
{
    OnXIEndAbilityTargeting.Broadcast();
}