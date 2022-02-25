// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "XIRemix/XIRemix.h"
#include "XIEnums.h"
#include "XIGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UXIGameplayAbility();

	// Abilities with this set will automatically activate when the input is pressed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EXIAbilityInputID AbilityInputID = EXIAbilityInputID::None;

	// Value to associate an ability with an slot without tying it to an automatically activated input.
	// Passive abilities won't be tied to an input so we need a way to generically associate abilities with slots.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EXIAbilityInputID AbilityID = EXIAbilityInputID::None;

	// Tells an ability to activate immediately when its granted. Used for passive abilities and abilities forced on others.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
	bool bActivateAbilityOnGranted = false;

	//The cost of the ability.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability|Parameters")
	FScalableFloat Cost;

	//Used to apply a generic Cooldown GE that uses the GA's cooldown value.
	const FGameplayTagContainer* GetCooldownTags() const override;
	void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;

	// If an ability is marked as 'ActivateAbilityOnGranted', activate them immediately when given here
	// Epic's comment: Projects may want to initiate passives or do other "BeginPlay" type of logic here.
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

protected:

	// Adds the capsule radius to the range to ensure larger enemies can reach beyond the center of it's root.
	UPROPERTY(BlueprintReadWrite, Category = "Ability|Parameters")
	float CapsuleRadius;

	//The Base Power of the ability.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability|Parameters")
	float BasePower;

	// The max range of the attack.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability|Parameters")
	float Range;

	// Angle which determines the range of attack around the user. 180 = a full 360 degrees.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability|Parameters")
	float Angle;

	//Should we use Fixed Enmity Values for this ability?
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability|Enmity")
	bool bFixedEnmity;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability|Enmity", meta=(EditCondition="bFixedEnmity"))
	float CumulativeEnmity;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability|Enmity", meta=(EditCondition="bFixedEnmity"))
	float VolatileEnmity;

	// The attitute the owner needs to be towards the target actor.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability|Parameters")
	EXITeamAttitude TargetAttitude;

	//The Targeted actor for the ability. 
	UPROPERTY(BlueprintReadWrite, Category = "Ability|Target")
	AActor* MainTarget;

	//The Montage used for the ability.
	UPROPERTY(BlueprintReadWrite, Category = "Ability|Parameters")
	UAnimMontage* AnimMontage;

	UPROPERTY(BlueprintReadWrite, Category = "Ability")
	AActor* AvatarActor;

	//The cooldown for the ability.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability|Cooldown")
	FScalableFloat CooldownDuration;
	//The tag to track for the cooldown duration.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability|Cooldown")
	FGameplayTagContainer CooldownTags;

	//Temp container that we will return the pointer to in GetCooldownTags().
	//This will be the union of our CooldownTags and the Cooldown GE's cooldown tags.
	UPROPERTY(Transient)
	FGameplayTagContainer TempCooldownTags;

	// Checks the target is within Range the correct attitute.
	UFUNCTION(BlueprintPure, Category = "XIRemix|Ability")
	bool IsTargetValid(AActor* SourceActorLocation, AActor* InTargetActor, float InRange, float InAngle, EXITeamAttitude InTargetAttitude) const;

	//Returns an array of valid actors to apply AoE effects too.
	UFUNCTION(BlueprintCallable, Category = "XIRemix|Ability")
	TArray <AActor* > GetSphereAreaEffectTargets(AActor* InActorSource, float InRange); 

};
