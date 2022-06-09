// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/XIEquipmentManagerComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagsManager.h"
#include "Characters/XICharacterBaseHero.h"
#include "Components/XIInventoryComponent.h"

// Sets default values for this component's properties
UXIEquipmentManagerComponent::UXIEquipmentManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	SetComponentTickEnabled(false);
	SetIsReplicatedByDefault(true);

	EquippedItems.Add(FXIEquippedItem::FXIEquippedItem(EEquipSlot::MainHand, nullptr));
	EquippedItems.Add(FXIEquippedItem::FXIEquippedItem(EEquipSlot::SubHand, nullptr));
	EquippedItems.Add(FXIEquippedItem::FXIEquippedItem(EEquipSlot::Ranged, nullptr));
	EquippedItems.Add(FXIEquippedItem::FXIEquippedItem(EEquipSlot::Ammo, nullptr));
	EquippedItems.Add(FXIEquippedItem::FXIEquippedItem(EEquipSlot::Head, nullptr));
	EquippedItems.Add(FXIEquippedItem::FXIEquippedItem(EEquipSlot::Neck, nullptr));
	EquippedItems.Add(FXIEquippedItem::FXIEquippedItem(EEquipSlot::Ear1, nullptr));
	EquippedItems.Add(FXIEquippedItem::FXIEquippedItem(EEquipSlot::Ear2, nullptr));
	EquippedItems.Add(FXIEquippedItem::FXIEquippedItem(EEquipSlot::Body, nullptr));
	EquippedItems.Add(FXIEquippedItem::FXIEquippedItem(EEquipSlot::Hands, nullptr));
	EquippedItems.Add(FXIEquippedItem::FXIEquippedItem(EEquipSlot::Ring1, nullptr));
	EquippedItems.Add(FXIEquippedItem::FXIEquippedItem(EEquipSlot::Ring2, nullptr));
	EquippedItems.Add(FXIEquippedItem::FXIEquippedItem(EEquipSlot::Back, nullptr));
	EquippedItems.Add(FXIEquippedItem::FXIEquippedItem(EEquipSlot::Waist, nullptr));
	EquippedItems.Add(FXIEquippedItem::FXIEquippedItem(EEquipSlot::Legs, nullptr));
	EquippedItems.Add(FXIEquippedItem::FXIEquippedItem(EEquipSlot::Feet, nullptr));
}

void UXIEquipmentManagerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UXIEquipmentManagerComponent, EquippedItems, COND_None, REPNOTIFY_Always);
}

bool UXIEquipmentManagerComponent::ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
	bool bWroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	//Check if the array of items needs to replicate
	if (Channel->KeyNeedsToReplicate(0, ReplicatedItemsKey))
	{
		for (auto& Item : EquippedItems)
		{
			if (Channel->KeyNeedsToReplicate(Item.ItemEquipment->GetUniqueID(), Item.ItemEquipment->RepKey))
			{
				bWroteSomething |= Channel->ReplicateSubobject(Item.ItemEquipment, *Bunch, *RepFlags);
			}
		}
	}

	return bWroteSomething;
}

// Called when the game starts
void UXIEquipmentManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	HeroCharacter = Cast<AXICharacterBaseHero>(GetOwner());

	if(!HeroCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("XIEquipmentManagerComponent: %s is not a XICharacterBaseHero."), *GetOwner()->GetName());
		return;
	}
	
	AbilitySystemComponent = HeroCharacter->GetAbilitySystemComponent();

	if(SetByCallerParent.IsValid())
	{
		FGameplayTagContainer ChildTags;
		ChildTags = UGameplayTagsManager::Get().RequestGameplayTagChildren(SetByCallerParent);
		ChildTags.GetGameplayTagArray(SetByCallerChildTags);
	}

	CombatStyleReference = HeroCharacter->CombatStyle;

	InitializeEquippedItems();
}

