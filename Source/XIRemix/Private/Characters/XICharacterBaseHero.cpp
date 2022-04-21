// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/XICharacterBaseHero.h"
#include "Abilities/Hero/AttributeSetHero.h"
#include "Abilities/XIAbilitySystemComponent.h"
#include "Abilities/XIGameplayAbility.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/XIPlayerControllerInterface.h"
#include "UI/XIPlayerHUD.h"
#include "Net/UnrealNetwork.h"
#include "GameplayTagsManager.h"

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

	// Creates the Equipment Manager Component
	XIEquipmentManager = CreateDefaultSubobject<UXIEquipmentManagerComponent>(TEXT("XIEquipmentManager"));
	XIEquipmentManager->SetIsReplicated(true);
	XIEquipmentManager->OnMeshUpdated.AddDynamic(this, &AXICharacterBaseHero::SetCharacterMesh);
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
}

void AXICharacterBaseHero::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION_NOTIFY(AXICharacterBaseHero, SKMeshMergeParams, COND_None, REPNOTIFY_Always);
}

void AXICharacterBaseHero::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		ManaPointsMaxChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetManaPointsMaxAttribute()).AddUObject(this, &AXICharacterBaseHero::ManaPointsMaxChanged);
		TacticalPointsMaxChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetTacticalPointsMaxAttribute()).AddUObject(this, &AXICharacterBaseHero::TacticalPointsMaxChanged);
	}

	InitializeMeshesToMerge();
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
	
	IXIPlayerControllerInterface* PCInt = Cast<IXIPlayerControllerInterface>(GetController());
	if(PCInt)
	{
		PCInt->CreateHUD();
	}
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

void AXICharacterBaseHero::SetCharacterMesh(UItemEquipment* Item, ESkeletalMeshMergeType SKMeshMergeType)
{
	USkeletalMesh* TargetMesh = nullptr;

	if (Item)
	{
		if (Item->ItemType == EItemType::Shield || SKMeshMergeType != ESkeletalMeshMergeType::SubHand)
		{
			TargetMesh = Item->GetMesh(Race, false);
		}
		else
		{
			TargetMesh = Item->GetMesh(Race, true);
		}

		if(Item->CombatStyle == ECombatStyle::Hand2Hand)
		{
			int32 SubHandKey = SKMeshMergeMap.FindRef(ESkeletalMeshMergeType::SubHand);
			SKMeshMergeParams.MeshesToMerge[SubHandKey] = Item->GetMesh(Race, true);
		}
	}
	else
	{
		if(!XIEquipmentManager->GetSubHandItem())
		{
			int32 SubHandKey = SKMeshMergeMap.FindRef(ESkeletalMeshMergeType::SubHand);
			SKMeshMergeParams.MeshesToMerge[SubHandKey] = nullptr;
		}
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