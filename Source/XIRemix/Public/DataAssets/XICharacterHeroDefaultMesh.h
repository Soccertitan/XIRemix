// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "XICharacterHeroDefaultMesh.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class XIREMIX_API UXICharacterHeroDefaultMesh : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMesh* Face;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMesh* Body;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMesh* Hands;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMesh* Legs;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMesh* Feet;
};
