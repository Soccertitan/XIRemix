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

	// GetAutoAtkMontage is Implemented in C++
	virtual UAnimMontage* GetAutoAttackMontage() PURE_VIRTUAL(IXICharacterInterface::GetAutoAttackMontage(), return nullptr;);

	// GetCharacterName is Implemented in C++
	virtual FText GetCharacterName() PURE_VIRTUAL(IXICharacterInterface::GetCharacterName(), return FText(););

	// GetMainTarget is Implemented in C++
	virtual AActor* GetMainTarget() PURE_VIRTUAL(IXICharacterInterface::GetMainTarget(), return nullptr;);

	// GetSubTarget is Implemented in C++
	virtual AActor* GetSubTarget() PURE_VIRTUAL(IXICharacterInterface::GetSubTarget(), return nullptr;);

	// Get the XITeam from Actor
	virtual EXITeam GetXITeam() PURE_VIRTUAL(IXICharacterInterface::GetXITeam(), return EXITeam::Neutral;);

	//Get Attitute Towards Actor implemented in C++
	virtual EXITeamAttitude GetAttitudeTowardsActor(AActor* OtherActor) PURE_VIRTUAL(IXICharacterInterface::GetAttitudeTowardsActor(AActor* OtherActor), return EXITeamAttitude::Neutral;);

	//Gets the Radius of the capsule component. Implemented in C++
	virtual float GetCapsuleRadius() PURE_VIRTUAL(IXICharacterInterface::GetCapsuleRadius(), return 0.f;);
};
