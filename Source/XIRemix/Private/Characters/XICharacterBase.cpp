// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/XICharacterBase.h"
#include "Abilities/AttributeSetGlobal.h"
#include "Abilities/AbilitySystemComponentGlobal.h"
#include "Abilities/GameplayAbilityGlobal.h"
#include "Components/CapsuleComponent.h"
#include "Characters/XICharacterMovementComponent.h"

// Sets default values
AXICharacterBase::AXICharacterBase(const class FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UXICharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bAlwaysRelevant = true;

	// Cache Tags
	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Debuff.Dead"));

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponentGlobal>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAttributeSetGlobal>("AttributeSet");
}

// Called when the game starts or when spawned
void AXICharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

UAbilitySystemComponent * AXICharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

bool AXICharacterBase::IsAlive() const
{
	return GetHitPoints() > 0.0f;
}

void AXICharacterBase::InitializeAttributes()
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
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
	}
}

#pragma region AttributeGetters

float AXICharacterBase::GetHitPoints() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetHitPoints();
	}
	return 0.0f;
}

float AXICharacterBase::GetHitPointsMax() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetHitPointsMax();
	}

	return 0.0f;
}

float AXICharacterBase::GetManaPoints() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetManaPoints();
	}

	return 0.0f;
}

float AXICharacterBase::GetManaPointsMax() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetManaPointsMax();
	}

	return 0.0f;
}

float AXICharacterBase::GetTacticalPoints() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetTacticalPoints();
	}

	return 0.0f;
}

float AXICharacterBase::GetTacticalPointsMax() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetTacticalPointsMax();
	}

	return 0.0f;
}

float AXICharacterBase::GetMoveSpeed() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetMoveSpeed();
	}

	return 0.0f;
}

#pragma endregion AttributeGetters

