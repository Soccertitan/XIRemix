// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/XICharacterBase.h"
#include "Abilities/AttributeSetGlobal.h"
#include "Abilities/AbilitySystemComponentGlobal.h"
#include "Abilities/GameplayAbilityGlobal.h"
#include "Net/UnrealNetwork.h"
#include "Components/CapsuleComponent.h"
#include "Characters/XICharacterMovementComponent.h"

// Sets default values
AXICharacterBase::AXICharacterBase(const class FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UXICharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
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

	if (AbilitySystemComponent)
	{
		HitPointsChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHitPointsAttribute()).AddUObject(this, &AXICharacterBase::HitPointsChanged);
		HitPointsMaxChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHitPointsMaxAttribute()).AddUObject(this, &AXICharacterBase::HitPointsMaxChanged);
	}
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

void AXICharacterBase::AddStartupEffects()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent || AbilitySystemComponent->StartupEffectsApplied)
	{
		UE_LOG(LogTemp, Warning, TEXT("Startup Effects Will not Apply"));
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempting to apply GE Spec to Self"));
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 0, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
			UE_LOG(LogTemp, Warning, TEXT("Applied GE Spec to Self"));
		}
		UE_LOG(LogTemp, Warning, TEXT("GE Handle Invalid"));
	}

	AbilitySystemComponent->StartupEffectsApplied = true;
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

#pragma region CharacterName

FText AXICharacterBase::GetCharacterName() const
{
	return CharacterName;
}

bool AXICharacterBase::Server_SetCharacterName_Validate(FText Name)
{
	return true;
}

void AXICharacterBase::Server_SetCharacterName_Implementation(FText Name)
{
	CharacterName = Name;
}

#pragma endregion CharacterName

#pragma region AttributeChangeCallbacks

void AXICharacterBase::HitPointsChanged(const FOnAttributeChangeData & Data)
{
	float HitPoints = Data.NewValue;
}

void AXICharacterBase::HitPointsMaxChanged(const FOnAttributeChangeData & Data)
{
	float HitPointsMax = Data.NewValue;
}

#pragma endregion AttributeChangeCallbacks

void AXICharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const 
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AXICharacterBase, CharacterName);
}