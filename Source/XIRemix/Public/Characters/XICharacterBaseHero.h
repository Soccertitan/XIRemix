// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/XICharacterBase.h"
#include "Components/SphereComponent.h"
#include "FunctionLibrary/MeshMergeFunctionLibrary.h"
#include "Player/XITargetSystemComponent.h"
#include "XICharacterBaseHero.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API AXICharacterBaseHero : public AXICharacterBase
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

	// /**
	// * Getters for attributes from AttributeSetHero
	// **/
	UFUNCTION(BlueprintCallable, Category = "XICharacter|Attributes|Jobs")
	float GetWarriorLevel() const;

protected:
	
	UPROPERTY()
	class UAttributeSetHero* AttributeSetHero;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "XICharacter|MeshMerge")
	FSkeletalMeshMergeParams SKMeshMergeParams;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "XICharacter|MeshMerge")
	TMap <ESkeletalMeshMergeType, int32> SKMeshMergeMap;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Client only
	virtual void OnRep_PlayerState() override;	
};