void UXIEquipmentManagerComponent::SetGameplayEffects(FActiveGameplayEffectHandle& AGEHandle, UXIItemEquipment* Item)
{
	if(GetOwnerRole() != ROLE_Authority || !GEEquipment)
	{
		return;
	}

	if(AbilitySystemComponent)
	{
		// Removes the old Gameplay Effect
		AbilitySystemComponent->RemoveActiveGameplayEffect(AGEHandle);

		if(Item)
		{
			FGameplayEffectContextHandle GECH;
			FGameplayEffectSpecHandle GEC = AbilitySystemComponent->MakeOutgoingSpec(GEEquipment, 1.f, GECH);
			FGameplayEffectSpec* Spec = GEC.Data.Get();
			
			if (Spec)
			{
				InitializeSpecSetByCaller(Spec);

				for (auto& Attribute : Item->Attributes)
				{
					Spec->SetSetByCallerMagnitude(Attribute.AttributeTag, Attribute.Value);
				}

				Spec->DynamicGrantedTags = Item->GrantedTags;
				AGEHandle = AbilitySystemComponent->BP_ApplyGameplayEffectSpecToSelf(GEC);
			}
		}
	}
}

void UXIEquipmentManagerComponent::SetGameplayEffectAttackDelay(float Delay, FActiveGameplayEffectHandle& AGEHandle, bool bIsMelee)
{
	if(GetOwnerRole() != ROLE_Authority || !GEMeleeAttackDelay || !GEWeaponTags || !GERangeAttackDelay)
	{
		return;
	}

	if(AbilitySystemComponent)
	{
		//Removes the old Gameplay Effect
		AbilitySystemComponent->RemoveActiveGameplayEffect(AGEHandle);

		FGameplayEffectContextHandle GECH;
		FGameplayEffectSpecHandle GEC = AbilitySystemComponent->MakeOutgoingSpec(GEWeaponTags, 1.f, GECH);
		FGameplayEffectSpec* Spec = GEC.Data.Get();

		if (Spec)
		{
			if(bIsMelee)
			{
				UXIItemEquipment* MainHand = FindEquippedItemBySlot(EEquipSlot::MainHand);
				UXIItemEquipment* SubHand = FindEquippedItemBySlot(EEquipSlot::SubHand);

				if(MainHand)
				{
					Spec->DynamicGrantedTags.AddTag(MainHand->WeaponType);
				}
				if(SubHand)
				{
					Spec->DynamicGrantedTags.AddTag(SubHand->WeaponType);
					if(SubHand->ItemType == EItemType::WeaponMelee)
					{
						Spec->DynamicGrantedTags.AddTag(DualWielding);
					}
				}

				// Applies the instant Gameplay Effect for the Melee Attack Delay
				FGameplayEffectContextHandle GECHInstant;
				FGameplayEffectSpecHandle GECInstant = AbilitySystemComponent->MakeOutgoingSpec(GEMeleeAttackDelay, 1.f, GECHInstant);
				FGameplayEffectSpec* SpecInstant = GECInstant.Data.Get();

				if (SpecInstant)
				{
					SpecInstant->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag("SetByCaller.Attributes.AttackSpeed"), Delay);
					AbilitySystemComponent->BP_ApplyGameplayEffectSpecToSelf(GECInstant);
				}
			}
			else // Ranged Weapon
			{
				UXIItemEquipment* Ranged = FindEquippedItemBySlot(EEquipSlot::Ranged);
				
				if(Ranged)
				{
					Spec->DynamicGrantedTags.AddTag(Ranged->WeaponType);
				}

				// Applies the instant Gameplay Effect for the Ranged Attack Delay
				FGameplayEffectContextHandle GECHInstant;
				FGameplayEffectSpecHandle GECInstant = AbilitySystemComponent->MakeOutgoingSpec(GERangeAttackDelay, 1.f, GECHInstant);
				FGameplayEffectSpec* SpecInstant = GECInstant.Data.Get();

				if (SpecInstant)
				{
					SpecInstant->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag("SetByCaller.Attributes.AttackSpeed"), Delay);
					AbilitySystemComponent->BP_ApplyGameplayEffectSpecToSelf(GECInstant);
				}
			}

			// Applies the Gameplay Tags
			AGEHandle = AbilitySystemComponent->BP_ApplyGameplayEffectSpecToSelf(GEC);
		}
	}
}

