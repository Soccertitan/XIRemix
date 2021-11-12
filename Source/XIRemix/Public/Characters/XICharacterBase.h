// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "XICharacterBase.generated.h"

UCLASS()
class XIREMIX_API AXICharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AXICharacterBase();

	// UPROPERTY(BlueprintAssignable, Category = "XICharacter")
	// FCharacterDiedDelegate OnCharacterDied;

	// Implement IAbilitySystemInterface
	// virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// UFUNCTION(BlueprintCallable, Category = "XICharacter")
	// virtual bool IsAlive() const;

	// // Removes all CharacterAbilities. Can only be called by the Server. Removing on the Server will remove from Client too.
	// virtual void RemoveCharacterAbilities();


	// /**
	// * Getters for attributes from GDAttributeSetBase
	// **/	
	// UFUNCTION(BlueprintCallable, Category = "XICharacter|Attributes")
	// int32 GetCharacterLevel() const;

	// UFUNCTION(BlueprintCallable, Category = "XICharacter|Attributes")
	// float GetHealth() const;

	// UFUNCTION(BlueprintCallable, Category = "XICharacter|Attributes")
	// float GetMaxHealth() const;

	// UFUNCTION(BlueprintCallable, Category = "XICharacter|Attributes")
	// float GetMana() const;

	// UFUNCTION(BlueprintCallable, Category = "XICharacter|Attributes")
	// float GetMaxMana() const;

	// UFUNCTION(BlueprintCallable, Category = "XICharacter|Attributes")
	// float GetTacticalPoints() const;

	// UFUNCTION(BlueprintCallable, Category = "XICharacter|Attributes")
	// float GetMaxTacticalPoints() const;
	
	// // Gets the Current value of MoveSpeed
	// UFUNCTION(BlueprintCallable, Category = "XICharacter|Attributes")
	// float GetMoveSpeed() const;

	// // Gets the Base value of MoveSpeed
	// UFUNCTION(BlueprintCallable, Category = "XICharacter|Attributes")
	// float GetMoveSpeedBaseValue() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// FGameplayTag DeadTag;
	// FGameplayTag EffectRemoveOnDeathTag;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XICharacter")
	FText CharacterName;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
