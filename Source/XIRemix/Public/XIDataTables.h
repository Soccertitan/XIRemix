// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "XIEnums.h"
#include "XIDataTables.generated.h"

USTRUCT(BlueprintType)
struct FXIAbilityData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BasePower;

	// The length an ability persits
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Cooldown;

	// if bAreaEffect = true affect all targets within the radius of AreaEffectRange
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bAreaEffect;

	// The radius of the area of effect centered on the target.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AreaEffectRange;

	// if bFixedEnmity = true use CumlativeEnmity and VolatileEnmity values
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bFixedEnmity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CumulativeEnmity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float VolatileEnmity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Description;
};

USTRUCT(BlueprintType)
struct FXIJobSkillRankData : public FTableRowBase
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag Job;

	// Melee Weapon Skills
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Axe = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank GreatAxe = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Club = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Dagger = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank HandToHand = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Katana = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank GreatKatana = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Polearm = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Scythe = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Staff = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Sword = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank GreatSword = EXISkillRank::H;

	// Ranged Weapon Skills
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Archery = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Marksmanship = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Throwing = EXISkillRank::H;

	// Defensive skills
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Evasion = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Guarding = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Parrying = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Shield = EXISkillRank::H;

	//Magic and Music Skills
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Blue = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Dark = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Divine = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Elemental = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Enfeebling = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Enhancing = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Healing = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Summoning = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Ninjutsu = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Singing = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank String = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Wind = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Geomancy = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Handbell = EXISkillRank::H;
};

USTRUCT(BlueprintType)
struct FXIStatGrowthRankData : public FTableRowBase
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank HitPoints = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank ManaPoints = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Strength = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Dexterity = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Vitality = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Agility = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Intelligence = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Mind = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank Charisma = EXISkillRank::H;
};

USTRUCT(BlueprintType)
struct FXIStatGrowthData : public FTableRowBase
{
	
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EXISkillRank StatGrowthRank = EXISkillRank::H;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HitPointsScale;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HitPointsBase;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HitPointsMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ManaPointsScale;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ManaPointsBase;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttributeScale;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttributeBase;
};