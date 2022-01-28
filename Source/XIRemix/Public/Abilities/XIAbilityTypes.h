// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "XIAbilityTypes.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct XIREMIX_API FGameplayAbilitySingleTargetData : public FGameplayAbilityTargetData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Targeting")
	AActor* TargetActor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Targeting")
	UAnimMontage* AttackMontage;

	// /** The ID of the Ability that is performing targeting */
    UPROPERTY()
    uint32 UniqueID;

	
    virtual UScriptStruct* GetScriptStruct() const override
    {
        return FGameplayAbilitySingleTargetData::StaticStruct();
    }

    virtual FString ToString() const override
    {
        return TEXT("FGameplayAbilitySingleTargetData");
    }

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

};

template<>
struct TStructOpsTypeTraits<FGameplayAbilitySingleTargetData> : public TStructOpsTypeTraitsBase2<FGameplayAbilitySingleTargetData>
{
    enum
    {
        WithNetSerializer = true    // For now this is REQUIRED for FGameplayAbilityTargetDataHandle net serialization to work
    };
};