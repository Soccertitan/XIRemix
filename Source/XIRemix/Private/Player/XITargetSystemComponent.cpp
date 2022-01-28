// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/XITargetSystemComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SphereComponent.h"
#include "EngineUtils.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/Public/TimerManager.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UXITargetSystemComponent::UXITargetSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	LockedOnWidgetClass = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("WidgetBlueprint'/Game/XIRemix/Core/Player/UI/WBP_TargetDot.WBP_TargetDot_C'"));
	TargetableCollisionChannel = ECollisionChannel::ECC_Pawn;

	// Defining the SphereComponentParameters
	SphereComponent = CreateDefaultSubobject<USphereComponent>("XITargetSphere");
	SphereComponent->SetSphereRadius(MinimumDistanceToEnable);
	SphereComponent->SetCollisionProfileName(TEXT("TargetSphere"));
	SphereComponent->AreaClass = nullptr;
	SphereComponent->SetCanEverAffectNavigation(false);
	SphereComponent->PrimaryComponentTick.bCanEverTick = false;
	SphereComponent->PrimaryComponentTick.bStartWithTickEnabled = false;
}


// Called when the game starts
void UXITargetSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerActor = GetOwner();
	if (!OwnerActor)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] TargetSystemComponent: Cannot get Owner reference ..."), *GetName());
		return;
	}

	OwnerPawn = Cast<APawn>(OwnerActor);
	if (!ensure(OwnerPawn))
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] TargetSystemComponent: Component is meant to be added to Pawn only ..."), *GetName());
		return;
	}

	CameraComponent = OwnerActor->FindComponentByClass<UCameraComponent>();
	if(!IsValid(CameraComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] TargetSystemComponent: Cannot get the Camera component for ..."), *GetName());
		return;
	}

	SphereComponent->AttachToComponent(OwnerActor->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	SetupLocalPlayerController();
	
}


// Called every frame
void UXITargetSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!TargetedActor)
	{
		return;
	}

	if (bCameraLocked)
	{
		SetControlRotationOnTarget(TargetedActor);
		Server_SetActorRotation(OwnerActor, OwnerActor->GetActorRotation());
	}
	
	if (GetDistanceFromCharacter(TargetedActor) > MinimumDistanceToEnable)
	{
		RemoveTargetedActor();
	}

	if (ShouldBreakLineOfSight() && !bIsBreakingLineOfSight)
	{
		if (BreakLineOfSightDelay <= 0)
		{
			RemoveTargetedActor();
		}
		else
		{
			bIsBreakingLineOfSight = true;
			GetWorld()->GetTimerManager().SetTimer(
				LineOfSightBreakTimerHandle,
				this,
				&UXITargetSystemComponent::BreakLineOfSight,
				BreakLineOfSightDelay
			);
		}
	}

}

void UXITargetSystemComponent::TargetActor(TArray<AActor*> PerceivedActors)
{
	if(!TargetedActor)
	{
		TargetedActor = FindNearestTarget(PerceivedActors);
		TargetSelected(TargetedActor);
	}
}