float UXIEquipmentManagerComponent::GetAttackDelay(bool bIsMelee) const
{
	float Delay = 480.f;

	if(bIsMelee)
	{
		UXIItemEquipment* MainHand = FindEquippedItemBySlot(EEquipSlot::MainHand);
		UXIItemEquipment* SubHand = FindEquippedItemBySlot(EEquipSlot::SubHand);

		if(MainHand && MainHand->CombatStyle == ECombatStyle::Battle3)
		{
			Delay += MainHand->Delay;
		}
		else if(SubHand && MainHand && SubHand->ItemType == EItemType::WeaponMelee)
		{
			Delay = (MainHand->Delay + SubHand->Delay) / 2.f ;
		}
		else if (MainHand)
		{
			Delay = MainHand->Delay;
		}
	}
	else
	{
		UXIItemEquipment* Ranged = FindEquippedItemBySlot(EEquipSlot::Ranged);
		if(Ranged)
		{
			Delay = Ranged->Delay;
		}
	}

	return Delay;
}

void UXIEquipmentManagerComponent::InitializeSpecSetByCaller(FGameplayEffectSpec* InSpec)
{
	if(InSpec)
	{
		for(FGameplayTag& Tag : SetByCallerChildTags)
		{
			InSpec->SetSetByCallerMagnitude(Tag, 0.f);
		}
	}
}

bool UXIEquipmentManagerComponent::IsItemEquipable(UXIItem* Item) const
{
	if(!HeroCharacter || !Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("Warning! The Item or the Hero is invalid."));
		return false;
	}
	
	UXIItemEquipment* EquipItem = Cast<UXIItemEquipment>(Item);
	if(!EquipItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("Warning! The item is not a subclass of UXIItemEquipment."))
		return false;
	}

	FXICharacterHeroActiveJobsLevels CharacterJobsLevels;
	CharacterJobsLevels = HeroCharacter->GetCharacterActiveJobsAndLevels();

	if(!EquipItem->JobRequirements)
	{
		return false;
	}

	if((CharacterJobsLevels.MainJobLevel >= EquipItem->LevelRequirement && EquipItem->JobRequirements->JobTags.HasTagExact(CharacterJobsLevels.MainJobTag)) || (CharacterJobsLevels.SubJobLevel >= EquipItem->LevelRequirement && EquipItem->JobRequirements->JobTags.HasTagExact(CharacterJobsLevels.SubJobTag)))
	{
		return true;
	}
	return false;
}

