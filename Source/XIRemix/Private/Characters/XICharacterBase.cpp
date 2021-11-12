// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/XICharacterBase.h"
#include "Abilities/GlobalAttributeSet.h"
#include "Abilities/GlobalAbilitySystemComponent.h"
#include "Abilities/GlobalGameplayAbility.h"
#include "Components/CapsuleComponent.h"


// Sets default values
AXICharacterBase::AXICharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bAlwaysRelevant = true;

	// Cache Tags
	// DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Debuff.Dead"));
}

// Called when the game starts or when spawned
void AXICharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AXICharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AXICharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