void UXITargetSystemComponent::SwitchTargetActor(TArray<AActor*> PerceivedActors, float Direction)
{
	if (!TargetedActor)
	{
		TargetActor(PerceivedActors);
		return;
	}

	if(!IsValid(TargetedActor))
	{
		return;
	}

	FVector ReferenceLocation = CameraComponent->GetComponentLocation();
	FVector ReferenceActor = TargetedActor->GetActorLocation();
	FVector2D ReferenceVector = {ReferenceActor.X - ReferenceLocation.X , ReferenceActor.Y - ReferenceLocation.Y};
	ReferenceVector.Normalize();

	float RightComparison;
	float LeftComparison; 
	float ZRotation;
	AActor* RightActor = nullptr;
	AActor* LeftActor = nullptr;

	// // Initialize Comparison values for cycling targets to the Right if true.
	if(Direction > 0)
	{
		RightComparison = 180.f;
		LeftComparison = 0.f;
	}
	else
	{
		RightComparison = 0.f;
		LeftComparison = -180.f;
	}

	for (AActor* Actor : PerceivedActors)
	{
		if(LineTraceForActor(Actor) && IsInViewport(Actor))
		{
			// Gets the positive/ negative rotation from the source Actor to the next potentail targetable Actor.
			FVector ActorLocation = Actor->GetActorLocation();
			FVector2D ComparisonActorVector = {ActorLocation.X - ReferenceLocation.X , ActorLocation.Y - ReferenceLocation.Y};
			ComparisonActorVector.Normalize();

			ZRotation = FMath::RadiansToDegrees(FGenericPlatformMath::Acos(FVector2D::DotProduct(ReferenceVector, ComparisonActorVector))) * FMath::Sign(FVector2D::CrossProduct(ReferenceVector, ComparisonActorVector));

			// Get the target closest to the right and furthest from the left of the original target if we choose targets to the right.
			if(Direction > 0)
			{
				if (ZRotation > 0 && ZRotation < RightComparison)
				{
					RightComparison = ZRotation;
					RightActor = Actor;
				}
				else if (ZRotation < 0 && ZRotation < LeftComparison)
				{
					LeftComparison = ZRotation;
					LeftActor = Actor;
				}
			}
			else
			{
				if (ZRotation > 0 && ZRotation > RightComparison)
				{
					RightComparison = ZRotation;
					RightActor = Actor;
				}
				else if (ZRotation < 0 && ZRotation > LeftComparison)
				{
					LeftComparison = ZRotation;
					LeftActor = Actor;
				}
			}
		}
	}
	
	if (IsValid(RightActor) | IsValid(LeftActor))
	{
		// Selects targets to the right if true. 
		if(Direction > 0)
		{
			if(IsValid(RightActor))
			{
				RemoveTargetedActor();
				TargetedActor = RightActor;
				TargetSelected(TargetedActor);
			}
			else if (IsValid(LeftActor))
			{
				RemoveTargetedActor();
				TargetedActor = LeftActor;
				TargetSelected(TargetedActor);
			}
		}
		else
		{
			if(IsValid(LeftActor))
			{
				RemoveTargetedActor();
				TargetedActor = LeftActor;
				TargetSelected(TargetedActor);
			}
			else if (IsValid(RightActor))
			{
				RemoveTargetedActor();
				TargetedActor = RightActor;
				TargetSelected(TargetedActor);
			}
		}
	}
}

AActor* UXITargetSystemComponent::GetTargetedActor() const
{
	return TargetedActor;
}

TArray<AActor *> UXITargetSystemComponent::GetXIOverlappingActors() const
{
	TArray<AActor *> Actors;
	SphereComponent->GetOverlappingActors(Actors);
	return Actors;
}

AActor* UXITargetSystemComponent::FindNearestTarget(TArray<AActor*> Actors) const
{
	float ClosestDistance = MinimumDistanceToEnable;
	AActor* Target = nullptr;
	for (AActor* Actor : Actors)
	{
		if(LineTraceForActor(Actor) && IsInViewport(Actor))
		{
			const float Distance = GetDistanceFromCharacter(Actor);
			if (Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				Target = Actor;
			}
		}
	}
	
	if(IsValid(Target))
	{
		return Target;
	}
	return nullptr;
}

void UXITargetSystemComponent::SetupLocalPlayerController()
{
	if (!IsValid(OwnerPawn))
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] TargetSystemComponent: Component is meant to be added to Pawn only ..."), *GetName());
		return;
	}

	OwnerPlayerController = Cast<APlayerController>(OwnerPawn->GetController());
}

float UXITargetSystemComponent::GetDistanceFromCharacter(const AActor* OtherActor) const
{
	return OwnerActor->GetDistanceTo(OtherActor);
}

void UXITargetSystemComponent::LockCamera()
{
	// Recast PlayerController in case it wasn't already setup on Begin Play (local split screen)
	SetupLocalPlayerController();

	if (!TargetedActor)
	{
		if (IsValid(OwnerPlayerController))
		{
			OwnerPlayerController->ResetIgnoreLookInput();
		}
		ControlRotation(false);
		bCameraLocked = false;
	}
	else if ((TargetedActor != OwnerActor) && !bCameraLocked)
	{
		if (bAdjustPitchBasedOnDistanceToTarget || bIgnoreLookInput)
		{
			if (IsValid(OwnerPlayerController))
			{
				OwnerPlayerController->SetIgnoreLookInput(true);
			}
		}
		ControlRotation(true);
		bCameraLocked = true;
	}
	else if (TargetedActor && bCameraLocked)
	{
		if (IsValid(OwnerPlayerController))
		{
			OwnerPlayerController->ResetIgnoreLookInput();
		}
		ControlRotation(false);
		bCameraLocked = false;
	}
}