void UXIEquipmentManagerComponent::EquipItem(UXIItem* Item, EEquipSlot EquipSlot)
{
	if(!GetOwner()->HasAuthority())
	{
		Server_EquipItem(Item, EquipSlot);
	}
	else
	{
		if(!Item || !IsItemEquipable(Item))
		{	
			return;
		}

		UXIItemEquipment* EquipItem = Cast<UXIItemEquipment>(Item);
		if(!EquipItem && EquipItem->OwningInventory && EquipItem->OwningInventory->FindItem(EquipItem))
		{
			UE_LOG(LogTemp, Warning, TEXT("Warning! The item cannot be equipped. Because it's either invalid, does not have an owning inventory, or does not exist in the inventory."))
			return;
		}

		//The item cannot be equipped to that slot!.
		if(!EquipItem->EquipSlot.Contains(EquipSlot))
		{
			UE_LOG(LogTemp, Warning, TEXT("Item cannot be equipped to that slot"));
			return;
		}

		// Gets the Index of the array that will equip the item.
		const FXIEquippedItem ItemSlot = FXIEquippedItem::FXIEquippedItem(EquipSlot);
		const int Index = EquippedItems.Find(ItemSlot);

		if(Index == -1)
		{
			return;
		}

		switch (EquipSlot)
		{
			case EEquipSlot::MainHand:
			{
				// Unequip the item from Subhand because we're weilding a 2Handed weapon.
				if(!EquipItem->EquipSlot.Contains(EEquipSlot::SubHand))
				{
					// Gets the Index of the array that will unequip the item.
					const FXIEquippedItem SubItemSlot = FXIEquippedItem::FXIEquippedItem(EEquipSlot::SubHand);
					const int SubIndex = EquippedItems.Find(SubItemSlot);

					if(SubIndex != -1)
					{
						EquippedItems[SubIndex].ItemEquipment = nullptr;
						SetGameplayEffects(EquippedItems[SubIndex].ActiveGEHandle, nullptr);
						OnUpdateMesh.Broadcast(nullptr, ESkeletalMeshMergeType::SubHand);
					}
				}

				EquippedItems[Index].ItemEquipment = EquipItem;
				SetGameplayEffectAttackDelay(GetAttackDelay(true), AGEMeleeDelayTags, true);
				CheckCombatStyle();
				OnUpdateMesh.Broadcast(EquipItem, ESkeletalMeshMergeType::MainHand);
			}	
				break;

			case EEquipSlot::SubHand:
			{
				// Gets the Index of the array that will unequip the item.
				const FXIEquippedItem MainItemSlot = FXIEquippedItem::FXIEquippedItem(EEquipSlot::MainHand);
				const int MainIndex = EquippedItems.Find(MainItemSlot);
				
				if(MainIndex != -1 && EquippedItems[MainIndex].ItemEquipment)
				{
					// Unequips MainHand item if it cannot be equipped in the sub hand.
					if(!EquippedItems[MainIndex].ItemEquipment->EquipSlot.Contains(EEquipSlot::SubHand))
					{
						EquippedItems[MainIndex].ItemEquipment = nullptr;
						SetGameplayEffects(EquippedItems[MainIndex].ActiveGEHandle, nullptr);
					}
				}

				if(EquipItem->ItemType == EItemType::WeaponMelee && !AbilitySystemComponent->HasMatchingGameplayTag(DualWield))
				{
					// Don't equip the subHand item. We can't dual wield.
					return;
				}

				EquippedItems[Index].ItemEquipment = EquipItem;
				SetGameplayEffectAttackDelay(GetAttackDelay(true), AGEMeleeDelayTags, true);
				CheckCombatStyle();
				OnUpdateMesh.Broadcast(EquipItem, ESkeletalMeshMergeType::SubHand);
			}
				break;

			case EEquipSlot::Ranged:
			{
				EquippedItems[Index].ItemEquipment = EquipItem;
				SetGameplayEffectAttackDelay(GetAttackDelay(false), AGERangeDelayTags, false);
				/*
				TODO: Add logic to remove ammo if not appropriate.
				*/
				OnUpdateMesh.Broadcast(EquipItem, ESkeletalMeshMergeType::Range);
			}
				break;
			
			case EEquipSlot::Ammo:
				
				//TODO for Ammo logic.
				break;
			
			case EEquipSlot::Head:
			{
				//Unequips Body equipment if body does not allow head gear.
				// Gets the Index of the array that will unequip the item.
				const FXIEquippedItem BodyItemSlot = FXIEquippedItem::FXIEquippedItem(EEquipSlot::Body);
				const int BodyIndex = EquippedItems.Find(BodyItemSlot);

				if(BodyIndex != -1 && EquippedItems[BodyIndex].ItemEquipment && EquippedItems[BodyIndex].ItemEquipment->GrantedTags.HasTag(NoHeadGear))
				{
					EquippedItems[BodyIndex].ItemEquipment = nullptr;
					SetGameplayEffects(EquippedItems[BodyIndex].ActiveGEHandle, nullptr);
					OnUpdateMesh.Broadcast(nullptr, ESkeletalMeshMergeType::Body);
				}

				EquippedItems[Index].ItemEquipment = EquipItem;
				OnUpdateMesh.Broadcast(EquipItem, ESkeletalMeshMergeType::Head);
			}
				break;
			
			case EEquipSlot::Body:
			{
				//Unequips Head equipment if body does not allow head gear.
				// Gets the Index of the array that will unequip the item.
				const FXIEquippedItem HeadItemSlot = FXIEquippedItem::FXIEquippedItem(EEquipSlot::Head);
				const int HeadIndex = EquippedItems.Find(HeadItemSlot);
				
				if(HeadIndex != -1 && EquippedItems[HeadIndex].ItemEquipment && EquipItem->GrantedTags.HasTag(NoHeadGear))
				{
					EquippedItems[HeadIndex].ItemEquipment = nullptr;
					SetGameplayEffects(EquippedItems[HeadIndex].ActiveGEHandle, nullptr);
					OnUpdateMesh.Broadcast(nullptr, ESkeletalMeshMergeType::Head);
				}
						
				EquippedItems[Index].ItemEquipment = EquipItem;
				OnUpdateMesh.Broadcast(EquipItem, ESkeletalMeshMergeType::Body);
			}
				break;

			case EEquipSlot::Hands:
				
				EquippedItems[Index].ItemEquipment = EquipItem;
				OnUpdateMesh.Broadcast(EquipItem, ESkeletalMeshMergeType::Hands);
				break;

			case EEquipSlot::Legs:
				
				EquippedItems[Index].ItemEquipment = EquipItem;
				OnUpdateMesh.Broadcast(EquipItem, ESkeletalMeshMergeType::Legs);
				break;

			case EEquipSlot::Feet:
				
				EquippedItems[Index].ItemEquipment = EquipItem;
				OnUpdateMesh.Broadcast(EquipItem, ESkeletalMeshMergeType::Feet);
				break;
		}

		EquippedItems[Index].ItemEquipment = EquipItem;
		SetGameplayEffects(EquippedItems[Index].ActiveGEHandle, EquippedItems[Index].ItemEquipment);
		OnEquipmentUpdated.Broadcast();
		OnRep_EquippedItems();
	}
}

