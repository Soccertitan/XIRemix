// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/XICharacterBaseHero.h"
#include "Abilities/Hero/AttributeSetHero.h"
#include "Abilities/AbilitySystemComponentGlobal.h"
#include "Abilities/GameplayAbilityGlobal.h"

// Sets default values
AXICharacterBaseHero::AXICharacterBaseHero(const class FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	AttributeSetHero = CreateDefaultSubobject<UAttributeSetHero>("AttributeSetHero");
}

void AXICharacterBaseHero::BeginPlay()
{
	Super::BeginPlay();
}

// Server only
void AXICharacterBaseHero::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);

	// Initialize GAS
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	InitializeAttributes();
}

// Client only
void AXICharacterBaseHero::OnRep_PlayerState() 
{
	Super::OnRep_PlayerState();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	InitializeAttributes();
}

#pragma region AttributeGetters

float AXICharacterBaseHero::GetWarriorLevel() const
{
	if (AttributeSetHero)
	{
		return AttributeSetHero->GetWarriorLevel();
	}
	return 0.0f;
}

#pragma endregion AttributeGetters

