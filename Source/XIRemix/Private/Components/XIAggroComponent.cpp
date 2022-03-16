// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/XIAggroComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SphereComponent.h"
#include "FunctionLibrary/CombatFunctionLibrary.h"
#include "AbilitySystemInterface.h"
#include "Abilities/XIAbilitySystemComponent.h"

// Sets default values for this component's properties
UXIAggroComponent::UXIAggroComponent()
{
	//Setting Default Tick
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	
	// Defining the SphereComponentParameters
	SphereComponent = CreateDefaultSubobject<USphereComponent>("AggroSphere");
	SphereComponent->SetSphereRadius(Range);
	SphereComponent->SetCollisionProfileName(TEXT("TargetSphere"));
	SphereComponent->AreaClass = nullptr;
	SphereComponent->SetCanEverAffectNavigation(false);
	SphereComponent->PrimaryComponentTick.bCanEverTick = false;
	SphereComponent->PrimaryComponentTick.bStartWithTickEnabled = false;
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &UXIAggroComponent::OnOverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &UXIAggroComponent::OnOverlapEnd);
}

// Called when the game starts
void UXIAggroComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerActor = GetOwner();
	if (!OwnerActor)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] XIAggroComponent: Cannot get Owner reference ..."), *GetName());
		return;
	}
	
	IAbilitySystemInterface* AbilityInt = Cast<IAbilitySystemInterface>(OwnerActor);
	
	if(AbilityInt)
	{
		OwnerASC = AbilityInt->GetAbilitySystemComponent();
	}

}

// Called every frame to detect if Hostile Actor is within Aggro Range.
void UXIAggroComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Get the overlapping actors and check if they are within aggro range.
	bool bWithinRange;
	bool bHasGameplayTag;
	bool bIsAlive;

	if ((GetOwnerRole() != ROLE_Authority) | (!HostileActors.IsValidIndex(0)) | !bAggroEnabled)
	{
		SetComponentTickEnabled(false);
		return;
	}

	for (AActor* Actor : HostileActors)
	{
		bWithinRange = UCombatFunctionLibrary::CheckTargetWithinRange(OwnerActor, Actor, Angle, Range);
		bIsAlive = UCombatFunctionLibrary::IsAlive(Actor);
		
		if(!bIsAlive)
		{
			continue;
		}

		// Always Aggro if target is within range!
		if ((EXIAggroType::TrueSense == XIAggroType) & bWithinRange)
		{
			UE_LOG(LogTemp, Warning, TEXT("Truesensed! Broadcasting %s"), *Actor->GetName());
			OnActorDetected.Broadcast(Actor);
			SetAggroMode(false);
			return;
		}
		
		IAbilitySystemInterface* AbilityInt = Cast<IAbilitySystemInterface>(Actor);
		if(AbilityInt)
		{
			HostileASC = AbilityInt->GetAbilitySystemComponent();
			
			//Is hostile target visible and within range?
			bHasGameplayTag = HostileASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Buff.Invisible")));
			if((EXIAggroType::Sight == XIAggroType) & bWithinRange & !bHasGameplayTag)
			{
				UE_LOG(LogTemp, Warning, TEXT("Sight Detection! Broadcasting %s"), *Actor->GetName());
				OnActorDetected.Broadcast(Actor);
				SetAggroMode(false);
				return;
			}

			//Is hostile target not sneaking and within range?
			bHasGameplayTag = HostileASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Buff.Sneak")));
			if((EXIAggroType::Sound == XIAggroType) & bWithinRange & !bHasGameplayTag)
			{
				UE_LOG(LogTemp, Warning, TEXT("Sound Detection! Broadcasting %s"), *Actor->GetName());
				OnActorDetected.Broadcast(Actor);
				SetAggroMode(false);
				return;
			}

			//Is hostile target smelly and within range?
			bHasGameplayTag = HostileASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Buff.Deodorize")));
			if((EXIAggroType::Smell == XIAggroType) & bWithinRange & !bHasGameplayTag)
			{
				UE_LOG(LogTemp, Warning, TEXT("Smell Detection! Broadcasting %s"), *Actor->GetName());
				OnActorDetected.Broadcast(Actor);
				SetAggroMode(false);
				return;
			}
		}
	}
}

void UXIAggroComponent::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if((GetOwnerRole() != ROLE_Authority) | (EXIAggroType::Passive == XIAggroType))
	{
		return;
	}

	if (OtherActor && (OtherActor != OwnerActor) && OtherComp)
	{
		EXITeamAttitude XITeamAttitude = UCombatFunctionLibrary::GetAttitudeTowardsActor(OwnerActor, OtherActor);

		if(XITeamAttitude == EXITeamAttitude::Hostile)
		{
			// Hostile Actor Detected! Enable tick to check if hostile actor is within Aggro range
			HostileActors.Add(OtherActor);
			if(bAggroEnabled)
			{
				UE_LOG(LogTemp, Warning, TEXT("Hostile Actor in CollisonSphere, Enabling Tick for checking if in LoS."));
				SetComponentTickEnabled(true);
				return;
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Neutral/Friendly Actor Detected No action Taken"));
		}
	}
}

void UXIAggroComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if((GetOwnerRole() != ROLE_Authority) | !OtherActor)
	{
		return;
	}
	HostileActors.Remove(OtherActor);
}

void UXIAggroComponent::SetAggroMode(bool bEnableAggro)
{
	bAggroEnabled = bEnableAggro;

	if(bAggroEnabled)
	{
		SetComponentTickEnabled(true);
	}
	else
	{
		SetComponentTickEnabled(false);
	}
}