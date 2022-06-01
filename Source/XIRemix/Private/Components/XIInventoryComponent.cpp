// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/XIInventoryComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "Items/XIItem.h"

#define LOCTEXT_NAMESPACE "Inventory"

// Sets default values for this component's properties
UXIInventoryComponent::UXIInventoryComponent()
{
	Capacity = 100;
	OnItemAdded.AddDynamic(this, &UXIInventoryComponent::ItemAdded);
	OnItemRemoved.AddDynamic(this, &UXIInventoryComponent::ItemRemoved);

	SetIsReplicatedByDefault(true);
}

FXIItemAddResult UXIInventoryComponent::TryAddItem(class UXIItem* Item)
{
	return TryAddItem_Internal(Item);
}

FXIItemAddResult UXIInventoryComponent::TryAddItemFromClass(TSubclassOf<class UXIItem> ItemClass, const int32 Quantity /*=1*/)
{
	UXIItem* Item = NewObject<UXIItem>(GetOwner(), ItemClass);
	Item->SetQuantity(Quantity);
	return TryAddItem_Internal(Item);
}

int32 UXIInventoryComponent::ConsumeItem(class UXIItem* Item)
{
	if (Item)
	{
		ConsumeItem(Item, Item->GetQuantity());
	}
	return 0;
}

int32 UXIInventoryComponent::ConsumeItem(class UXIItem* Item, const int32 Quantity)
{
	if (GetOwner() && GetOwner()->HasAuthority() && Item)
	{
		const int32 RemoveQuantity = FMath::Min(Quantity, Item->GetQuantity());

		//We shouldn't have a negative amount of the item after the drop
		ensure(!(Item->GetQuantity() - RemoveQuantity < 0));

		//We now have zero of this item, remove it from the inventory
		Item->SetQuantity(Item->GetQuantity() - RemoveQuantity);

		if (Item->GetQuantity() <= 0)
		{
			RemoveItem(Item);
		}
		else
		{
			Client_RefreshInventory();
		}

		return RemoveQuantity;
	}

	return 0;
}

bool UXIInventoryComponent::RemoveItem(class UXIItem* Item)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		if (Item)
		{
			Items.RemoveSingle(Item);
			OnItemRemoved.Broadcast(Item);

			OnRep_Items();

			ReplicatedItemsKey++;

			return true;
		}
	}

	return false;
}

bool UXIInventoryComponent::HasItem(TSubclassOf <class UXIItem> ItemClass, const int32 Quantity /*= 1*/) const
{
	if (UXIItem* ItemToFind = FindItemByClass(ItemClass))
	{
		return ItemToFind->GetQuantity() >= Quantity;
	}
	return false;
}

UXIItem* UXIInventoryComponent::FindItem(class UXIItem* Item) const
{
	if (Item)
	{
		for (auto& InvItem : Items)
		{
			if (InvItem && InvItem->GetClass() == Item->GetClass())
			{
				return InvItem;
			}
		}
	}
	return nullptr;
}

UXIItem* UXIInventoryComponent::FindItemByClass(TSubclassOf<class UXIItem> ItemClass) const
{
	for (auto& InvItem : Items)
	{
		if (InvItem && InvItem->GetClass() == ItemClass)
		{
			return InvItem;
		}
	}
	return nullptr;
}

TArray<UXIItem*> UXIInventoryComponent::FindItemsByClass(TSubclassOf<class UXIItem> ItemClass) const
{
	TArray<UXIItem*> ItemsOfClass;

	for (auto& InvItem : Items)
	{
		if (InvItem && InvItem->GetClass()->IsChildOf(ItemClass))
		{
			ItemsOfClass.Add(InvItem);
		}
	}

	return ItemsOfClass;
}

void UXIInventoryComponent::SetCapacity(const int32 NewCapacity)
{
	Capacity = NewCapacity;
	OnInventoryUpdated.Broadcast();
}

void UXIInventoryComponent::Client_RefreshInventory_Implementation()
{
	OnInventoryUpdated.Broadcast();
}

void UXIInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UXIInventoryComponent, Items, COND_None, REPNOTIFY_Always);
}

bool UXIInventoryComponent::ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
	bool bWroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	//Check if the array of items needs to replicate
	if (Channel->KeyNeedsToReplicate(0, ReplicatedItemsKey))
	{
		for (auto& Item : Items)
		{
			if (Channel->KeyNeedsToReplicate(Item->GetUniqueID(), Item->RepKey))
			{
				bWroteSomething |= Channel->ReplicateSubobject(Item, *Bunch, *RepFlags);
			}
		}
	}

	return bWroteSomething;
}

