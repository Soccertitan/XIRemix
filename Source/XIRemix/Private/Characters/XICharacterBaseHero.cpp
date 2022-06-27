// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/XICharacterBaseHero.h"
#include "Abilities/Hero/AttributeSetHero.h"
#include "Abilities/XIAbilitySystemComponent.h"
#include "Abilities/XIGameplayAbility.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/XIPlayerControllerInterface.h"
#include "Components/XIInteractionComponent.h"
#include "Net/UnrealNetwork.h"
#include "GameplayTagsManager.h"

// Sets default values
AXICharacterBaseHero::AXICharacterBaseHero(const class FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	AttributeSetHero = CreateDefaultSubobject<UAttributeSetHero>("AttributeSetHero");

	AbilitySystemComponent->OnLevelUp.AddDynamic(this, &AXICharacterBaseHero::LevelUp);

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

	// Creates the Equipment Manager Component
	XIEquipmentManager = CreateDefaultSubobject<UXIEquipmentManagerComponent>(TEXT("XIEquipmentManager"));
	XIEquipmentManager->SetIsReplicated(true);
	XIEquipmentManager->OnUpdateMesh.AddDynamic(this, &AXICharacterBaseHero::SetCharacterMesh);
	XIEquipmentManager->OnCombatStyleChanged.AddDynamic(this, &AXICharacterBaseHero::SetCombatStyle);

	//Mesh Merge Map
	SKMeshMergeMap.Add(ESkeletalMeshMergeType::Face, 0);
	SKMeshMergeMap.Add(ESkeletalMeshMergeType::Head, 1);
	SKMeshMergeMap.Add(ESkeletalMeshMergeType::Body, 2);
	SKMeshMergeMap.Add(ESkeletalMeshMergeType::Hands, 3);
	SKMeshMergeMap.Add(ESkeletalMeshMergeType::Legs, 4);
	SKMeshMergeMap.Add(ESkeletalMeshMergeType::Feet, 5);
	SKMeshMergeMap.Add(ESkeletalMeshMergeType::MainHand, 6);
	SKMeshMergeMap.Add(ESkeletalMeshMergeType::SubHand, 7);
	SKMeshMergeMap.Add(ESkeletalMeshMergeType::Range, 8);

	SKMeshMergeParams.MeshesToMerge.SetNum(9);

	XITeam = EXITeam::Hero;

	MainJobTags = UGameplayTagsManager::Get().RequestGameplayTagChildren(ParentMainJobTag);
    SubJobTags = UGameplayTagsManager::Get().RequestGameplayTagChildren(ParentSubJobTag);

	InteractionCheckFrequency = 0.f;
	InteractionCheckDistance = 1000.f;
}

void AXICharacterBaseHero::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION_NOTIFY(AXICharacterBaseHero, SKMeshMergeParams, COND_None, REPNOTIFY_Always);
}

void AXICharacterBaseHero::BeginPlay()
{
	Super::BeginPlay();

	InitializeMeshesToMerge();

	OnRep_CombatStyle();
}

void AXICharacterBaseHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// const bool bIsInteractingOnServer = (HasAuthority() && IsInteracting());
	if(!IsLocallyControlled())
	{
		SetActorTickEnabled(false);
	}

	if(GetWorld()->TimeSince(InteractionData.LastInteractionCheckTime) > InteractionCheckFrequency)
	{
		PerformInteractionCheck();
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
}

// Client only
void AXICharacterBaseHero::OnRep_PlayerState() 
{
	Super::OnRep_PlayerState();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	InitializeAttributes();
}

#pragma region AttributeGetters

float AXICharacterBaseHero::GetCharacterLevel() const
{
	FXICharacterHeroActiveJobsLevels Level = GetCharacterActiveJobsAndLevels();
	return Level.MainJobLevel;
}

FXICharacterHeroActiveJobsLevels AXICharacterBaseHero::GetCharacterActiveJobsAndLevels() const
{
	TArray<FGameplayTag> JobTagsArray;
    FXIJobTagRelationshipItem JobTagRelationshipItem;

	FXICharacterHeroActiveJobsLevels CharacterJobLevel;

    FGameplayTagContainer OwnedGameplayTags;
	AbilitySystemComponent->GetOwnedGameplayTags(OwnedGameplayTags);

	/*
    // Find and return the Main Job Tag and Level.
    */
    MainJobTags.GetGameplayTagArray(JobTagsArray);
	for(const FGameplayTag& JobTag : JobTagsArray)
	{
		if(OwnedGameplayTags.HasTagExact(JobTag))
        {
            AbilitySystemComponent->GetXIJobTagRelationship(JobTag, JobTagRelationshipItem);
            CharacterJobLevel.MainJobTag = JobTag;
            CharacterJobLevel.MainJobLevel = AbilitySystemComponent->GetNumericAttribute(JobTagRelationshipItem.JobLevelAttribute);
            break;
        }
    }

	/*
    // Find and return the Sub Job Tag and Level.
    */
    SubJobTags.GetGameplayTagArray(JobTagsArray);
    for(const FGameplayTag& JobTag : JobTagsArray)
    {
        if(OwnedGameplayTags.HasTagExact(JobTag))
        {
			AbilitySystemComponent->GetXIJobTagRelationship(JobTag, JobTagRelationshipItem);
			CharacterJobLevel.SubJobTag = JobTag;
			CharacterJobLevel.SubJobLevel = AbilitySystemComponent->GetNumericAttribute(JobTagRelationshipItem.JobLevelAttribute);
			return CharacterJobLevel;
        }
    }
	return CharacterJobLevel;
}

