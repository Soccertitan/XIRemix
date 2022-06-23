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

USTRUCT(BlueprintType)
struct XIREMIX_API FXIGameplayEffectContext : public FGameplayEffectContext
{
    GENERATED_BODY()

public:
    bool IsCriticalHit() const { return bIsCriticalHit; }
    bool IsBlocked() const { return bIsBlocked; }
    bool IsParried() const { return bIsParried; }
    bool IsGuarded() const { return bIsGuarded; }
    bool IsEvaded() const { return bIsEvaded; }
    bool IsResisted() const { return bIsResisted; }
 
    void SetIsCriticalHit(bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
    void SetIsBlocked(bool bInIsBlocked) { bIsBlocked = bInIsBlocked; }
    void SetIsParried(bool bInIsParried) { bIsParried = bInIsParried; }
    void SetIsGuarded(bool bInIsGuarded) { bIsGuarded = bInIsGuarded; }
    void SetIsEvaded(bool bInIsEvaded) { bIsEvaded = bInIsEvaded; }
    void SetIsResisted(bool bInIsResisted) { bIsResisted = bInIsResisted; }
 
protected:
 
    UPROPERTY()
    bool bIsCriticalHit;

    UPROPERTY()
    bool bIsBlocked;

    UPROPERTY()
    bool bIsParried;

    UPROPERTY()
    bool bIsGuarded;

    UPROPERTY()
    bool bIsEvaded;

    UPROPERTY()
    bool bIsResisted;
 
public:
    /** Returns the actual struct used for serialization, subclasses must override this! */
    virtual UScriptStruct* GetScriptStruct() const override
    {
        return StaticStruct();
    }
 
    /** Creates a copy of this context, used to duplicate for later modifications */
    virtual FXIGameplayEffectContext* Duplicate() const override
    {
        FXIGameplayEffectContext* NewContext = new FXIGameplayEffectContext();
        *NewContext = *this;
        NewContext->AddActors(Actors);
        if (GetHitResult())
        {
            // Does a deep copy of the hit result
            NewContext->AddHitResult(*GetHitResult(), true);
        }
        return NewContext;
    }
 
    virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;
};
 
template <>
struct TStructOpsTypeTraits<FXIGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FXIGameplayEffectContext>
{
    enum
    {
        WithNetSerializer = true,
        WithCopy = true // Necessary so that TSharedPtr<FHitResult> Data is copied around
    };
};