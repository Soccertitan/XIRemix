// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/XICharacterBase.h"
#include "Components/SphereComponent.h"
#include "FunctionLibrary/MeshMergeFunctionLibrary.h"
#include "Components/XITargetSystemComponent.h"
#include "Components/XIEquipmentManagerComponent.h"
#include "Interfaces/XITargetSystemInterface.h"
#include "Interfaces/XIEquipmentManagerInterface.h"
#include "DataAssets/XICharacterHeroDefaultMesh.h"
#include "XICharacterBaseHero.generated.h"

USTRUCT(BlueprintType)
struct XIREMIX_API FXICharacterHeroActiveJobsLevels
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag MainJobTag = MainJobTag.EmptyTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag SubJobTag = SubJobTag.EmptyTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MainJobLevel = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SubJobLevel = 0.f;
};

USTRUCT()
struct XIREMIX_API FXIInteractionData
{
	GENERATED_BODY()

	FXIInteractionData()
	{
		ViewedInteractionComponent = nullptr;
		LastInteractionCheckTime = 0.f;
		bInteractHeld = false;
	}

	//The current interactable component we're viewing, if there is one
	UPROPERTY()
	class UXIInteractionComponent* ViewedInteractionComponent;

	//The time when we last checked for an interactable
	UPROPERTY()
	float LastInteractionCheckTime;

	//Whether the local player is holding the interact key.
	UPROPERTY()
	bool bInteractHeld;
};

/**
 * 
 */
UCLASS()
class XIREMIX_API AXICharacterBaseHero : public AXICharacterBase, public IXITargetSystemInterface, public IXIEquipmentManagerInterface
{
	GENERATED_BODY()

	friend class UXIEquipmentManagerComponent;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = XITarget, meta = (AllowPrivateAccess = "true"))
	class UXITargetSystemComponent* XITargetSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = XIEquipmentManager, meta = (AllowPrivateAccess = "true"))
	class UXIEquipmentManagerComponent* XIEquipmentManager;

public:
	AXICharacterBaseHero(const class FObjectInitializer& ObjectInitializer);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Only called on the Server. Calls before Server's AcknowledgePossession.
	virtual void PossessedBy(AController* NewController) override;

	// Implements XITargetSystemInterface
	virtual UXITargetSystemComponent* GetXITargetSystemComponent() const override;

	// Implements XIEquipmentManagerInterface
	virtual UXIEquipmentManagerComponent* GetXIEquipmentManagerComponent() const override;

	//Implements IXICharacterInterface
	virtual float GetCharacterLevel() const override;

	UFUNCTION(BlueprintPure, Category = "XICharacter|Hero")
	FXICharacterHeroActiveJobsLevels GetCharacterActiveJobsAndLevels() const;

	UFUNCTION(BlueprintCallable, Category = "XICharacter|Mesh")
	void SetCharacterMesh(UXIItemEquipment* Item, ESkeletalMeshMergeType SKMeshMergeType);

protected:
	
	UPROPERTY()
	class UAttributeSetHero* AttributeSetHero;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, ReplicatedUsing = OnRep_SKMeshMergeParams, Category = "XICharacter|MeshMerge")
	FSkeletalMeshMergeParams SKMeshMergeParams;
	UFUNCTION()
	void OnRep_SKMeshMergeParams();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XICharacter|MeshMerge")
	UXICharacterHeroDefaultMesh* DefaultMeshesToMerge;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "XICharacter|MeshMerge")
	TMap <ESkeletalMeshMergeType, int32> SKMeshMergeMap;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XICharacter")
	ERace Race;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Called Every frame
	virtual void Tick(float DeltaTime) override;
	
	// Client only
	virtual void OnRep_PlayerState() override;

	UFUNCTION()
	void SetCombatStyle(ECombatStyle InCombatStyle);

	void InitializeMeshesToMerge();

	//These tags are used to evaluate which job any given charcter could be.
	FGameplayTag ParentMainJobTag  = FGameplayTag::RequestGameplayTag("State.Job.Main");
	FGameplayTag ParentSubJobTag = FGameplayTag::RequestGameplayTag("State.Job.Sub");
	FGameplayTagContainer MainJobTags;
	FGameplayTagContainer SubJobTags;

	//Attribute Change Callbacks
	virtual void HitPointsChanged(const FOnAttributeChangeData& Data) override;

	//Interactables

	//How often in seconds to check for an interactable object. Set this to zero if you want to check every tick.
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float InteractionCheckFrequency;

	//How far we'll trace when we check if the player is looking at an interactable object
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float InteractionCheckDistance;
	
	//Information about the current state of the player's interaction
	UPROPERTY()
	FXIInteractionData InteractionData;

	//Helper function to make grabbing interactables faster
	FORCEINLINE class UXIInteractionComponent* GetInteractable() const {return InteractionData.ViewedInteractionComponent;}
	
	FTimerHandle TimerHandle_Interact;

public:

	//True if we're interacting with an item that has an interaction time. For example a light that takes 2 seconds to turn on.
	bool IsInteracting() const;

	//Get the time till we interact witht he current interactable
	float GetRemainingInteractTime() const;

	UFUNCTION(BlueprintCallable)
	void BeginInteract();
	UFUNCTION(BlueprintCallable)
	void EndInteract();

protected:

	void PerformInteractionCheck();
	void CouldntFindInteractable();
	void FoundNewInteractable(UXIInteractionComponent* Interactable);

	UFUNCTION(Server, WithValidation, Reliable, Category = "Interaction")
	void Server_BeginInteract();

	UFUNCTION(Server, WithValidation, Reliable, Category = "Interaction")
	void Server_EndInteract();

	void Interact();
};
