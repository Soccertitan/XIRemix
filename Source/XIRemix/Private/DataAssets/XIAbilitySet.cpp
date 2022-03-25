// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/XIAbilitySet.h"
#include "Abilities/XIGameplayAbility.h"
#include "Abilities/XIAbilitySystemComponent.h"

void FXIAbilitySetHandle::AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle)
{
    if (Handle.IsValid())
    {
        AbilitySpecHandles.Add(Handle);
    }
}
 
void FXIAbilitySetHandle::AddGameplayEffectHandle(const FActiveGameplayEffectHandle& Handle)
{
    if (Handle.IsValid())
    {
        GameplayEffectHandles.Add(Handle);
    }
}
 
namespace XIAbilitySetHandle_Impl
{
    static int32 LastHandleId = 0;
    static int32 GetNextQueuedHandleIdForUse() { return ++LastHandleId; }
}
 
UXIAbilitySet::UXIAbilitySet(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}
 
FXIAbilitySetHandle UXIAbilitySet::GiveAbilitySetTo(UXIAbilitySystemComponent* ASC, UObject* OverrideSourceObject) const
{
    check(ASC);
 
    if (!ASC->IsOwnerActorAuthoritative())
    {
        // Must be authoritative to give or take ability sets.
        return FXIAbilitySetHandle();
    }
 
    FXIAbilitySetHandle OutHandle;
    OutHandle.HandleId = XIAbilitySetHandle_Impl::GetNextQueuedHandleIdForUse();
    OutHandle.AbilitySystemComponent = ASC;
 
    // Grant the gameplay abilities.
    for (int32 AbilityIndex = 0; AbilityIndex < GrantedGameplayAbilities.Num(); ++AbilityIndex)
    {
        const FXIAbilitySet_GameplayAbility& AbilityToGrant = GrantedGameplayAbilities[AbilityIndex];
 
        if (!IsValid(AbilityToGrant.Ability))
        {
            UE_LOG(LogTemp, Error, TEXT("GrantedGameplayAbilities[%d] on ability set [%s] is not valid."), AbilityIndex, *GetNameSafe(this));
            continue;
        }
 
        UXIGameplayAbility* AbilityCDO = AbilityToGrant.Ability->GetDefaultObject<UXIGameplayAbility>();
 
        FGameplayAbilitySpec AbilitySpec(AbilityCDO, AbilityToGrant.AbilityLevel);
        AbilitySpec.SourceObject = OverrideSourceObject;
 
 
        const FGameplayAbilitySpecHandle AbilitySpecHandle = ASC->GiveAbility(AbilitySpec);
        OutHandle.AddAbilitySpecHandle(AbilitySpecHandle);
    }
 
    // Grant the gameplay effects.
    for (int32 EffectIndex = 0; EffectIndex < GrantedGameplayEffects.Num(); ++EffectIndex)
    {
        const FXIAbilitySet_GameplayEffect& EffectToGrant = GrantedGameplayEffects[EffectIndex];
 
        if (!IsValid(EffectToGrant.GameplayEffect))
        {
            UE_LOG(LogTemp, Error, TEXT("GrantedGameplayEffects[%d] on ability set [%s] is not valid"), EffectIndex, *GetNameSafe(this));
            continue;
        }
 
        const UGameplayEffect* GameplayEffect = EffectToGrant.GameplayEffect->GetDefaultObject<UGameplayEffect>();
        const FActiveGameplayEffectHandle GameplayEffectHandle = ASC->ApplyGameplayEffectToSelf(GameplayEffect, EffectToGrant.EffectLevel, ASC->MakeEffectContext());
        OutHandle.AddGameplayEffectHandle(GameplayEffectHandle);
    }
 
 
 
    return OutHandle;
}
 
FXIAbilitySetHandle UXIAbilitySet::GiveAbilitySetToInterface(TScriptInterface<IAbilitySystemInterface> AbilitySystemInterface, UObject* OverrideSourceObject) const
{
    UXIAbilitySystemComponent* XIASC = Cast<UXIAbilitySystemComponent>(AbilitySystemInterface.GetObject());
    return GiveAbilitySetTo(XIASC, OverrideSourceObject);
}
 
void UXIAbilitySet::TakeAbilitySet(FXIAbilitySetHandle& AbilitySetHandle)
{
    if (!AbilitySetHandle.IsValid())
    {
        return;
    }
     
    if (!AbilitySetHandle.AbilitySystemComponent->IsOwnerActorAuthoritative())
    {
        // Must be authoritative to give or take ability sets.
        return;
    }
 
    for (const FGameplayAbilitySpecHandle& Handle : AbilitySetHandle.AbilitySpecHandles)
    {
        if (Handle.IsValid())
        {
            AbilitySetHandle.AbilitySystemComponent->ClearAbility(Handle);
        }
    }
 
    for (const FActiveGameplayEffectHandle& Handle : AbilitySetHandle.GameplayEffectHandles)
    {
        if (Handle.IsValid())
        {
            AbilitySetHandle.AbilitySystemComponent->RemoveActiveGameplayEffect(Handle);
        }
    }
 
    AbilitySetHandle.Reset();
}