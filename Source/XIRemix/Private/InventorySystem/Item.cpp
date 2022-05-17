// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystem/Item.h"
#include "Net/UnrealNetwork.h"
#include "InventorySystem/InventoryComponent.h"

#define LOCTEXT_NAMESPACE "Item"

UItem::UItem()
{
    Name = LOCTEXT("ItemName", "Item");
    bStackable = false;
    MaxStackSize = 99;
    bIsExclusive = false;
    Quantity = 1;
    RepKey = 0;
}

void UItem::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UItem, Quantity, COND_None, REPNOTIFY_Always);
}

bool UItem::IsSupportedForNetworking() const
{
	return true;
}

#if WITH_EDITOR
void UItem::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName ChangedPropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	//UPROPERTY clamping doesn't support using a variable to clamp so we do in here instead
	if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(UItem, Quantity))
	{
		Quantity = FMath::Clamp(Quantity, 1, bStackable ? MaxStackSize : 1);
	}
	else if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(UItem, bStackable))
	{
		if (!bStackable)
		{
			Quantity = 1;
		}
	}
}
#endif

void UItem::Use(class AXICharacterBaseHero* Character)
{

}

void UItem::AddedToInventory(class UInventoryComponent* Inventory)
{

}

void UItem::SetQuantity(const int32 NewQuantity)
{
	if (NewQuantity != Quantity)
	{
		Quantity = FMath::Clamp(NewQuantity, 0, bStackable ? MaxStackSize : 1);
		MarkDirtyForReplication();
	}
}

void UItem::OnRep_Quantity()
{
    OnItemModified.Broadcast();
}

void UItem::MarkDirtyForReplication()
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