void UXITargetSystemComponent::CreateAndAttachTargetSelectedWidgetComponent(AActor* TargetActor)
{
	if (!LockedOnWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("TargetSystemComponent: Cannot get LockedOnWidgetClass, please ensure it is a valid reference in the Component Properties."));
		return;
	}

	TargetWidgetComponent = NewObject<UWidgetComponent>(TargetActor, MakeUniqueObjectName(TargetActor, UWidgetComponent::StaticClass(), FName("TargetLockOn")));
	TargetWidgetComponent->SetWidgetClass(LockedOnWidgetClass);

	UMeshComponent* MeshComponent = TargetActor->FindComponentByClass<UMeshComponent>();
	USceneComponent* ParentComponent = MeshComponent && LockedOnWidgetParentSocket != NAME_None ? MeshComponent : TargetActor->GetRootComponent();

	if (IsValid(OwnerPlayerController))
	{
		TargetWidgetComponent->SetOwnerPlayer(OwnerPlayerController->GetLocalPlayer());
	}

	TargetWidgetComponent->ComponentTags.Add(FName("TargetSystem.LockOnWidget"));
	TargetWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	TargetWidgetComponent->SetupAttachment(ParentComponent, LockedOnWidgetParentSocket);
	TargetWidgetComponent->SetRelativeLocation(LockedOnWidgetRelativeLocation);
	TargetWidgetComponent->SetDrawSize(FVector2D(LockedOnWidgetDrawSize, LockedOnWidgetDrawSize));
	TargetWidgetComponent->SetVisibility(true);
	TargetWidgetComponent->RegisterComponent();
}

bool UXITargetSystemComponent::IsInViewport(const AActor* TargetActor) const
{
	if (!IsValid(OwnerPlayerController))
	{
		return true;
	}

	FVector2D ScreenLocation;
	bool bWorldLocation = OwnerPlayerController->ProjectWorldLocationToScreen(TargetActor->GetActorLocation(), ScreenLocation);

	FVector2D ViewportSize;
	GetWorld()->GetGameViewport()->GetViewportSize(ViewportSize);

	return ScreenLocation.X > 0 && ScreenLocation.Y > 0 && ScreenLocation.X < ViewportSize.X && ScreenLocation.Y < ViewportSize.Y && bWorldLocation;
}

bool UXITargetSystemComponent::LineTraceForActor(AActor* OtherActor, const TArray<AActor*> ActorsToIgnore) const
{
	if (OtherActor == OwnerActor)
	{
		return true;
	}

	FHitResult HitResult;
	const bool bHit = LineTrace(HitResult, OtherActor, ActorsToIgnore);
	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor == OtherActor)
		{
			return true;
		}
	}

	return false;
}

bool UXITargetSystemComponent::LineTrace(FHitResult& HitResult, const AActor* OtherActor, const TArray<AActor*> ActorsToIgnore) const
{
	FCollisionQueryParams Params = FCollisionQueryParams(FName("LineTraceSingle"));

	TArray<AActor*> IgnoredActors;
	IgnoredActors.Init(OwnerActor, 1);
	IgnoredActors += ActorsToIgnore;

	Params.AddIgnoredActors(IgnoredActors);
	
	return GetWorld()->LineTraceSingleByChannel(
			HitResult,
			CameraComponent->GetComponentLocation(),
			OtherActor->GetActorLocation(),
			TargetableCollisionChannel,
			Params
		);
}

bool UXITargetSystemComponent::ShouldBreakLineOfSight() const
{
	if (!TargetedActor)
	{
		return true;
	}

	// Get the sphere collider to get all actors.
	TArray<AActor*> ActorsToIgnore;
	SphereComponent->GetOverlappingActors(ActorsToIgnore);
	ActorsToIgnore.Remove(TargetedActor);

	FHitResult HitResult;
	const bool bHit = LineTrace(HitResult, TargetedActor, ActorsToIgnore);
	if (bHit && HitResult.GetActor() != TargetedActor)
	{
		return true;
	}

	return false;
}

