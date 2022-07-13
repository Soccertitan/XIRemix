// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AbilityTasks/XIAbilityTask_WaitConfirmTarget.h"
#include "Abilities/XIAbilitySystemComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/PrimitiveComponent.h"
#include "FunctionLibrary/XIGameplayFunctionLibrary.h"
#include "Engine/World.h"

UXIAbilityTask_WaitConfirmTarget::UXIAbilityTask_WaitConfirmTarget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	RegisteredCallbacks = false;

}

void UXIAbilityTask_WaitConfirmTarget::OnConfirmCallback()
{
	
	if (XIASC)
	{
		XIASC->ConsumeGenericReplicatedEvent(EAbilityGenericReplicatedEvent::GenericConfirm, GetAbilitySpecHandle(), GetActivationPredictionKey());
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnConfirm.Broadcast(TargetedActor);
		}
		EndTask();
	}
}

void UXIAbilityTask_WaitConfirmTarget::OnCancelCallback()
{
	if (XIASC)
	{
		XIASC->ConsumeGenericReplicatedEvent(EAbilityGenericReplicatedEvent::GenericCancel, GetAbilitySpecHandle(), GetActivationPredictionKey());
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnCancel.Broadcast(TargetedActor);
		}
		EndTask();
	}
}

void UXIAbilityTask_WaitConfirmTarget::OnLocalConfirmCallback()
{
	FScopedPredictionWindow ScopedPrediction(XIASC, IsPredictingClient());

	if (XIASC && IsPredictingClient())
	{
		XIASC->ServerSetReplicatedEvent(EAbilityGenericReplicatedEvent::GenericConfirm, GetAbilitySpecHandle(), GetActivationPredictionKey() ,XIASC->ScopedPredictionKey);
	}
	OnConfirmCallback();
}

void UXIAbilityTask_WaitConfirmTarget::OnLocalCancelCallback()
{
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent, IsPredictingClient());

	if (XIASC && IsPredictingClient())
	{
		XIASC->ServerSetReplicatedEvent(EAbilityGenericReplicatedEvent::GenericCancel, GetAbilitySpecHandle(), GetActivationPredictionKey() ,XIASC->ScopedPredictionKey);
	}
	OnCancelCallback();
}

UXIAbilityTask_WaitConfirmTarget* UXIAbilityTask_WaitConfirmTarget::WaitConfirmCancel(UGameplayAbility* OwningAbility,
		AActor* InitialTarget,
		EXITeamAttitude XITeamAttitude,
		TSubclassOf<UUserWidget> TargetWidgetClass,
        FVector TargetWidgetRelativeLocation,
        float TargetWidgetDrawSize,
		FName TargetWidgetParentSocket,
		float TargetingRange)
{
    UXIAbilityTask_WaitConfirmTarget* MyObj = NewAbilityTask<UXIAbilityTask_WaitConfirmTarget>(OwningAbility);
	MyObj->TargetingRange = TargetingRange;
    MyObj->TargetWidgetClass = TargetWidgetClass;
    MyObj->TargetWidgetParentSocket = TargetWidgetParentSocket;
    MyObj->TargetWidgetDrawSize = TargetWidgetDrawSize;
    MyObj->TargetWidgetRelativeLocation = TargetWidgetRelativeLocation;
    MyObj->TargetedActor = InitialTarget;
    MyObj->XITeamAttitude = XITeamAttitude;

    return MyObj;
}

