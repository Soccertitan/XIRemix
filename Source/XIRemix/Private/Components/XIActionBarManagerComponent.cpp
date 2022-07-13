// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/XIActionBarManagerComponent.h"

// Sets default values for this component's properties
UXIActionBarManagerComponent::UXIActionBarManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UXIActionBarManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	XICharacter = Cast<AXICharacterBase>(GetOwner());

	if(!XICharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("UXIActionBarManagerComponent: %s is not AXICharacterBase!"), *GetNameSafe(GetOwner()));
	}

	if(!GetOwner()->HasAuthority())
	{
		ActionBarInfo.ActionBars.SetNum(3);
		for(auto& Action : ActionBarInfo.ActionBars)
		{
			Action.Items.SetNum(16);
		}
	}
}

void UXIActionBarManagerComponent::ActivateAction(int32 ActionBarIndex, int32 ActionIndex)
{
	if(ActionBarInfo.ActionBars.IsValidIndex(ActionBarIndex) && ActionBarInfo.ActionBars[ActionBarIndex].Items.IsValidIndex(ActionIndex))
	{
		UXIItem* Item = ActionBarInfo.ActionBars[ActionBarIndex].Items[ActionIndex];
		if(Item)
		{
			Item->Use(XICharacter);
		}
	}
}