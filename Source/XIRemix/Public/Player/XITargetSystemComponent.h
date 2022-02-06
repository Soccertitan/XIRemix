// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "XIEnums.h"
#include "XITargetSystemComponent.generated.h"

class UUserWidget;
class UWidgetComponent;
class APlayerController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FComponentOnTargetModified, AActor*, TargetActor);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class XIREMIX_API UXITargetSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UXITargetSystemComponent();

	// The minimum distance to remove targeted actor.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System")
	float MinimumDistanceToEnable = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System")
	TEnumAsByte<ECollisionChannel> TargetableCollisionChannel;

	// The amount of time to break line of sight when actor gets behind an Object.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System")
	float BreakLineOfSightDelay = 2.0f;

	// Whether to accept pitch input when bAdjustPitchBasedOnDistanceToTarget is disabled
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System")
	bool bIgnoreLookInput = true;

	// The Widget Class to use when locked on Target. If not defined, will fallback to a Text-rendered
	// widget with a single O character.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System|Widget")
	TSubclassOf<UUserWidget> LockedOnWidgetClass;

	// // The Widget Draw Size for the Widget class to use when locked on Target.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System|Widget")
	float LockedOnWidgetDrawSize = 32.0f;

	// The Socket name to attach the LockedOn Widget.
	//
	// You should use this to configure the Bone or Socket name the widget should be attached to, and allow
	// the widget to move with target character's animation (Ex: spine_03)
	//
	// Set it to None to attach the Widget Component to the Root Component instead of the Mesh.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System|Widget")
	FName LockedOnWidgetParentSocket = FName("spine_03");

	// // The Relative Location to apply on Target LockedOn Widget when attached to a target.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System|Widget")
	FVector LockedOnWidgetRelativeLocation = FVector(0.0f, 0.0f, 0.0f);

	// Setting this to true will tell the Target System to adjust the Pitch Offset (the Y axis) when locked on,
	// depending on the distance to the target actor.
	//
	// It will ensure that the Camera will be moved up vertically the closer this Actor gets to its target.
	//
	// Formula:
	//
	//   (DistanceToTarget * PitchDistanceCoefficient + PitchDistanceOffset) * -1.0f
	//
	// Then Clamped by PitchMin / PitchMax
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System|Pitch Offset")
	bool bAdjustPitchBasedOnDistanceToTarget = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System|Pitch Offset")
	float PitchDistanceCoefficient = -0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System|Pitch Offset")
	float PitchDistanceOffset = 60.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System|Pitch Offset")
	float PitchMin = -50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System|Pitch Offset")
	float PitchMax = -20.0f;

	UPROPERTY(EditAnywhere, Category = "Target System|Sphere")
	USphereComponent* SphereComponent;

	UFUNCTION(BlueprintCallable, Category = "Target System")
	void TargetActor(EXITeamAttitude XIAttitude, float Direction);

	// Function to call to lock the camera and rotation.
	UFUNCTION(BlueprintCallable, Category = "Target System")
	void LockCamera();

	// Function to call to deselect the Targeted Actor.
	UFUNCTION(BlueprintCallable, Category = "Target System")
	void RemoveTargetedActor();

	// Switches to the next target on the right if float is positive.
	UFUNCTION(BlueprintCallable, Category = "Target System")
	void SwitchTargetActor(TArray<AActor*> PerceivedActors, float Direction);

	// Gets overlapping Actors from SphereComponent
	UFUNCTION(BlueprintCallable, Category = "Target System")
	TArray<AActor *> GetXIOverlappingActors() const;

	// Called when a target is deslected, either if it is out of reach (based on MinimumDistanceToEnable) or behind an Object.
	UPROPERTY(BlueprintAssignable, Category = "Target System")
	FComponentOnTargetModified OnTargetRemoved;

	// Called when a target is selected.
	UPROPERTY(BlueprintAssignable, Category = "Target System")
	FComponentOnTargetModified OnTargetSelected;

	// Returns the reference to currently targeted Actor if any
	UFUNCTION(BlueprintCallable, Category = "Target System")
	AActor* GetTargetedActor() const;

private:
	UPROPERTY()
	AActor* OwnerActor;

	UPROPERTY()
	APawn* OwnerPawn;

	UPROPERTY()
	APlayerController* OwnerPlayerController;

	UPROPERTY()
	UCameraComponent* CameraComponent;

	UPROPERTY()
	UWidgetComponent* TargetWidgetComponent;

	UPROPERTY()
	AActor* TargetedActor;

	FTimerHandle LineOfSightBreakTimerHandle;

	bool bIsBreakingLineOfSight = false;
	bool bCameraLocked = false;
	float ClosestTargetDistance = 0.0f;

	//~ Actors search / trace

	AActor* FindNearestTarget(TArray<AActor*> Actors) const;

	bool LineTrace(FHitResult& HitResult, const AActor* OtherActor, TArray<AActor*> ActorsToIgnore = TArray<AActor*>()) const;
	bool LineTraceForActor(AActor* OtherActor, TArray<AActor*> ActorsToIgnore = TArray<AActor*>()) const;

	bool ShouldBreakLineOfSight() const;
	void BreakLineOfSight();

	bool IsInViewport(const AActor* TargetActor) const;
	float GetDistanceFromCharacter(const AActor* OtherActor) const;

	//~ Actor rotation

	FRotator GetControlRotationOnTarget(const AActor* OtherActor) const;
	void SetControlRotationOnTarget(AActor* TargetActor) const;
	void ControlRotation(bool ShouldControlRotation) const;

	UFUNCTION(Server, WithValidation, UnReliable)
	void Server_SetActorRotation(AActor* TargetActor, FRotator ActorRotation);
	bool Server_SetActorRotation_Validate(AActor* TargetActor, FRotator ActorRotation);
	void Server_SetActorRotation_Implementation(AActor* TargetActor, FRotator ActorRotation);

	//~ Targeting
	void TargetSelected(AActor* TargetActor);

	// //~ Widget

	void CreateAndAttachTargetSelectedWidgetComponent(AActor* TargetActor);

	/**
	 *  Sets up cached Owner PlayerController from Owner Pawn.
	 *
	 *  For local split screen, Pawn's Controller may not have been setup already when this component begins play.
	 */
	 void SetupLocalPlayerController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