bool UXIEquipmentManagerComponent::Server_EquipItem_Validate(UXIItem* Item, EEquipSlot EquipSlot)
{
	return true;
}

void UXIEquipmentManagerComponent::Server_EquipItem_Implementation(UXIItem* Item, EEquipSlot EquipSlot)
{
	EquipItem(Item, EquipSlot);
}

void UXIEquipmentManagerComponent::UnEquipItem(EEquipSlot EquipSlot)
{
	if(!GetOwner()->HasAuthority())
	{
		Server_UnEquipItem(EquipSlot);
	}
	else
	{
		// Gets the Index of the array that will unequip the item.
		const FXIEquippedItem ItemSlot = FXIEquippedItem::FXIEquippedItem(EquipSlot);
		const int Index = EquippedItems.Find(ItemSlot);

		if(Index == -1)
		{
			return;
		}

		if(!EquippedItems[Index].ItemEquipment)
		{
			//Item is already null. No action
			return;
		}

		EquippedItems[Index].ItemEquipment = nullptr;
		SetGameplayEffects(EquippedItems[Index].ActiveGEHandle, nullptr);
		
		switch(EquipSlot)
		{
			case EEquipSlot::MainHand:
				SetGameplayEffectAttackDelay(GetAttackDelay(true), AGEMeleeDelayTags, true);
				OnUpdateMesh.Broadcast(nullptr, ESkeletalMeshMergeType::MainHand);
				CheckCombatStyle();
				break;
			
			case EEquipSlot::SubHand:
				SetGameplayEffectAttackDelay(GetAttackDelay(true), AGEMeleeDelayTags, true);
				OnUpdateMesh.Broadcast(nullptr, ESkeletalMeshMergeType::SubHand);
				CheckCombatStyle();
				break;

			case EEquipSlot::Ranged:
				SetGameplayEffectAttackDelay(GetAttackDelay(false), AGERangeDelayTags, false);
				OnUpdateMesh.Broadcast(nullptr, ESkeletalMeshMergeType::Range);
				break;

			case EEquipSlot::Head:
				OnUpdateMesh.Broadcast(nullptr, ESkeletalMeshMergeType::Head);
				break;

			case EEquipSlot::Body:
				OnUpdateMesh.Broadcast(nullptr, ESkeletalMeshMergeType::Body);
				break;

			case EEquipSlot::Hands:
				OnUpdateMesh.Broadcast(nullptr, ESkeletalMeshMergeType::Hands);
				break;

			case EEquipSlot::Legs:
				OnUpdateMesh.Broadcast(nullptr, ESkeletalMeshMergeType::Legs);
				break;

			case EEquipSlot::Feet:
				OnUpdateMesh.Broadcast(nullptr, ESkeletalMeshMergeType::Feet);
				break;
		}				
		OnRep_EquippedItems();
		return;
	}
}

