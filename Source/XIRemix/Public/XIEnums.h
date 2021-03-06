// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XIEnums.generated.h"

UENUM(BlueprintType)
enum class EXIAbilityInputID : uint8
{
	// 0 None
	None			UMETA(DisplayName = "None"),
	// 1 Confirm
	Confirm			UMETA(DisplayName = "Confirm"),
	// 2 Cancel
	Cancel			UMETA(DisplayName = "Cancel"),
};

UENUM(BlueprintType, Category="XIRemix")
enum class ECombatStyle : uint8
{
	Battle1 UMETA(DisplayName = "Axe/Club"),
	Battle2 UMETA(DisplayName = "Sword"),
	Battle3 UMETA(DisplayName = "Hand2Hand"),
	Battle4 UMETA(DisplayName = "Dagger"),
	Battle5 UMETA(DisplayName = "GreatSword"),
	Battle6 UMETA(DisplayName = "GreatAxe/Scythe/Staff"),
	Battle7 UMETA(DisplayName = "GreatKatana"),
	Battle8 UMETA(DisplayName = "Polearm"),
	Battle9 UMETA(DisplayName = "Unarmed"),
	Battle10 UMETA(DisplayName = "Katana")
};

UENUM(BlueprintType, Category="XIRemix")
enum class EEquipSlot : uint8
{
	MainHand UMETA(DisplayName = "MainHand"),
	SubHand UMETA(DisplayName = "SubHand"),
	Ranged UMETA(DisplayName = "Ranged"),
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
	Shield UMETA(DisplayName = "Shield"),
	Instrument UMETA(DisplayName = "Instrument"),
	Ammo UMETA(DisplayName = "Ammo"),
	Armor UMETA(DisplayName = "Armor"),
	Accessory UMETA(DisplayName = "Accessory"),
	Consumable UMETA(DisplayName = "Consumable"),
	Material UMETA(Displayname = "Material"),
	KeyItem UMETA(DisplayName = "KeyItem")
};

UENUM(BlueprintType, Category="XIRemix")
enum class EInventoryType : uint8
{
	Melee UMETA(DisplayName = "Melee"),
	Ranged UMETA(DisplayName = "Ranged"),
	Armor UMETA(DisplayName = "Armor"),
	Accessory UMETA(DisplayName = "Accessory"),
	Consumable UMETA(DisplayName = "Consumable"),
	Material UMETA(DisplayName = "Material"),
	Ability UMETA(DisplayName = "Ability"),
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
enum class ESkeletalMeshMergeType : uint8
{
	Face UMETA(DisplayName = "Face"),
	Head UMETA(DisplayName = "Head"),
	Body UMETA(DisplayName = "Body"),
	Hands UMETA(DisplayName = "Hands"),
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

UENUM(BlueprintType, Category="XIRemix")
enum class EXISkillRank : uint8
{
	APlus UMETA(DisplayName = "APlus"),
	A UMETA(DisplayName = "A"),
	AMinus UMETA(DisplayName = "AMinus"),
	BPlus UMETA(DisplayName = "BPlus"),
	B UMETA(DisplayName = "B"),
	BMinus UMETA(DisplayName = "BMinus"),
	CPlus UMETA(DisplayName = "CPlus"),
	C UMETA(DisplayName = "C"),
	CMinus UMETA(DisplayName = "CMinus"),
	D UMETA (DisplayName = "D"),
	E UMETA (DisplayName = "E"),
	F UMETA (DisplayName = "F"),
	G UMETA (DisplayName = "G"),
	H UMETA (DisplayName = "H")
};

UENUM(BlueprintType, Category="XIRemix")
enum class EXISheatheStyle : uint8
{
	A UMETA(DisplayName = "A"),
	B UMETA(DisplayName = "B"),
	C UMETA(DisplayName = "C"),
	D UMETA (DisplayName = "D"),
	E UMETA (DisplayName = "E"),
	F UMETA (DisplayName = "F"),
	G UMETA (DisplayName = "G"),
	H UMETA (DisplayName = "H"),
	I UMETA (DisplayName = "I"),
	J UMETA (DisplayName = "J"),
	K UMETA (DisplayName = "K"),
	L UMETA (DisplayName = "L")
};