void UXITargetSystemComponent::BreakLineOfSight()
{
	bIsBreakingLineOfSight = false;
	if (ShouldBreakLineOfSight())
	{
		RemoveTargetedActor();
	}
}

void UXITargetSystemComponent::TargetSelected(AActor* TargetActor)
{
	if (!IsValid(TargetActor))
	{
		return;
	}
	
	CreateAndAttachTargetSelectedWidgetComponent(TargetActor);

	if (OnTargetSelected.IsBound())
	{
		OnTargetSelected.Broadcast(TargetActor);
	}
}

void UXITargetSystemComponent::RemoveTargetedActor()
{
	if (TargetWidgetComponent)
	{
		TargetWidgetComponent->DestroyComponent();
	}

	if (TargetedActor)
	{
		if (OnTargetRemoved.IsBound())
		{
			OnTargetRemoved.Broadcast(TargetedActor);
		}
	}
	TargetedActor = nullptr;
	LockCamera();
}

#pragma region ActorRotation

void UXITargetSystemComponent::SetControlRotationOnTarget(AActor* TargetActor) const
{
	if (!IsValid(OwnerPlayerController))
	{
		return;
	}

	const FRotator ControlRotation = GetControlRotationOnTarget(TargetActor);
	OwnerPlayerController->SetControlRotation(ControlRotation);
}

FRotator UXITargetSystemComponent::GetControlRotationOnTarget(const AActor* OtherActor) const
{
	if (!IsValid(OwnerPlayerController))
	{
		UE_LOG(LogTemp, Warning, TEXT("UTargetSystemComponent::GetControlRotationOnTarget - OwnerPlayerController is not valid ..."))
		return FRotator::ZeroRotator;
	}

	const FRotator ControlRotation = OwnerPlayerController->GetControlRotation();

	const FVector CharacterLocation = OwnerActor->GetActorLocation();
	const FVector OtherActorLocation = OtherActor->GetActorLocation();

	// Find look at rotation
	const FRotator LookRotation = FRotationMatrix::MakeFromX(OtherActorLocation - CharacterLocation).Rotator();
	float Pitch = LookRotation.Pitch;
	FRotator TargetRotation;
	if (bAdjustPitchBasedOnDistanceToTarget)
	{
		const float DistanceToTarget = GetDistanceFromCharacter(OtherActor);
		const float PitchInRange = (DistanceToTarget * PitchDistanceCoefficient + PitchDistanceOffset) * -1.0f;
		const float PitchOffset = FMath::Clamp(PitchInRange, PitchMin, PitchMax);

		Pitch = Pitch + PitchOffset;
		TargetRotation = FRotator(Pitch, LookRotation.Yaw, ControlRotation.Roll);
	}
	else
	{
		if (bIgnoreLookInput)
		{
			TargetRotation = FRotator(Pitch, LookRotation.Yaw, ControlRotation.Roll);
		}
		else
		{
			TargetRotation = FRotator(ControlRotation.Pitch, LookRotation.Yaw, ControlRotation.Roll);
		}
	}

	return FMath::RInterpTo(ControlRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 9.0f);
}

void UXITargetSystemComponent::ControlRotation(const bool ShouldControlRotation) const
{
	if (!IsValid(OwnerPawn))
	{
		return;
	}

	OwnerPawn->bUseControllerRotationYaw = ShouldControlRotation;

	UCharacterMovementComponent* CharacterMovementComponent = OwnerPawn->FindComponentByClass<UCharacterMovementComponent>();
	if (CharacterMovementComponent)
	{
		CharacterMovementComponent->bOrientRotationToMovement = !ShouldControlRotation;
	}
}

bool UXITargetSystemComponent::Server_SetActorRotation_Validate(AActor* TargetActor, FRotator ActorRotation)
{
	if (TargetActor)
	{
		return true;
	}
	return false;
}

void UXITargetSystemComponent::Server_SetActorRotation_Implementation(AActor* TargetActor, FRotator ActorRotation)
{
	TargetActor->SetActorRotation(FMath::RInterpTo((TargetActor->GetActorRotation()), ActorRotation, 1, 2));
}

#pragma endregion ActorRotation

