// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/XICharacterBase.h"
#include "Components/SphereComponent.h"
#include "FunctionLibrary/MeshMergeFunctionLibrary.h"
#include "Components/XITargetSystemComponent.h"
#include "Interfaces/XITargetSystemInterface.h"
#include "XICharacterBaseHero.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API AXICharacterBaseHero : public AXICharacterBase, public IXITargetSystemInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = XITarget, meta = (AllowPrivateAccess = "true"))
	class UXITargetSystemComponent* XITargetSystem;

public:
	AXICharacterBaseHero(const class FObjectInitializer& ObjectInitializer);

	// Only called on the Server. Calls before Server's AcknowledgePossession.
	virtual void PossessedBy(AController* NewController) override;

	// Implements XITargetSystemInterface
	virtual UXITargetSystemComponent* GetXITargetSystemComponent() const override;

	//Implements IXICharacterInterface
	virtual float GetCharacterLevel() const override;

	UFUNCTION(BlueprintPure, Category = "XICharacter|Hero")
	void GetCharacterActiveJobsAndLevels(FGameplayTag& MainJobTag, float& MainJobLevel, FGameplayTag& SubJobTag, float& SubJobLevel) const;

protected:
	
	UPROPERTY()
	class UAttributeSetHero* AttributeSetHero;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "XICharacter|MeshMerge")
	FSkeletalMeshMergeParams SKMeshMergeParams;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "XICharacter|MeshMerge")
	TMap <ESkeletalMeshMergeType, int32> SKMeshMergeMap;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XICharacter")
	ERace Race;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Client only
	virtual void OnRep_PlayerState() override;	

	//These tags are used to evaluate which job any given charcter could be.
	FGameplayTag ParentMainJobTag  = FGameplayTag::RequestGameplayTag("State.Job.Main");
	FGameplayTag ParentSubJobTag = FGameplayTag::RequestGameplayTag("State.Job.Sub");
	FGameplayTagContainer MainJobTags;
	FGameplayTagContainer SubJobTags;

	//Attribute Change Callbacks
	FDelegateHandle ManaPointsMaxChangedDelegateHandle;
	FDelegateHandle TacticalPointsMaxChangedDelegateHandle;
	virtual void HitPointsChanged(const FOnAttributeChangeData& Data) override;
	virtual void HitPointsMaxChanged(const FOnAttributeChangeData& Data) override;
	virtual void ManaPointsChanged(const FOnAttributeChangeData& Data) override;
	virtual void ManaPointsMaxChanged(const FOnAttributeChangeData& Data);
	virtual void TacticalPointsChanged(const FOnAttributeChangeData& Data) override;
	virtual void TacticalPointsMaxChanged(const FOnAttributeChangeData& Data);
};
