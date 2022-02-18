// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XIEnums.h"
#include "XICharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UXICharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XIREMIX_API IXICharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// /**
	// * Getters for Anim Montages
	// **/
	virtual UAnimMontage* GetAutoAttackMontage() PURE_VIRTUAL(IXICharacterInterface::GetAutoAttackMontage(), return nullptr;);
	virtual UAnimMontage* GetBlackMagicMontage() PURE_VIRTUAL(IXICharacterInterface::GetBlackMagicMontage(), return nullptr;);
	virtual UAnimMontage* GetWhiteMagicMontage() PURE_VIRTUAL(IXICharacterInterface::GetWhiteMagicMontage(), return nullptr;);
	virtual UAnimMontage* GetSummonerMagicMontage() PURE_VIRTUAL(IXICharacterInterface::GetSummonerMagicMontage(), return nullptr;);
	virtual UAnimMontage* GetNinjitsuMagicMontage() PURE_VIRTUAL(IXICharacterInterface::GetNinjitsuMagicMontage(), return nullptr;);
	virtual UAnimMontage* GetBlueMagicMontage() PURE_VIRTUAL(IXICharacterInterface::GetBlueMagicMontage(), return nullptr;);
	virtual UAnimMontage* GetGeoMagicMontage() PURE_VIRTUAL(IXICharacterInterface::GetGeoMagicMontage(), return nullptr;);
	virtual UAnimMontage* GetJobAbilityMontage() PURE_VIRTUAL(IXICharacterInterface::GetJobAbilityMontage(), return nullptr;);
	virtual UAnimMontage* GetJobAbilityCombatMontage() PURE_VIRTUAL(IXICharacterInterface::GetJobAbilityCombatMontage(), return nullptr;);

	// GetCharacterName is Implemented in C++
	virtual FText GetCharacterName() const PURE_VIRTUAL(IXICharacterInterface::GetCharacterName(), return FText(););

	// GetMainTarget is Implemented in C++
	virtual AActor* GetMainTarget() const PURE_VIRTUAL(IXICharacterInterface::GetMainTarget(), return nullptr;);

	// GetSubTarget is Implemented in C++
	virtual AActor* GetSubTarget() const PURE_VIRTUAL(IXICharacterInterface::GetSubTarget(), return nullptr;);

	// Get the XITeam from Actor
	virtual EXITeam GetXITeam() const PURE_VIRTUAL(IXICharacterInterface::GetXITeam(), return EXITeam::Neutral;);

	//Get Attitute Towards Actor implemented in C++
	virtual EXITeamAttitude GetAttitudeTowardsActor(AActor* OtherActor) const PURE_VIRTUAL(IXICharacterInterface::GetAttitudeTowardsActor(AActor* OtherActor), return EXITeamAttitude::Neutral;);

	//Gets the Radius of the capsule component. Implemented in C++
	virtual float GetCapsuleRadius() const PURE_VIRTUAL(IXICharacterInterface::GetCapsuleRadius(), return 0.f;);

	//Is the character alive?
	virtual bool IsAlive() const PURE_VIRTUAL(IXICharacterInterface::IsAlive(), return false;);

	// /**
	// * Getters for attributes from GlobalAttributeSet
	// **/
	virtual float GetMoveSpeed() const PURE_VIRTUAL(IXICharacterInterface::GetMoveSpeed(), return 0.f;);
	virtual float GetHitPoints() const PURE_VIRTUAL(IXICharacterInterface::GetHitPoints(), return 0.f;);
	virtual float GetHitPointsMax() const PURE_VIRTUAL(IXICharacterInterface::GetHitPointsMax(), return 0.f;);
	virtual float GetManaPoints() const PURE_VIRTUAL(IXICharacterInterface::GetManaPoints(), return 0.f;);
	virtual float GetManaPointsMax() const PURE_VIRTUAL(IXICharacterInterface::GetManaPointsMax(), return 0.f;);
	virtual float GetTacticalPoints() const PURE_VIRTUAL(IXICharacterInterface::GetTacticalPoints(), return 0.f;);
	virtual float GetTacticalPointsMax() const PURE_VIRTUAL(IXICharacterInterface::GetTacticalPointsMax(), return 0.f;);
	
};
