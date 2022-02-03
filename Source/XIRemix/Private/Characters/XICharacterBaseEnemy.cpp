// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/XICharacterBaseEnemy.h"
#include "Abilities/Enemy/AttributeSetEnemy.h"
#include "Abilities/XIAbilitySystemComponent.h"
#include "Abilities/XIGameplayAbility.h"

// Sets default values
AXICharacterBaseEnemy::AXICharacterBaseEnemy(const class FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	AttributeSetEnemy = CreateDefaultSubobject<UAttributeSetEnemy>("AttributeSetEnemy");
	XIAggroComponent = CreateDefaultSubobject<UXIAggroComponent>("XIAggroComponent");
	XIAggroComponent->SphereComponent->SetupAttachment(RootComponent);

	XITeam = EXITeam::Enemy;
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
	AddCharacterAbilities();
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