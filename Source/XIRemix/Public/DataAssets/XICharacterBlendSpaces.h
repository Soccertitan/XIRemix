// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "XIEnums.h"
#include "XICharacterBlendSpaces.generated.h"


/*
 * Maps a combat style to it's blend space.
 */
USTRUCT(BlueprintType)
struct FCharacterBlendSpace
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECombatStyle CombatStyle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBlendSpace* UpperBody;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBlendSpace* LowerBody;
};

/**
 * 
 */
UCLASS()
class XIREMIX_API UXICharacterBlendSpaces : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBlendSpace* NonCombatUpperBody;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBlendSpace* NonCombatLowerBody;

	void GetCombatBlendSpace(UBlendSpace*& OutUpperBody, UBlendSpace*& OutLowerBody, ECombatStyle CombatStyle) const;
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FCharacterBlendSpace> CombatBlendSpaces;
};
