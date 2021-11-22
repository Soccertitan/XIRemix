// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AttributeSetGlobal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSetEnemy.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class XIREMIX_API UAttributeSetEnemy : public UAttributeSetGlobal
{
	GENERATED_BODY()

public:

	UAttributeSetEnemy();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Enemy", ReplicatedUsing = OnRep_Level)
	FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(UAttributeSetEnemy, Level);
	UFUNCTION()
	virtual void OnRep_Level(const FGameplayAttributeData& OldLevel);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Enemy", ReplicatedUsing = OnRep_ExpBounty)
	FGameplayAttributeData ExpBounty;
	ATTRIBUTE_ACCESSORS(UAttributeSetEnemy, ExpBounty);
	UFUNCTION()
	virtual void OnRep_ExpBounty(const FGameplayAttributeData& OldExpBounty);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Enemy", ReplicatedUsing = OnRep_GilBounty)
	FGameplayAttributeData GilBounty;
	ATTRIBUTE_ACCESSORS(UAttributeSetEnemy, GilBounty);
	UFUNCTION()
	virtual void OnRep_GilBounty(const FGameplayAttributeData& OldGilBounty);

};
