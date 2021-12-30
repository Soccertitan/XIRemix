// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/XICharacterBaseEnemy.h"
#include "Abilities/Enemy/AttributeSetEnemy.h"
#include "Abilities/AbilitySystemComponentGlobal.h"
#include "Abilities/GameplayAbilityGlobal.h"

// Sets default values
AXICharacterBaseEnemy::AXICharacterBaseEnemy(const class FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	AttributeSetEnemy = CreateDefaultSubobject<UAttributeSetEnemy>("AttributeSetEnemy");
}

void AXICharacterBaseEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Server only
void AXICharacterBaseEnemy::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);

	// Initialize GAS
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	InitializeAttributes();
	AddStartupEffects();
}

// Client only
void AXICharacterBaseEnemy::OnRep_PlayerState() 
{
	Super::OnRep_PlayerState();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	InitializeAttributes();
}