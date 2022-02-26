// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/XICharacterBaseHero.h"
#include "Abilities/Hero/AttributeSetHero.h"
#include "Abilities/XIAbilitySystemComponent.h"
#include "Abilities/XIGameplayAbility.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/XIPlayerControllerInterface.h"
#include "UI/XIPlayerHUD.h"

// Sets default values
AXICharacterBaseHero::AXICharacterBaseHero(const class FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	AttributeSetHero = CreateDefaultSubobject<UAttributeSetHero>("AttributeSetHero");

	// XI Targeting system for players
	XITargetSystem = CreateDefaultSubobject<UXITargetSystemComponent>("XITargetSystem");
	XITargetSystem->SphereComponent->SetupAttachment(RootComponent);

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraBoom->PrimaryComponentTick.bStartWithTickEnabled = false;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	FollowCamera->PrimaryComponentTick.bStartWithTickEnabled = false;

	//Mesh Merge Map
	SKMeshMergeMap.Add(ESkeletalMeshMergeType::Face, 0);
	SKMeshMergeMap.Add(ESkeletalMeshMergeType::Head, 1);
	SKMeshMergeMap.Add(ESkeletalMeshMergeType::Body, 2);
	SKMeshMergeMap.Add(ESkeletalMeshMergeType::Arms, 3);
	SKMeshMergeMap.Add(ESkeletalMeshMergeType::Legs, 4);
	SKMeshMergeMap.Add(ESkeletalMeshMergeType::Feet, 5);
	SKMeshMergeMap.Add(ESkeletalMeshMergeType::MainHand, 6);
	SKMeshMergeMap.Add(ESkeletalMeshMergeType::SubHand, 7);
	SKMeshMergeMap.Add(ESkeletalMeshMergeType::Range, 8);

	XITeam = EXITeam::Hero;
}

void AXICharacterBaseHero::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		ManaPointsMaxChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetManaPointsMaxAttribute()).AddUObject(this, &AXICharacterBaseHero::ManaPointsMaxChanged);
		TacticalPointsMaxChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetTacticalPointsMaxAttribute()).AddUObject(this, &AXICharacterBaseHero::TacticalPointsMaxChanged);
	}
}

// Server only
void AXICharacterBaseHero::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);

	// Initialize GAS
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	AddCharacterAbilities();
	InitializeAttributes();
	AddStartupEffects();
}

// Client only
void AXICharacterBaseHero::OnRep_PlayerState() 
{
	Super::OnRep_PlayerState();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	InitializeAttributes();
	
	IXIPlayerControllerInterface* PCInt = Cast<IXIPlayerControllerInterface>(GetController());
	if(PCInt)
	{
		PCInt->CreateHUD();
	}
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

#pragma region AttributeChangeCallbacks

void AXICharacterBaseHero::HitPointsChanged(const FOnAttributeChangeData & Data)
{
	Super::HitPointsChanged(Data);
	float HitPoints = Data.NewValue;
	
	IXIPlayerControllerInterface* PCInt = Cast<IXIPlayerControllerInterface>(GetController());
	if(PCInt)
	{
		UXIPlayerHUD* PlayerHUD = PCInt->GetHUD();
		if(PlayerHUD)
		{
			PlayerHUD->SetHitPoints(HitPoints);
		}
	}
}

void AXICharacterBaseHero::HitPointsMaxChanged(const FOnAttributeChangeData & Data)
{
	float HitPointsMax = Data.NewValue;

	IXIPlayerControllerInterface* PCInt = Cast<IXIPlayerControllerInterface>(GetController());
	if(PCInt)
	{
		UXIPlayerHUD* PlayerHUD = PCInt->GetHUD();
		if(PlayerHUD)
		{
			PlayerHUD->SetHitPointsMax(HitPointsMax);
		}
	}
}

void AXICharacterBaseHero::ManaPointsChanged(const FOnAttributeChangeData& Data)
{
	float ManaPoints = Data.NewValue;

	IXIPlayerControllerInterface* PCInt = Cast<IXIPlayerControllerInterface>(GetController());
	if(PCInt)
	{
		UXIPlayerHUD* PlayerHUD = PCInt->GetHUD();
		if(PlayerHUD)
		{
			PlayerHUD->SetManaPoints(ManaPoints);
		}
	}
}

void AXICharacterBaseHero::ManaPointsMaxChanged(const FOnAttributeChangeData& Data)
{
	float ManaPointsMax = Data.NewValue;

	IXIPlayerControllerInterface* PCInt = Cast<IXIPlayerControllerInterface>(GetController());
	if(PCInt)
	{
		UXIPlayerHUD* PlayerHUD = PCInt->GetHUD();
		if(PlayerHUD)
		{
			PlayerHUD->SetManaPointsMax(ManaPointsMax);
		}
	}
}

void AXICharacterBaseHero::TacticalPointsChanged(const FOnAttributeChangeData& Data)
{
	float TacticalPoints = Data.NewValue;

	IXIPlayerControllerInterface* PCInt = Cast<IXIPlayerControllerInterface>(GetController());
	if(PCInt)
	{
		UXIPlayerHUD* PlayerHUD = PCInt->GetHUD();
		if(PlayerHUD)
		{
			PlayerHUD->SetTacticalPoints(TacticalPoints);
		}
	}
}

void AXICharacterBaseHero::TacticalPointsMaxChanged(const FOnAttributeChangeData& Data)
{
	float TacticalPointsMax = Data.NewValue;

	IXIPlayerControllerInterface* PCInt = Cast<IXIPlayerControllerInterface>(GetController());
	if(PCInt)
	{
		UXIPlayerHUD* PlayerHUD = PCInt->GetHUD();
		if(PlayerHUD)
		{
			PlayerHUD->SetTacticalPointsMax(TacticalPointsMax);
		}
	}
}

#pragma endregion AttributeChangeCallbacks

UXITargetSystemComponent* AXICharacterBaseHero::GetXITargetSystemComponent() const
{
	return XITargetSystem;
}