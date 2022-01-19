// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "XIAT_SingleTargetActor.generated.h"

USTRUCT(BlueprintType)
struct FGameplayAbilityMeleeTarget : public FGameplayAbilityTargetData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Targeting")
	AActor* TargetActor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Targeting")
	UAnimMontage* AttackMontage;

	// /** The ID of the Ability that is performing targeting */
    UPROPERTY()
    uint32 UniqueID;

	 // -------------------------------------
    virtual UScriptStruct* GetScriptStruct() const override
    {
        return FGameplayAbilityMeleeTarget::StaticStruct();
    }

    virtual FString ToString() const override
    {
        return TEXT("FGameplayAbilityMeleeTarget");
    }

    // bool NetSerialize(FArchive&amp; Ar, class UPackageMap* Map, bool&amp; bOutSuccess);
	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

};

template<>
struct TStructOpsTypeTraits<FGameplayAbilityMeleeTarget> : public TStructOpsTypeTraitsBase2<FGameplayAbilityMeleeTarget>
{
    enum
    {
        WithNetSerializer = true    // For now this is REQUIRED for FGameplayAbilityTargetDataHandle net serialization to work
    };
};

/**
 * 
 */
UCLASS()
class XIREMIX_API AXIAT_SingleTargetActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:
	AXIAT_SingleTargetActor();

	virtual void StartTargeting(UGameplayAbility* Ability) override;

	virtual void ConfirmTargetingAndContinue() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Trace")
	float MaxRange;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Trace")
	float Angle;
};
