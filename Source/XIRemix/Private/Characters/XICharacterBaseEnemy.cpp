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

void AXICharacterBaseEnemy::InitializeAttributes()
{
	if (!AbilitySystemComponent)
	{
		return;
	}

	if (!DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	// Can run on Server and Client
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);
	FGameplayEffectSpec* GES = NewHandle.Data.Get();
	GES->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag("SetByCaller.Potency"), Level);

	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
	}
}

// Server only
void AXICharacterBaseEnemy::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);

	// Initialize GAS
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	AddCharacterAbilities();
	InitializeAttributes();
}

// Client only
void AXICharacterBaseEnemy::OnRep_PlayerState() 
{
	Super::OnRep_PlayerState();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	InitializeAttributes();
}

UXIAggroComponent* AXICharacterBaseEnemy::GetXIAggroComponent() const
{
	return XIAggroComponent;
}

float AXICharacterBaseEnemy::GetCharacterLevel() const
{
	return AttributeSetEnemy->GetLevel();
}