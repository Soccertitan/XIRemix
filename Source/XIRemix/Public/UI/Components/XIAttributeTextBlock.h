// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "XIAttributeTextBlock.generated.h"

/**
 * Sets the number of the text block based on the Attribute specified.
 */
UCLASS()
class XIREMIX_API UXIAttributeTextBlock : public UTextBlock
{
	GENERATED_BODY()
	
public:

	UXIAttributeTextBlock();

	//Gets the Actors Ability System Component and binds delegates to the attribute changes.
	UFUNCTION(BlueprintCallable, Category = "XIAttributeTextBlock")
	bool SetupAttributeCallback(AActor* Actor);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XIAttributeTextBlock")
	FGameplayAttribute ValueAttribute;

	FNumberFormattingOptions FormatOptions;

	UPROPERTY(EditAnywhere, Category = "XIAttributeTextBlock|Format")
	int32 MaxFractionalDigits;

	UPROPERTY(BlueprintReadOnly, Category = "XIAttributeTextBlock")
	AActor* TargetActor;

	UPROPERTY(BlueprintReadOnly, Category = "XIAttributeTextBlock")
	float Value;

	UPROPERTY(BlueprintReadOnly, Category = "XIAttributeTextBlock")
	UAbilitySystemComponent* ASC;

	// Attribute delegates
	FDelegateHandle ValueChangedDelegateHandle;
	virtual void ValueChanged(const FOnAttributeChangeData& Data);

	void SetValueText();
};