bool UXIEquipmentManagerComponent::Server_UnEquipItem_Validate(EEquipSlot EquipSlot)
{
	return true;
}

void UXIEquipmentManagerComponent::Server_UnEquipItem_Implementation(EEquipSlot EquipSlot)
{
	UnEquipItem(EquipSlot);
}

UXIItemEquipment* UXIEquipmentManagerComponent::FindEquippedItemBySlot(EEquipSlot EquipSlot) const
{
	const FXIEquippedItem ItemRef = FXIEquippedItem::FXIEquippedItem(EquipSlot);
	const int Index = EquippedItems.Find(ItemRef);

	if(Index != -1)
	{
		return EquippedItems[Index].ItemEquipment;
	}

	return nullptr;
}

ECombatStyle UXIEquipmentManagerComponent::CheckCombatStyle()
{
	UXIItemEquipment* MainHand = FindEquippedItemBySlot(EEquipSlot::MainHand);
	UXIItemEquipment* SubHand = FindEquippedItemBySlot(EEquipSlot::SubHand);

	if(MainHand && !SubHand)
	{
		if (MainHand->CombatStyle != CombatStyleReference)
		{
			CombatStyleReference = MainHand->CombatStyle;
			OnCombatStyleChanged.Broadcast(CombatStyleReference);
		}
	}
	else if(MainHand && SubHand)
	{
		if(MainHand->ItemType == EItemType::WeaponMelee && SubHand->ItemType != EItemType::WeaponMelee)
		{
			if (MainHand->CombatStyle != CombatStyleReference)
			{
				CombatStyleReference = MainHand->CombatStyle;
				OnCombatStyleChanged.Broadcast(CombatStyleReference);
			}
		}
		else if (MainHand->ItemType == EItemType::WeaponMelee && SubHand->ItemType == EItemType::WeaponMelee)
		{
			//TODO: How to determine Dual Wield Style.
		}
	}
	else if(!MainHand)
	{
		if(CombatStyleReference != ECombatStyle::Battle9)
		{
			CombatStyleReference = ECombatStyle::Battle9;
			OnCombatStyleChanged.Broadcast(CombatStyleReference);
		}
	}

	return CombatStyleReference;
}

void UXIEquipmentManagerComponent::InitializeEquippedItems()
{
	
}

void UXIEquipmentManagerComponent::OnRep_EquippedItems()
{
	SetupEquippedItemsReference();
	OnEquipmentUpdated.Broadcast();
}

