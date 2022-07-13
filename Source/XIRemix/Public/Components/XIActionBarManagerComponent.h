// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/XIItem.h"
#include "Characters/XICharacterBase.h"
#include "XIActionBarManagerComponent.generated.h"

USTRUCT(BlueprintType)
struct FXIActions
{
	GENERATED_BODY()
 
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<UXIItem*> Items;
};

USTRUCT(BlueprintType)
struct FXIActionBarInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FXIActions> ActionBars;
};

/*
* A component that should be attached to an XICharacterBase. Will store information on items to activate their 'use' functions.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class XIREMIX_API UXIActionBarManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UXIActionBarManagerComponent();

	UFUNCTION(BlueprintPure, Category = "XIActionBarManagerComponent")
	FORCEINLINE FXIActionBarInfo GetXIActionBarInfo() {return ActionBarInfo;}

	UFUNCTION(BlueprintCallable, Category = "XIActionBarManagerComponent")
	FORCEINLINE void SetXIActionBarInfo(FXIActionBarInfo InXIActionBarInfo) {ActionBarInfo = InXIActionBarInfo;}

	UFUNCTION(BlueprintCallable, Category = "XIActionBarManagerComponent")
	void ActivateAction(int32 ActionBarIndex, int32 ActionIndex);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	AXICharacterBase* XICharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FXIActionBarInfo ActionBarInfo;
	
};
