// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "XIEnums.h"
#include "XICombatSkillsRank.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXICombatSkillsRank : public UDataAsset
{
	GENERATED_BODY()
	
public:

	// Melee Weapon Skills
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Melee")
	EXISkillRank Axe = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Melee")
	EXISkillRank GreatAxe = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Melee")
	EXISkillRank Club = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Melee")
	EXISkillRank Dagger = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Melee")
	EXISkillRank HandToHand = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Melee")
	EXISkillRank Katana = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Melee")
	EXISkillRank GreatKatana = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Melee")
	EXISkillRank Polearm = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Melee")
	EXISkillRank Scythe = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Melee")
	EXISkillRank Staff = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Melee")
	EXISkillRank Sword = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Melee")
	EXISkillRank GreatSword = EXISkillRank::H;

	// Ranged Weapon Skills
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ranged")
	EXISkillRank Archery = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ranged")
	EXISkillRank Marksmanship = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ranged")
	EXISkillRank Throwing = EXISkillRank::H;

	// Defensive skills
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defensive")
	EXISkillRank Evasion = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defensive")
	EXISkillRank Guarding = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defensive")
	EXISkillRank Parrying = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defensive")
	EXISkillRank Shield = EXISkillRank::H;

	//Magic and Music Skills
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Special")
	EXISkillRank Blue = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Special")
	EXISkillRank Dark = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Special")
	EXISkillRank Divine = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Special")
	EXISkillRank Elemental = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Special")
	EXISkillRank Enfeebling = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Special")
	EXISkillRank Enhancing = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Special")
	EXISkillRank Healing = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Special")
	EXISkillRank Summoning = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Special")
	EXISkillRank Ninjutsu = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Special")
	EXISkillRank Singing = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Special")
	EXISkillRank String = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Special")
	EXISkillRank Wind = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Special")
	EXISkillRank Geomancy = EXISkillRank::H;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Special")
	EXISkillRank Handbell = EXISkillRank::H;
};
