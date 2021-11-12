// Copyright Epic Games, Inc. All Rights Reserved.

#include "XIRemixGameMode.h"
#include "Characters/HeroCharacter.h"
#include "UObject/ConstructorHelpers.h"

AXIRemixGameMode::AXIRemixGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/BP_HeroCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
