// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "XIEnums.h"
#include "GameplayTagContainer.h"
#include "XICharacterAnimMontages.generated.h"

/*
 * Maps a combat style to it's animation montages.
 */
USTRUCT(BlueprintType)
struct FCharacterCombatMontages
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECombatStyle CombatStyle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* StartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* ExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray <UAnimMontage*> BasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* AtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* AtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* AtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* AtkRight;
};

// Maps a Gameplay Tag to a ranged anim montage
USTRUCT(BlueprintType)
struct FCharacterRangedMontages
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories="Weapon.Ranged"))
	FGameplayTag RangedWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* AnimMontage;
};

// Maps a magic type to an anim montage
USTRUCT(BlueprintType)
struct FCharacterMagicMontages
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXIMagicType MagicType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* AnimMontage;
};

/**
 * 
 */
UCLASS(BlueprintType)
class XIREMIX_API UXICharacterAnimMontages : public UDataAsset
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "XICharacterMontages")
	UAnimMontage* GetAutoAttackMontage(ECombatStyle CombatStyle, float Speed, float Direction) const;

	UFUNCTION(BlueprintPure, Category = "XICharacterMontages")
	UAnimMontage* GetCombatStartMontage(ECombatStyle CombatStyle) const;

	UFUNCTION(BlueprintPure, Category = "XICharacterMontages")
	UAnimMontage* GetCombatExitMontage(ECombatStyle CombatStyle) const;

	UFUNCTION(BlueprintPure, Category = "XICharacterMontages")
	UAnimMontage* GetRangedMontage(FGameplayTag RangedWeapon) const;

	UFUNCTION(BlueprintPure, Category = "XICharacterMontages")
	UAnimMontage* GetMagicMontage(EXIMagicType MagicType) const;

	UFUNCTION(BlueprintPure, Category = "XICharacterMontages")
	UAnimMontage* GetJobAbilityMontage(bool bIsWeaponOut) const;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FCharacterCombatMontages> CombatMontages;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FCharacterRangedMontages> RangedMontages;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FCharacterMagicMontages> MagicMontages;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* JobAbility;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* JobAbilityCombat;
};
