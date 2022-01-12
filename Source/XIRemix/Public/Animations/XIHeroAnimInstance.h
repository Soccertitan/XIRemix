// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Interfaces/AnimationBP.h"
#include "XIEnums.h"
#include "XIHeroAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIHeroAnimInstance : public UAnimInstance, public IAnimationBP
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "XICharacter|AnimBP")
	float GetDirection(); virtual float GetDirection_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "XICharacter|AnimBP")
	float GetSpeed(); virtual float GetSpeed_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "XICharacter|AnimBP")
	void SetCombatStyle(ECombatStyle CStyle); virtual void SetCombatStyle_Implementation(ECombatStyle CStyle) override;

protected:	
	
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
