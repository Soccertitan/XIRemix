// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/XIAbilityFunctionLibrary.h"

const FGameplayAbilitySingleTargetData& UXIAbilityFunctionLibrary::GetGameplayAbilitySingleTargetData(const FGameplayAbilityTargetDataHandle& TargetData, int32 Index)
{
    if (TargetData.Data.IsValidIndex(Index))
    {
        FGameplayAbilitySingleTargetData* Data = static_cast<FGameplayAbilitySingleTargetData*>(TargetData.Data[Index].Get());
        if (Data)
        {
            return *Data;
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("%s() Valid Data Not Found, ArraySize:%d, returning empty struct"), *FString(__FUNCTION__), TargetData.Data.Num());
    
    static FGameplayAbilitySingleTargetData dummy;
    return dummy;
}

bool UXIAbilityFunctionLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContext)
{
    const FXIGameplayEffectContext* XIEffectContext = static_cast<const FXIGameplayEffectContext*>(EffectContext.Get());
    if (XIEffectContext)
    {
        return XIEffectContext->IsCriticalHit();
    }
    return false;
}

bool UXIAbilityFunctionLibrary::IsBlocked(const FGameplayEffectContextHandle& EffectContext)
{
    const FXIGameplayEffectContext* XIEffectContext = static_cast<const FXIGameplayEffectContext*>(EffectContext.Get());
    if (XIEffectContext)
    {
        return XIEffectContext->IsBlocked();
    }
    return false;
}

bool UXIAbilityFunctionLibrary::IsParried(const FGameplayEffectContextHandle& EffectContext)
{
    const FXIGameplayEffectContext* XIEffectContext = static_cast<const FXIGameplayEffectContext*>(EffectContext.Get());
    if (XIEffectContext)
    {
        return XIEffectContext->IsParried();
    }
    return false;
}

bool UXIAbilityFunctionLibrary::IsGuarded(const FGameplayEffectContextHandle& EffectContext)
{
    const FXIGameplayEffectContext* XIEffectContext = static_cast<const FXIGameplayEffectContext*>(EffectContext.Get());
    if (XIEffectContext)
    {
        return XIEffectContext->IsGuarded();
    }
    return false;
}

bool UXIAbilityFunctionLibrary::IsEvaded(const FGameplayEffectContextHandle& EffectContext)
{
    const FXIGameplayEffectContext* XIEffectContext = static_cast<const FXIGameplayEffectContext*>(EffectContext.Get());
    if (XIEffectContext)
    {
        return XIEffectContext->IsEvaded();
    }
    return false;
}

bool UXIAbilityFunctionLibrary::IsResisted(const FGameplayEffectContextHandle& EffectContext)
{
    const FXIGameplayEffectContext* XIEffectContext = static_cast<const FXIGameplayEffectContext*>(EffectContext.Get());
    if (XIEffectContext)
    {
        return XIEffectContext->IsResisted();
    }
    return false;
}