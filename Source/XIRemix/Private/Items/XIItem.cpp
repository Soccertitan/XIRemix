// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/XIItem.h"
#include "Net/UnrealNetwork.h"
#include "Components/XIInventoryComponent.h"

#define LOCTEXT_NAMESPACE "Item"

UXIItem::UXIItem()
{
    Name = LOCTEXT("ItemName", "Item");
    bStackable = false;
    MaxStackSize = 99;
    bIsExclusive = false;
    Quantity = 1;
    RepKey = 0;
}

void UXIItem::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UXIItem, Quantity, COND_None, REPNOTIFY_Always);
}

bool UXIItem::IsSupportedForNetworking() const
{
	return true;
}

#if WITH_EDITOR
void UXIItem::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName ChangedPropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	//UPROPERTY clamping doesn't support using a variable to clamp so we do in here instead
	if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(UXIItem, Quantity))
	{
		Quantity = FMath::Clamp(Quantity, 1, bStackable ? MaxStackSize : 1);
	}
	else if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(UXIItem, bStackable))
	{
		if (!bStackable)
		{
			Quantity = 1;
		}
	}
}
#endif

void UXIItem::Use(class AXICharacterBaseHero* Character)
{

}

void UXIItem::AddedToInventory(class UXIInventoryComponent* Inventory)
{

}

void UXIItem::SetQuantity(const int32 NewQuantity)
{
	if (NewQuantity != Quantity)
	{
		Quantity = FMath::Clamp(NewQuantity, 0, bStackable ? MaxStackSize : 1);
		MarkDirtyForReplication();
	}
}

void UXIItem::OnRep_Quantity()
{
    OnItemModified.Broadcast();
}

void UXIItem::MarkDirtyForReplication()
{
	//Mark this object for replication
	++RepKey;

	//Mark the array for replication
	if (OwningInventory)
	{
		++OwningInventory->ReplicatedItemsKey;
	}
}

#undef LOCTEXT_NAMESPACE
