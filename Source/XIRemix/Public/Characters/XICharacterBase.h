// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameplayEffectTypes.h"
#include "XICharacterBase.generated.h"

UCLASS()
class XIREMIX_API AXICharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AXICharacterBase(const class FObjectInitializer& ObjectInitializer);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// UPROPERTY(BlueprintAssignable, Category = "XICharacter")
	// FCharacterDiedDelegate OnCharacterDied;

	// Implement IAbilitySystemInterface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "XICharacter")
	virtual bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "XICharacter|Name")
	FText GetCharacterName() const;

	// // Removes all CharacterAbilities. Can only be called by the Server. Removing on the Server will remove from Client too.
	// virtual void RemoveCharacterAbilities();

	// /**
	// * Getters for attributes from GlobalAttributeSet
	// **/
	UFUNCTION(BlueprintCallable, Category = "XICharacter|Attributes")
	float GetHitPoints() const;

	UFUNCTION(BlueprintCallable, Category = "XICharacter|Attributes")
	float GetHitPointsMax() const;

	UFUNCTION(BlueprintCallable, Category = "XICharacter|Attributes")
	float GetManaPoints() const;

	UFUNCTION(BlueprintCallable, Category = "XICharacter|Attributes")
	float GetManaPointsMax() const;

	UFUNCTION(BlueprintCallable, Category = "XICharacter|Attributes")
	float GetTacticalPoints() const;

	UFUNCTION(BlueprintCallable, Category = "XICharacter|Attributes")
	float GetTacticalPointsMax() const;
	
	// // Gets the Current value of MoveSpeed
	UFUNCTION(BlueprintCallable, Category = "XICharacter|Attributes")
	float GetMoveSpeed() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Replicated, Category = "XICharacter")
	FText CharacterName;

	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = "XICharacter|Name")
	void Server_SetCharacterName(const FText &Name);
	bool Server_SetCharacterName_Validate(FText Name);
	void Server_SetCharacterName_Implementation(FText Name);

	UPROPERTY()
	class UAbilitySystemComponentGlobal* AbilitySystemComponent;
	UPROPERTY()
	class UAttributeSetGlobal* AttributeSet;

	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	FDelegateHandle HitPointsChangedDelegateHandle;
	FDelegateHandle HitPointsMaxChangedDelegateHandle;

	// Attribute Change Callbacks
	virtual void HitPointsChanged(const FOnAttributeChangeData& Data);
	virtual void HitPointsMaxChanged(const FOnAttributeChangeData& Data);

	// Default abilities for this Character. These will be removed on Character death and regiven if Character respawns.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XICharacter|Abilities")
	TArray<TSubclassOf<class UGameplayAbilityGlobal>> CharacterAbilities;

	// Default attributes for a character for initializing on spawn/respawn.
	// This is an instant GE that overrides the values for attributes that get reset on spawn/respawn.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XICharacter|Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	// These effects are only applied one time on startup
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XICharacter|Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	// Initialize the Character's attributes. Must run on Server but we run it on Client too
	// so that we don't have to wait. The Server's replication to the Client won't matter since
	// the values should be the same.
	virtual void InitializeAttributes();

	virtual void AddStartupEffects();

};