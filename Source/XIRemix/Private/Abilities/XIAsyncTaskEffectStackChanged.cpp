// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/XIAsyncTaskEffectStackChanged.h"

UXIAsyncTaskEffectStackChanged * UXIAsyncTaskEffectStackChanged::ListenForGameplayEffectStackChange(UAbilitySystemComponent * AbilitySystemComponent, FGameplayTag InEffectGameplayTag)
{
	UXIAsyncTaskEffectStackChanged* ListenForGameplayEffectStackChange = NewObject<UXIAsyncTaskEffectStackChanged>();
	ListenForGameplayEffectStackChange->ASC = AbilitySystemComponent;
	ListenForGameplayEffectStackChange->EffectGameplayTag = InEffectGameplayTag;

	if (!IsValid(AbilitySystemComponent) || !InEffectGameplayTag.IsValid())
	{
		ListenForGameplayEffectStackChange->EndTask();
		return nullptr;
	}

	AbilitySystemComponent->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(ListenForGameplayEffectStackChange, &UXIAsyncTaskEffectStackChanged::OnActiveGameplayEffectAddedCallback);
	AbilitySystemComponent->OnAnyGameplayEffectRemovedDelegate().AddUObject(ListenForGameplayEffectStackChange, &UXIAsyncTaskEffectStackChanged::OnRemoveGameplayEffectCallback);

	return ListenForGameplayEffectStackChange;
}

void UXIAsyncTaskEffectStackChanged::EndTask()
{
	if (IsValid(ASC))
	{
		ASC->OnActiveGameplayEffectAddedDelegateToSelf.RemoveAll(this);
		ASC->OnAnyGameplayEffectRemovedDelegate().RemoveAll(this);
	}

	SetReadyToDestroy();
	MarkPendingKill();
}

void UXIAsyncTaskEffectStackChanged::OnActiveGameplayEffectAddedCallback(UAbilitySystemComponent * Target, const FGameplayEffectSpec & SpecApplied, FActiveGameplayEffectHandle ActiveHandle)
{
	FGameplayTagContainer AssetTags;
	SpecApplied.GetAllAssetTags(AssetTags);

	FGameplayTagContainer GrantedTags;
	SpecApplied.GetAllGrantedTags(GrantedTags);

	if (AssetTags.HasTagExact(EffectGameplayTag) || GrantedTags.HasTagExact(EffectGameplayTag))
	{
		ASC->OnGameplayEffectStackChangeDelegate(ActiveHandle)->AddUObject(this, &UXIAsyncTaskEffectStackChanged::GameplayEffectStackChanged);
		OnGameplayEffectStackChange.Broadcast(EffectGameplayTag, ActiveHandle, 1, 0);
	}
}

void UXIAsyncTaskEffectStackChanged::OnRemoveGameplayEffectCallback(const FActiveGameplayEffect & EffectRemoved)
{
	FGameplayTagContainer AssetTags;
	EffectRemoved.Spec.GetAllAssetTags(AssetTags);

	FGameplayTagContainer GrantedTags;
	EffectRemoved.Spec.GetAllGrantedTags(GrantedTags);

	if (AssetTags.HasTagExact(EffectGameplayTag) || GrantedTags.HasTagExact(EffectGameplayTag))
	{
		OnGameplayEffectStackChange.Broadcast(EffectGameplayTag, EffectRemoved.Handle, 0, 1);
	}
}

void UXIAsyncTaskEffectStackChanged::GameplayEffectStackChanged(FActiveGameplayEffectHandle EffectHandle, int32 NewStackCount, int32 PreviousStackCount)
{
	OnGameplayEffectStackChange.Broadcast(EffectGameplayTag, EffectHandle, NewStackCount, PreviousStackCount);
}