#pragma endregion AttributeGetters

void AXICharacterBaseHero::LevelUp()
{
	FXICharacterHeroActiveJobsLevels CharacterLevels = GetCharacterActiveJobsAndLevels();
	FGameplayTagContainer MJTagContainer;
	FGameplayTagContainer SJTagContainer;
	MJTagContainer.AddTag(CharacterLevels.MainJobTag);
	SJTagContainer.AddTag(CharacterLevels.SubJobTag);
	
	AbilitySystemComponent->TryActivateAbilitiesByTag(MJTagContainer, true);
	AbilitySystemComponent->TryActivateAbilitiesByTag(SJTagContainer, true);
}

void AXICharacterBaseHero::HitPointsChanged(const FOnAttributeChangeData & Data)
{
	Super::HitPointsChanged(Data);
}

UXITargetSystemComponent* AXICharacterBaseHero::GetXITargetSystemComponent() const
{
	return XITargetSystem;
}

UXIEquipmentManagerComponent* AXICharacterBaseHero::GetXIEquipmentManagerComponent() const
{
	return XIEquipmentManager;
}

void AXICharacterBaseHero::OnRep_SKMeshMergeParams()
{
	USkeletalMesh* MergedMesh = UMeshMergeFunctionLibrary::MergeMeshes(SKMeshMergeParams);

	if (MergedMesh)
	{
		GetMesh()->SetSkeletalMesh(MergedMesh, false);
	}
}

void AXICharacterBaseHero::SetCharacterMesh(UXIItemEquipment* Item, ESkeletalMeshMergeType SKMeshMergeType)
{
	if(!HasAuthority())
	{
		return;
	}

	USkeletalMesh* TargetMesh = nullptr;

	if (Item)
	{
		if (SKMeshMergeType == ESkeletalMeshMergeType::SubHand && Item->ItemType == EItemType::WeaponMelee)
		{
			TargetMesh = Item->GetMesh(Race, true);
		}
		else
		{
			TargetMesh = Item->GetMesh(Race, false);
		}

		if(SKMeshMergeType == ESkeletalMeshMergeType::MainHand && Item->CombatStyle == ECombatStyle::Battle3)
		{
			int32 SubHandKey = SKMeshMergeMap.FindRef(ESkeletalMeshMergeType::SubHand);
			SKMeshMergeParams.MeshesToMerge[SubHandKey] = Item->GetMesh(Race, true);
		}
	}

	if(!XIEquipmentManager->FindEquippedItemBySlot(EEquipSlot::SubHand) && CombatStyle != ECombatStyle::Battle3)
	{
		int32 SubHandKey = SKMeshMergeMap.FindRef(ESkeletalMeshMergeType::SubHand);
		SKMeshMergeParams.MeshesToMerge[SubHandKey] = nullptr;
	}

	// To ensure the character body isn't invisible if mesh is null.
	if (TargetMesh == nullptr && DefaultMeshesToMerge)
	{
		switch (SKMeshMergeType)
		{
			case ESkeletalMeshMergeType::Body:
				TargetMesh = DefaultMeshesToMerge->Body;
				break;
			case ESkeletalMeshMergeType::Hands:
				TargetMesh = DefaultMeshesToMerge->Hands;
				break;
			case ESkeletalMeshMergeType::Legs:
				TargetMesh = DefaultMeshesToMerge->Legs;
				break;
			case ESkeletalMeshMergeType::Feet:
				TargetMesh = DefaultMeshesToMerge->Feet;
				break;
		}
	}

	int32 Key = SKMeshMergeMap.FindRef(SKMeshMergeType);
	SKMeshMergeParams.MeshesToMerge[Key] = TargetMesh;

	OnRep_SKMeshMergeParams();
}

void AXICharacterBaseHero::InitializeMeshesToMerge()
{
	if (DefaultMeshesToMerge)
	{
		int32 Key = SKMeshMergeMap.FindRef(ESkeletalMeshMergeType::Face);
		if (!SKMeshMergeParams.MeshesToMerge[Key])
		{
			SKMeshMergeParams.MeshesToMerge[Key] = DefaultMeshesToMerge->Face;
		}

		Key = SKMeshMergeMap.FindRef(ESkeletalMeshMergeType::Body);
		if (!SKMeshMergeParams.MeshesToMerge[Key])
		{
			SKMeshMergeParams.MeshesToMerge[Key] = DefaultMeshesToMerge->Body;
		}

		Key = SKMeshMergeMap.FindRef(ESkeletalMeshMergeType::Hands);
		if (!SKMeshMergeParams.MeshesToMerge[Key])
		{
			SKMeshMergeParams.MeshesToMerge[Key] = DefaultMeshesToMerge->Hands;
		}

		Key = SKMeshMergeMap.FindRef(ESkeletalMeshMergeType::Legs);
		if (!SKMeshMergeParams.MeshesToMerge[Key])
		{
			SKMeshMergeParams.MeshesToMerge[Key] = DefaultMeshesToMerge->Legs;
		}

		Key = SKMeshMergeMap.FindRef(ESkeletalMeshMergeType::Feet);
		if (!SKMeshMergeParams.MeshesToMerge[Key])
		{
			SKMeshMergeParams.MeshesToMerge[Key] = DefaultMeshesToMerge->Feet;
		}
	}

	OnRep_SKMeshMergeParams();
}