void UXIEquipmentManagerComponent::SetupEquippedItemsReference()
{
	//Accessing Items this way to save on iterating through the Array. As we know which index is which item.
	// Not sure how much this saves. But if this causes problems or bad practice remove this block and re-enable the one below.
	EquippedItemsReference.MainHand = EquippedItems[0].ItemEquipment;
	EquippedItemsReference.SubHand = EquippedItems[1].ItemEquipment;
	EquippedItemsReference.Ranged = EquippedItems[2].ItemEquipment;
	EquippedItemsReference.Ammo = EquippedItems[3].ItemEquipment;
	EquippedItemsReference.Head = EquippedItems[4].ItemEquipment;
	EquippedItemsReference.Neck = EquippedItems[5].ItemEquipment;
	EquippedItemsReference.Ear1 = EquippedItems[6].ItemEquipment;
	EquippedItemsReference.Ear2 = EquippedItems[7].ItemEquipment;
	EquippedItemsReference.Body = EquippedItems[8].ItemEquipment;
	EquippedItemsReference.Hands = EquippedItems[9].ItemEquipment;
	EquippedItemsReference.Ring1 = EquippedItems[10].ItemEquipment;
	EquippedItemsReference.Ring2 = EquippedItems[11].ItemEquipment;
	EquippedItemsReference.Back = EquippedItems[12].ItemEquipment;
	EquippedItemsReference.Waist = EquippedItems[13].ItemEquipment;
	EquippedItemsReference.Legs = EquippedItems[14].ItemEquipment;
	EquippedItemsReference.Feet = EquippedItems[15].ItemEquipment;
	
	// for (auto& Item : EquippedItems)
	// {
	// 	if(Item.EquipSlot == EEquipSlot::MainHand) EquippedItemsReference.MainHand = Item.ItemEquipment;
	// 	else if(Item.EquipSlot == EEquipSlot::SubHand) EquippedItemsReference.SubHand = Item.ItemEquipment;
	// 	else if(Item.EquipSlot == EEquipSlot::Ranged) EquippedItemsReference.Ranged = Item.ItemEquipment;
	// 	else if(Item.EquipSlot == EEquipSlot::Ammo) EquippedItemsReference.Ammo = Item.ItemEquipment;
	// 	else if(Item.EquipSlot == EEquipSlot::Head) EquippedItemsReference.Head = Item.ItemEquipment;
	// 	else if(Item.EquipSlot == EEquipSlot::Neck) EquippedItemsReference.Neck = Item.ItemEquipment;
	// 	else if(Item.EquipSlot == EEquipSlot::Ear1) EquippedItemsReference.Ear1 = Item.ItemEquipment;
	// 	else if(Item.EquipSlot == EEquipSlot::Ear2) EquippedItemsReference.Ear2 = Item.ItemEquipment;
	// 	else if(Item.EquipSlot == EEquipSlot::Body) EquippedItemsReference.Body = Item.ItemEquipment;
	// 	else if(Item.EquipSlot == EEquipSlot::Hands) EquippedItemsReference.Hands = Item.ItemEquipment;
	// 	else if(Item.EquipSlot == EEquipSlot::Ring1) EquippedItemsReference.Ring1 = Item.ItemEquipment;
	// 	else if(Item.EquipSlot == EEquipSlot::Ring2) EquippedItemsReference.Ring2 = Item.ItemEquipment;
	// 	else if(Item.EquipSlot == EEquipSlot::Back) EquippedItemsReference.Back = Item.ItemEquipment;
	// 	else if(Item.EquipSlot == EEquipSlot::Waist) EquippedItemsReference.Waist = Item.ItemEquipment;
	// 	else if(Item.EquipSlot == EEquipSlot::Legs) EquippedItemsReference.Legs = Item.ItemEquipment;
	// 	else if(Item.EquipSlot == EEquipSlot::Feet) EquippedItemsReference.Feet = Item.ItemEquipment;
	// }
}