UXIItem* UXIInventoryComponent::AddItem(class UXIItem* Item, const int32 Quantity)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		UXIItem* NewItem = NewObject<UXIItem>(GetOwner(), Item->GetClass());
		NewItem->World = GetWorld();
		NewItem->SetQuantity(Quantity);
		NewItem->OwningInventory = this;
		NewItem->AddedToInventory(this);
		Items.Add(NewItem);
		NewItem->MarkDirtyForReplication();
		OnItemAdded.Broadcast(NewItem);
		OnRep_Items();

		return NewItem;
	}

	return nullptr;
}

void UXIInventoryComponent::OnRep_Items()
{
	OnInventoryUpdated.Broadcast();

	for (auto& Item : Items)
	{
		//On the client the world won't be set initially, so it set if not
		if (!Item->World)
		{
			OnItemAdded.Broadcast(Item);
			Item->World = GetWorld();
		}
	}
}

FXIItemAddResult UXIInventoryComponent::TryAddItem_Internal(class UXIItem* Item)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		if (Item->bStackable)
		{
			//Somehow the items quantity went over the max stack size. This shouldn't ever happen
			ensure(Item->GetQuantity() <= Item->MaxStackSize);

			if (UXIItem* ExistingItem = FindItem(Item))
			{
				if (ExistingItem->IsStackFull())
				{
					return FXIItemAddResult::AddedNone(Item->GetQuantity(), FText::Format(LOCTEXT("StackFullText", "Couldn't add {ItemName}. Tried adding items to a stack that was full."), Item->Name));
				}
				else
				{
					const int32 QuantityMaxAddAmount = FMath::Min(ExistingItem->MaxStackSize - ExistingItem->GetQuantity(), Item->GetQuantity());
					const int32 AddAmount = QuantityMaxAddAmount;

					ExistingItem->SetQuantity(ExistingItem->GetQuantity() + AddAmount);
					return AddAmount >= Item->GetQuantity() ? FXIItemAddResult::AddedAll(Item->GetQuantity()) : FXIItemAddResult::AddedSome(Item->GetQuantity(), AddAmount, LOCTEXT("StackAddedSomeFullText", "Couldn't add all of stack to inventory."));
				}
			}
			else //we want to add a stackable item that doesn't exist in the inventory
			{
				if (Items.Num() + 1 > GetCapacity() && GetCapacity() != 0)
				{
					return FXIItemAddResult::AddedNone(Item->GetQuantity(), FText::Format(LOCTEXT("InventoryCapacityFullText", "Couldn't add {ItemName} to Inventory. Inventory is full."), Item->Name));
				}

				const int32 QuantityMaxAddAmount = FMath::Min(Item->MaxStackSize, Item->GetQuantity());
				const int32 AddAmount = QuantityMaxAddAmount;

				AddItem(Item, AddAmount);

				return AddAmount >= Item->GetQuantity() ? FXIItemAddResult::AddedAll(Item->GetQuantity()) : FXIItemAddResult::AddedSome(Item->GetQuantity(), AddAmount, LOCTEXT("StackAddedSomeFullText", "Couldn't add all of stack to inventory."));
			}
		}
		else //item isnt stackable
		{
			if (Items.Num() + 1 > GetCapacity() && GetCapacity() != 0)
			{
				return FXIItemAddResult::AddedNone(Item->GetQuantity(), FText::Format(LOCTEXT("InventoryCapacityFullText", "Couldn't add {ItemName} to Inventory. Inventory is full."), Item->Name));
			}

			//Non-stackables should always have a quantity of 1
			ensure(Item->GetQuantity() == 1);

			AddItem(Item, 1);

			return FXIItemAddResult::AddedAll(Item->GetQuantity());
		}
	}

	//AddItem should never be called on a client
	return FXIItemAddResult::AddedNone(-1, LOCTEXT("ErrorMessage", ""));

}

void UXIInventoryComponent::ItemAdded(class UXIItem* Item)
{
	FString RoleString = GetOwner()->HasAuthority() ? "server" : "client";
	UE_LOG(LogTemp, Warning, TEXT("Item added: %s on %s"), *GetNameSafe(Item), *RoleString);
}

void UXIInventoryComponent::ItemRemoved(class UXIItem* Item)
{
	FString RoleString = GetOwner()->HasAuthority() ? "server" : "client";
	UE_LOG(LogTemp, Warning, TEXT("Item Removed: %s on %s"), *GetNameSafe(Item), *RoleString);
}

#undef LOCTEXT_NAMESPACE