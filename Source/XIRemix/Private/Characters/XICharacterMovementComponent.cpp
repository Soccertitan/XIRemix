// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/XICharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "Interfaces/XICharacterInterface.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "Interfaces/AnimBPInterface.h"


UXICharacterMovementComponent::UXICharacterMovementComponent()
{
	bOrientRotationToMovement = true;

}

float UXICharacterMovementComponent::GetMaxSpeed() const
{
	IXICharacterInterface* Owner = Cast<IXICharacterInterface>(GetOwner());
	IAbilitySystemInterface* ASC = Cast<IAbilitySystemInterface>(GetOwner());
	IAnimBPInterface* ABPInt = Cast<IAnimBPInterface>((GetCharacterOwner())->GetMesh()->GetAnimInstance());

	if (!Owner | !ASC | !ABPInt)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Character has not implemented the XICharacterInterface, or AbilitySystemInterface. Or the AnimBP does not implement the AnimBPInterface"), *FString(__FUNCTION__));
		return Super::GetMaxSpeed();
	}

	if (!Owner->IsAlive())
	{
		return 0.0f;
	}

	if (ASC->GetAbilitySystemComponent()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun"))))
	{
		
		return 0.0f;
	}

	if(ABPInt)
	{	
		if ((ABPInt->GetDirection() > 100) | (ABPInt->GetDirection() < -100))
		{
			return (Owner->GetMoveSpeed() / 2);
		}
	}

	return Owner->GetMoveSpeed();
}

void UXICharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);
}

FNetworkPredictionData_Client * UXICharacterMovementComponent::GetPredictionData_Client() const
{
	check(PawnOwner != NULL);

	if (!ClientPredictionData)
	{
		UXICharacterMovementComponent* MutableThis = const_cast<UXICharacterMovementComponent*>(this);

		MutableThis->ClientPredictionData = new FXINetworkPredictionData_Client(*this);
		MutableThis->ClientPredictionData->MaxSmoothNetUpdateDist = 92.f;
		MutableThis->ClientPredictionData->NoSmoothNetUpdateDist = 140.f;
	}

	return ClientPredictionData;
}

void UXICharacterMovementComponent::FXISavedMove::Clear()
{
	Super::Clear();
}

uint8 UXICharacterMovementComponent::FXISavedMove::GetCompressedFlags() const
{
	uint8 Result = Super::GetCompressedFlags();

	return Result;
}

bool UXICharacterMovementComponent::FXISavedMove::CanCombineWith(const FSavedMovePtr & NewMove, ACharacter * Character, float MaxDelta) const
{
	return Super::CanCombineWith(NewMove, Character, MaxDelta);
}

void UXICharacterMovementComponent::FXISavedMove::SetMoveFor(ACharacter * Character, float InDeltaTime, FVector const & NewAccel, FNetworkPredictionData_Client_Character & ClientData)
{
	Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);
}

void UXICharacterMovementComponent::FXISavedMove::PrepMoveFor(ACharacter * Character)
{
	Super::PrepMoveFor(Character);
}

UXICharacterMovementComponent::FXINetworkPredictionData_Client::FXINetworkPredictionData_Client(const UCharacterMovementComponent & ClientMovement)
	: Super(ClientMovement)
{
}

FSavedMovePtr UXICharacterMovementComponent::FXINetworkPredictionData_Client::AllocateNewMove()
{
	return FSavedMovePtr(new FXISavedMove());
}