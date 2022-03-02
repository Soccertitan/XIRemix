// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XIEnums.generated.h"

UENUM(BlueprintType, Category="XIRemix")
enum class ECombatStyle : uint8
{
	Unarmed UMETA(DisplayName = "Unarmed"),
	Sword UMETA(DisplayName = "Sword"),
	Axe UMETA(DisplayName = "Axe"),
	Dagger UMETA(DisplayName = "Dagger"),
	Club UMETA(DisplayName = "Club"),
	Katana UMETA(DisplayName = "Katana"),
	Hand2Hand UMETA(DisplayName = "Hand2Hand"),
	GreatSword UMETA(DisplayName = "GreatSword"),
	GreatKatana UMETA(DisplayName = "GreatKatana"),
	TwoHanded UMETA(DisplayName = "TwoHanded")
};

UENUM(BlueprintType, Category="XIRemix")
enum class EEquipSlot : uint8
{
	MainHand UMETA(DisplayName = "MainHand"),
	SubHand UMETA(DisplayName = "SubHand"),
	Range UMETA(DisplayName = "Range"),
	Ammo UMETA(DisplayName = "Ammo"),
	Head UMETA(DisplayName = "Head"),
	Neck UMETA(DisplayName = "Neck"),
	Ear1 UMETA(DisplayName = "Ear1"),
	Ear2 UMETA(DisplayName = "Ear2"),
	Body UMETA(DisplayName = "Body"),
	Hands UMETA(DisplayName = "Hands"),
	Ring1 UMETA(DisplayName = "Ring1"),
	Ring2 UMETA(DisplayName = "Ring2"),
	Back UMETA(DisplayName = "Back"),
	Waist UMETA(DisplayName = "Waist"),
	Legs UMETA(DisplayName = "Legs"),
	Feet UMETA(DisplayName = "Feet")
};

UENUM(BlueprintType, Category="XIRemix")
enum class EItemType : uint8
{
	WeaponMelee UMETA(DisplayName = "WeaponMelee"),
	WeaponRange UMETA(DisplayName = "WeaponRange"),
	Instrument UMETA(DisplayName = "Instrument"),
	Ammo UMETA(DisplayName = "Ammo"),
	Armor UMETA(DisplayName = "Armor"),
	Accessory UMETA(DisplayName = "Accessory"),
	Consumable UMETA(DisplayName = "Consumable"),
	Material UMETA(Displayname = "Material"),
	KeyItem UMETA(DisplayName = "KeyItem")
};

UENUM(BlueprintType, Category="XIRemix")
enum class ERace : uint8
{
	HumeMale UMETA(DisplayName = "HumeMale"),
	HumeFemale UMETA(DisplayName = "HumeFemale"),
	ElvaanMale UMETA(DisplayName = "ElvaanMale"),
	ElvaanFemale UMETA(DisplayName = "ElvaanFemale"),
	Tarutaru UMETA(DisplayName = "Tarutaru"),
	Galka UMETA(DisplayName = "Galka"),
	Mithra UMETA(DisplayName = "Mithra"),
	AllRaces UMETA(DisplayName = "AllRaces")
};

UENUM(BlueprintType, Category="XIRemix")
enum class EWeaponType : uint8
{
	Hand UMETA(DisplayName = "Hand"),
	Dagger UMETA(DisplayName = "Dagger"),
	Sword UMETA(DisplayName = "Sword"),
	GreatSword UMETA(DisplayName = "GreatSword"),
	Axe UMETA(DisplayName = "Axe"),
	GreatAxe UMETA(DisplayName = "GreatAxe"),
	Scythe UMETA(DisplayName = "Scythe"),
	Polearm UMETA(DisplayName = "Polearm"),
	Katana UMETA(DisplayName = "Katana"),
	GreatKatana UMETA(DisplayName = "GreatKatana"),
	Club UMETA(DisplayName = "Club"),
	Staff UMETA(DisplayName = "Staff"),
	Shield UMETA(DisplayName = "Shield"),
	Throwing UMETA(DisplayName = "Throwing"),
	Archery UMETA(DisplayName = "Archery"),
	Gun UMETA(DisplayName = "Gun"),
	Wind UMETA(DisplayName = "Wind"),
	String UMETA(DisplayName = "String"),
	Bell UMETA(DisplayName = "Bell")
};

UENUM(BlueprintType, Category="XIRemix")
enum class ESkeletalMeshMergeType : uint8
{
	Face UMETA(DisplayName = "Face"),
	Head UMETA(DisplayName = "Head"),
	Body UMETA(DisplayName = "Body"),
	Arms UMETA(DisplayName = "Arms"),
	Legs UMETA(DisplayName = "Legs"),
	Feet UMETA(DisplayName = "Feet"),
	MainHand UMETA(DisplayName = "MainHand"),
	SubHand UMETA(DisplayName = "SubHand"),
	Range UMETA(DisplayName = "Range")
};

UENUM(BlueprintType, Category="XITeams")
enum class EXITeam : uint8
{
	Neutral UMETA(DisplayName = "Neutral"),
	Enemy UMETA(DisplayName = "Enemy"),
	Hero UMETA(DisplayName = "Hero")
};

UENUM(BlueprintType, Category="XITeams")
enum class EXITeamAttitude : uint8
{
	Neutral UMETA(DisplayName = "Neutral"),
	Hostile UMETA(DisplayName = "Hostile"),
	Friendly UMETA(DisplayName = "Friendly")
};

UENUM(BlueprintType, Category="XIRemix")
enum class EXIAggroType : uint8
{
	Passive UMETA(DisplayName = "Passive"),
	Sight UMETA(DisplayName = "Sight"),
	Sound UMETA(DisplayName = "Sound"),
	Smell UMETA(DisplayName = "Smell"),
	TrueSense UMETA(DisplayName = "TrueSense")
};

UENUM(BlueprintType, Category="XIRemix")
enum class EXIMagicType : uint8
{
	Black UMETA(DisplayName = "Black"),
	Blue UMETA(DisplayName = "Blue"),
	Geomancy UMETA(DisplayName = "Geomancy"),
	HandBell UMETA(DisplayName = "HandBell"),
	Ninjitsu UMETA(DisplayName = "Ninjitsu"),
	Summoner UMETA(DisplayName = "Summoner"),
	White UMETA(DisplayName = "White")
};