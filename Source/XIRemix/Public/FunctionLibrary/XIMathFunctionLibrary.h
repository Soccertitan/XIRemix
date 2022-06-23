// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTags.h"
#include "XIMathFunctionLibrary.generated.h"

/**
 * A class defining resuable functions for calculating damage and retrieving specific attributes.
 */
UCLASS()
class XIREMIX_API UXIMathFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// The Damage bonus/penalty from the source Strength subtracted from targets Vitality. With bounds of that value set by Weapon damage.
	UFUNCTION(BlueprintPure, Category = "XIMathFunctionLibrary")
	static float fSTRMelee(float STR, float VIT, float WeaponDamage, bool bIsHandToHand);

	// The Damage bonus/penalty from the source Strength subtracted from targets Vitality. With bounds of that value set by Weapon damage.
	UFUNCTION(BlueprintPure, Category = "XIMathFunctionLibrary")
	static float fSTRRange(float STR, float VIT, float WeaponDamage);

	// The ratio of Attack/Defense affected by the difference level between the Target's Level - Attacker's level.
	UFUNCTION(BlueprintPure, Category = "XIMathFunctionLibrary")
	static float pDIF(float Attack, float Defense, float LevelDif, float CritChance, float CritBonus, FGameplayTag WeaponType, bool bIsMonster, bool& OutbIsCriticalHit);

	// The percent chance to hit a target with an attack. Which is further affected by the Targets Level - Attackers Level.
	// Returns a value between 0.2 and 0.95.
	UFUNCTION(BlueprintPure, Category = "XIMathFunctionLibrary")
	static float HitRate(float Accuracy, float Evasion, float LevelDif);

	UFUNCTION(BlueprintPure, Category = "XIMathFunctionLibrary")
	static float TPGained(float Delay);

protected:

	static const FGameplayTag Axe; 
	static const FGameplayTag Club;
	static const FGameplayTag Dagger;
	static const FGameplayTag GreatAxe;
	static const FGameplayTag GreatKatana;
	static const FGameplayTag HandToHand;
	static const FGameplayTag Katana;
	static const FGameplayTag Polearm;
	static const FGameplayTag Scythe;
	static const FGameplayTag Staff;
	static const FGameplayTag Sword;

	static const FGameplayTag Archery;
	static const FGameplayTag Marksmanship;
	static const FGameplayTag Throwing;
};