void UXIAbilityTask_WaitConfirmTarget::Activate()
{
    XIASC = Cast<UXIAbilitySystemComponent>(AbilitySystemComponent);
	if (XIASC && Ability)
	{
		const FGameplayAbilityActorInfo* Info = Ability->GetCurrentActorInfo();
        
		if (Info->IsLocallyControlled())
		{
			// We have to wait for the callback from the AbilitySystemComponent.
			XIASC->GenericLocalConfirmCallbacks.AddDynamic(this, &UXIAbilityTask_WaitConfirmTarget::OnLocalConfirmCallback);	// Tell me if the confirm input is pressed
			XIASC->GenericLocalCancelCallbacks.AddDynamic(this, &UXIAbilityTask_WaitConfirmTarget::OnLocalCancelCallback);	// Tell me if the cancel input is pressed
            XIASC->OnXICycleTarget.AddDynamic(this, &UXIAbilityTask_WaitConfirmTarget::TargetActor); // Tell me if the input to switch targets is pressed.
            XIASC->XIStartAbilityTargeting();

			RegisteredCallbacks = true;
			Ability->OnWaitingForConfirmInputBegin();
            
            OwnerPawn = Cast<APawn>(Info->AvatarActor);
            SetupLocalPlayerController();
            CameraComponent = OwnerPawn->FindComponentByClass<UCameraComponent>();

            if(XITeamAttitude == UXIGameplayFunctionLibrary::GetAttitudeTowardsActor(OwnerPawn, TargetedActor))
            {
                CreateAndAttachTargetSelectedWidgetComponent(TargetedActor);
            }
            else
            {
                TargetedActor = nullptr;
                TargetActor(1.f);

                if(TargetedActor == nullptr)
                {
                    OnCancelCallback();
                }
            }
		}
		else
		{
			if (CallOrAddReplicatedDelegate(EAbilityGenericReplicatedEvent::GenericConfirm,  FSimpleMulticastDelegate::FDelegate::CreateUObject(this, &UXIAbilityTask_WaitConfirmTarget::OnConfirmCallback)) )
			{
				// GenericConfirm was already received from the client and we just called OnConfirmCallback. The task is done.
				return;
			}
			if (CallOrAddReplicatedDelegate(EAbilityGenericReplicatedEvent::GenericCancel,  FSimpleMulticastDelegate::FDelegate::CreateUObject(this, &UXIAbilityTask_WaitConfirmTarget::OnCancelCallback)) )
			{
				// GenericCancel was already received from the client and we just called OnCancelCallback. The task is done.
				return;
			}
		}
	}
}

void UXIAbilityTask_WaitConfirmTarget::OnDestroy(bool AbilityEnding)
{
	if (RegisteredCallbacks && XIASC)
	{
		XIASC->GenericLocalConfirmCallbacks.RemoveDynamic(this, &UXIAbilityTask_WaitConfirmTarget::OnLocalConfirmCallback);
		XIASC->GenericLocalCancelCallbacks.RemoveDynamic(this, &UXIAbilityTask_WaitConfirmTarget::OnLocalCancelCallback);
        XIASC->OnXICycleTarget.RemoveDynamic(this, &UXIAbilityTask_WaitConfirmTarget::TargetActor);
        XIASC->XIEndAbilityTargeting();

		if (Ability)
		{
			Ability->OnWaitingForConfirmInputEnd();
		}

        if (TargetWidgetComponent)
	    {
		    TargetWidgetComponent->DestroyComponent();
	    }
	}

	Super::OnDestroy(AbilityEnding);
}

void UXIAbilityTask_WaitConfirmTarget::SetupLocalPlayerController()
{
	if (!IsValid(OwnerPawn))
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] Actor is not a pawn."), *GetName());
		return;
	}

	OwnerPlayerController = Cast<APlayerController>(OwnerPawn->GetController());
}

