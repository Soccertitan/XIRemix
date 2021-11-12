// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "XIPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API AXIPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AXIPlayerState();

	// Implement IAbilitySystemInterface
	class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	class UHeroAttributeSet* GetAttributeSet() const;

protected:
	UPROPERTY()
	class UGlobalAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	class UHeroAttributeSet* AttributeSetHero;

	FGameplayTag DeadTag;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
