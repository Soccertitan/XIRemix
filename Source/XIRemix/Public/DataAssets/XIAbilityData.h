// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "XIEnums.h"
#include "XIAbilityData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class XIREMIX_API UXIAbilityData : public UDataAsset
{
	GENERATED_BODY()

public:

	// The class reference for this ability data.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UXIGameplayAbility> Ability;

	// The Gameplay Effect Class
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UGameplayEffect> GameplayEffect;

	// Actors attitude towards the main target.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXITeamAttitude TargetAttiude;

	// The base power of the ability.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Potency;

	// The length an ability's effect persits
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Duration;

	// The range of the ability to target.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Range;

	// The angle for Line of sight. 180 degrees is equal to 180 degrees to the right and left = 360 degrees.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Angle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CastTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Cost;

	// Tells an ability to activate immediately when its granted. Used for passive abilities and abilities forced on others.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bPassiveAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cooldown")
	float Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cooldown")
	FGameplayTagContainer CooldownTags;

	// if bAreaEffect = true affect all targets within the radius of AreaEffectRange
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Area of Effect")
	bool bAreaEffect;

	// The radius of the area of effect centered on the target.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Area of Effect")
	float AreaEffectRange;

	// if bFixedEnmity = true use CumlativeEnmity and VolatileEnmity values
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enmity")
	bool bFixedEnmity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enmity")
	float CumulativeEnmity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enmity")
	float VolatileEnmity;
};