void AXICharacterBaseHero::SetCombatStyle(ECombatStyle InCombatStyle)
{
	CombatStyle = InCombatStyle;
	OnRep_CombatStyle();
}


#pragma region Interactables

void AXICharacterBaseHero::PerformInteractionCheck()
{
	if (GetController() == nullptr)
	{
		return;
	}

	InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds();

	FVector ForwardVector = GetActorForwardVector();
	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = (ForwardVector * InteractionCheckDistance) + TraceStart;
	FHitResult TraceHit;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	if(GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
	{
		//Check if we hit an interactable object
		if(TraceHit.GetActor())
		{
			if(UXIInteractionComponent* InteractionComponent = Cast<UXIInteractionComponent>(TraceHit.GetActor()->GetComponentByClass(UXIInteractionComponent::StaticClass())))
			{
				float Distance = (TraceStart - TraceHit.ImpactPoint).Size();

				if(InteractionComponent != GetInteractable() && Distance <= InteractionComponent->InteractionDistance)
				{
					FoundNewInteractable(InteractionComponent);
					return;
				}
				else if (Distance > InteractionComponent->InteractionDistance && GetInteractable())
				{
					CouldntFindInteractable();
				}
				return;
			}
		}
	}
	CouldntFindInteractable();
}

void AXICharacterBaseHero::CouldntFindInteractable()
{
	//We've lost focus on an interactable. Clear the timer
	if(GetWorldTimerManager().IsTimerActive(TimerHandle_Interact))
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_Interact);
	}

	//Tell the interactable we've stopped focusing on it and clear the current interactable.
	if(UXIInteractionComponent* Interactable = GetInteractable())
	{
		Interactable->EndFocus(this);
		
		if(InteractionData.bInteractHeld)
		{
			EndInteract();
		}
	}

	InteractionData.ViewedInteractionComponent = nullptr;
}

void AXICharacterBaseHero::FoundNewInteractable(UXIInteractionComponent* Interactable)
{
	EndInteract();

	if(UXIInteractionComponent* OldInteractable = GetInteractable())
	{
		OldInteractable->EndFocus(this);
	}

	InteractionData.ViewedInteractionComponent = Interactable;
	Interactable->BeginFocus(this);
}

void AXICharacterBaseHero::BeginInteract()
{
	if(!HasAuthority())
	{
		Server_BeginInteract();
	}

	/**As an optimization, the server only checks that we're looking at an item once we begin interacting with it.
	This saves the server doing a check every tick for an interactable Item. The exception is a non-instant interact.
	In this case, the server will check every tick for the duration of the interact*/
	if (HasAuthority())
	{
		PerformInteractionCheck();
	}

	InteractionData.bInteractHeld = true;

	if (UXIInteractionComponent* Interactable = GetInteractable())
	{
		Interactable->BeginInteract(this);

		if (FMath::IsNearlyZero(Interactable->InteractionTime))
		{
			Interact();
		}
		else
		{
			GetWorldTimerManager().SetTimer(TimerHandle_Interact, this, &AXICharacterBaseHero::Interact, Interactable->InteractionTime, false);
		}
	}
}

bool AXICharacterBaseHero::Server_BeginInteract_Validate()
{
	return true;
}

void AXICharacterBaseHero::Server_BeginInteract_Implementation()
{
	BeginInteract();
}

void AXICharacterBaseHero::EndInteract()
{
	if(!HasAuthority())
	{
		Server_EndInteract();
	}

	InteractionData.bInteractHeld = false;

	GetWorldTimerManager().ClearTimer(TimerHandle_Interact);

	if(UXIInteractionComponent* Interactable = GetInteractable())
	{
		Interactable->EndInteract(this);
	}
}

bool AXICharacterBaseHero::Server_EndInteract_Validate()
{
	return true;
}

void AXICharacterBaseHero::Server_EndInteract_Implementation()
{
	EndInteract();
}

void AXICharacterBaseHero::Interact()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interact);

	if(UXIInteractionComponent* Interactable = GetInteractable())
	{
		Interactable->Interact(this);
	}
}

bool AXICharacterBaseHero::IsInteracting() const
{
	return GetWorldTimerManager().IsTimerActive(TimerHandle_Interact);
}

float AXICharacterBaseHero::GetRemainingInteractTime() const
{
	return GetWorldTimerManager().GetTimerRemaining(TimerHandle_Interact);
}

#pragma endregion Interactables

