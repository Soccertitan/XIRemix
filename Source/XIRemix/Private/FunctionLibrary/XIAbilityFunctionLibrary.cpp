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