AActor* UXIAbilityTask_WaitConfirmTarget::FindNearestTarget(TArray<AActor*> Actors) const
{
	float ClosestDistance = TargetingRange;
	AActor* Target = nullptr;
	for (AActor* Actor : Actors)
	{
		if(LineTraceForActor(Actor) && IsInViewport(Actor))
		{
			const float Distance = OwnerPawn->GetDistanceTo(Actor);
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

void UXIAbilityTask_WaitConfirmTarget::TargetActor(float Direction)
{
	TArray<AActor *> Actors;
	Actors = GetTargetableActorsFromTrace();
	SwitchTargetActor(Actors, Direction);
}

void UXIAbilityTask_WaitConfirmTarget::SwitchTargetActor(TArray<AActor*> PerceivedActors, float Direction)
{
    if (!TargetedActor)
	{
		TargetedActor = FindNearestTarget(PerceivedActors);
		TargetSelected(TargetedActor);
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
			// Gets the positive/ negative rotation from the source Actor to the next potential targetable Actor.
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
				TargetedActor = RightActor;
				TargetSelected(TargetedActor);
			}
			else if (IsValid(LeftActor))
			{
				TargetedActor = LeftActor;
				TargetSelected(TargetedActor);
			}
		}
		else
		{
			if(IsValid(LeftActor))
			{
				TargetedActor = LeftActor;
				TargetSelected(TargetedActor);
			}
			else if (IsValid(RightActor))
			{
				TargetedActor = RightActor;
				TargetSelected(TargetedActor);
			}
		}
	}
}

void UXIAbilityTask_WaitConfirmTarget::CreateAndAttachTargetSelectedWidgetComponent(AActor* TargetActor)
{
	if (!TargetWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("UXIAbilityTask_WaitConfirmTarget: Cannot get TargetWidgetClass, please ensure it is a valid reference."));
		return;
	}

    if (TargetWidgetComponent)
	{
		TargetWidgetComponent->DestroyComponent();
	}

	TargetWidgetComponent = NewObject<UWidgetComponent>(TargetActor, MakeUniqueObjectName(TargetActor, UWidgetComponent::StaticClass(), FName("TargetLockOn")));
	TargetWidgetComponent->SetWidgetClass(TargetWidgetClass);

	UMeshComponent* MeshComponent = TargetActor->FindComponentByClass<UMeshComponent>();
	USceneComponent* ParentComponent = MeshComponent && TargetWidgetParentSocket != NAME_None ? MeshComponent : TargetActor->GetRootComponent();

	if (IsValid(OwnerPlayerController))
	{
		TargetWidgetComponent->SetOwnerPlayer(OwnerPlayerController->GetLocalPlayer());
	}

	TargetWidgetComponent->ComponentTags.Add(FName("XIAbilityTask.TargetWidget"));
	TargetWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	TargetWidgetComponent->SetupAttachment(ParentComponent, TargetWidgetParentSocket);
	TargetWidgetComponent->SetRelativeLocation(TargetWidgetRelativeLocation);
    TargetWidgetComponent->SetDrawSize(FVector2D(TargetWidgetDrawSize, TargetWidgetDrawSize));
	TargetWidgetComponent->SetVisibility(true);
	TargetWidgetComponent->RegisterComponent();
}

TArray<AActor *> UXIAbilityTask_WaitConfirmTarget::GetTargetableActorsFromTrace() const
{
    TArray<AActor *> Actors;

    if(!OwnerPawn) return Actors;

    TArray<FHitResult> HitResults;

    FCollisionObjectQueryParams ObjectParams;
    ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
    
    FVector Start = OwnerPawn->GetActorLocation();
    FVector End = FVector(0,0,0);

    FCollisionQueryParams Params;

    bool bHitActors = OwnerPawn->GetWorld()->SweepMultiByObjectType(
        HitResults, Start, End, FQuat::Identity, ObjectParams, FCollisionShape::MakeSphere(TargetingRange), Params
    );

    if (bHitActors)
    {
        for(auto& Hit : HitResults)
        {
            AActor* Actor = Hit.GetActor();
            if(XITeamAttitude == UXIGameplayFunctionLibrary::GetAttitudeTowardsActor(OwnerPawn, Actor))
            {
                Actors.AddUnique(Actor);
            }
        }
    }

    return Actors;
}

bool UXIAbilityTask_WaitConfirmTarget::LineTraceForActor(AActor* OtherActor, const TArray<AActor*> ActorsToIgnore) const
{
	if (OtherActor == OwnerPawn)
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

bool UXIAbilityTask_WaitConfirmTarget::LineTrace(FHitResult& HitResult, const AActor* OtherActor, const TArray<AActor*> ActorsToIgnore) const
{
	FCollisionQueryParams Params = FCollisionQueryParams(FName("LineTraceSingle"));

	TArray<AActor*> IgnoredActors;
	IgnoredActors.Init(OwnerPawn, 1);
	IgnoredActors += ActorsToIgnore;

	Params.AddIgnoredActors(IgnoredActors);

    ECollisionChannel TargetableCollisionChannel = ECollisionChannel::ECC_Pawn;
	
	return GetWorld()->LineTraceSingleByChannel(
			HitResult,
			CameraComponent->GetComponentLocation(),
			OtherActor->GetActorLocation(),
			TargetableCollisionChannel,
			Params
		);
}

bool UXIAbilityTask_WaitConfirmTarget::IsInViewport(const AActor* TargetActor) const
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

void UXIAbilityTask_WaitConfirmTarget::TargetSelected(AActor* TargetActor)
{
	if (!IsValid(TargetActor))
	{
		return;
	}
	
    TargetedActor = TargetActor;

	CreateAndAttachTargetSelectedWidgetComponent(TargetActor);
}