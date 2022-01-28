// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/XIAggroComponent.h"
#include "Components/SphereComponent.h"
#include "FunctionLibrary/CombatFunctionLibrary.h"
#include "AbilitySystemInterface.h"
#include "Abilities/XIAbilitySystemComponent.h"

// Sets default values for this component's properties
UXIAggroComponent::UXIAggroComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	
	// Defining the SphereComponentParameters
	SphereComponent = CreateDefaultSubobject<USphereComponent>("AggroSphere");
	SphereComponent->SetSphereRadius(Range);
	SphereComponent->SetCollisionProfileName(TEXT("TargetSphere"));
	SphereComponent->AreaClass = nullptr;
	SphereComponent->SetCanEverAffectNavigation(false);
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

	SphereComponent->AttachToComponent(OwnerActor->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);	
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

	if (!HostileActors.IsValidIndex(0))
	{
		SetComponentTickEnabled(false);
		return;
	}

	for (AActor* Actor : HostileActors)
	{
		bWithinRange = UCombatFunctionLibrary::CheckTargetWithinRange(OwnerActor, Actor, Angle, Range);
		
		// Always Aggro if target is within range!
		if ((EXIAggroType::TrueSense == XIAggroType) & bWithinRange)
		{
			// TODO: Start Implementing Start combat functions!
			UE_LOG(LogTemp, Warning, TEXT("Start Combat with %s"), *Actor->GetName());
			SetComponentTickEnabled(false);
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
				// Start Implementing Start combat functions!
				UE_LOG(LogTemp, Warning, TEXT("Sight Detection! Start Combat with %s"), *Actor->GetName());
				SetComponentTickEnabled(false);
				return;
			}

			//Is hostile target not sneaking and within range?
			bHasGameplayTag = HostileASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Buff.Sneak")));
			if((EXIAggroType::Sound == XIAggroType) & bWithinRange & !bHasGameplayTag)
			{
				// Start Implementing Start combat functions!
				UE_LOG(LogTemp, Warning, TEXT("Sound Detection! Start Combat with %s"), *Actor->GetName());
				SetComponentTickEnabled(false);
				return;
			}

			//Is hostile target smelly and within range?
			bHasGameplayTag = HostileASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Buff.Deodorize")));
			if((EXIAggroType::Smell == XIAggroType) & bWithinRange & !bHasGameplayTag)
			{
				// Start Implementing Start combat functions!
				UE_LOG(LogTemp, Warning, TEXT("Smell Detection! Start Combat with %s"), *Actor->GetName());
				SetComponentTickEnabled(false);
				return;
			}
		}
	}
}

void UXIAggroComponent::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Also want to check if the OwnerActor is in Combat. If it is return immediately.
	// OwnerASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Gameplay.InCombat"))) Where should this go??

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
			SetComponentTickEnabled(true);
			return;
		}
		
		UE_LOG(LogTemp, Warning, TEXT("Neutral/Friendly Actor Detected No action Taken"));
	}
}

void UXIAggroComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(!OtherActor)
	{
		return;
	}
	HostileActors.Remove(OtherActor);
}