// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Interfaces/XIAnimBPInterface.h"
#include "XIEnums.h"
#include "DataAssets/XICharacterBlendSpaces.h"
#include "XIHeroAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIHeroAnimInstance : public UAnimInstance, public IXIAnimBPInterface
{
	GENERATED_BODY()

public:

	// IXIAnimBPInterface Implemented Functions
	virtual float GetDirection() override;
	virtual float GetSpeed() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "XICharacter|AnimBP")
	void SetCombatStyle(ECombatStyle InCombatStyle); virtual void SetCombatStyle_Implementation(ECombatStyle InCombatStyle) override;

protected:	
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UXICharacterBlendSpaces* BlendSpaces;
	UPROPERTY(BlueprintReadOnly)
	UBlendSpace* CombatUpperBody;
	UPROPERTY(BlueprintReadOnly)
	UBlendSpace* CombatLowerBody;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ECombatStyle CombatStyle;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Direction;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Speed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsDead;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsInAir;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bWeaponsOut;

	UPROPERTY(BlueprintReadWrite)
	APawn* XICharacter;
};
