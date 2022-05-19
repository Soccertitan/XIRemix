// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/XIEquipmentManagerComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagsManager.h"
#include "Characters/XICharacterBaseHero.h"

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

	InitializeEquippedItems();
}

void UXIEquipmentManagerComponent::SetGameplayEffects(FActiveGameplayEffectHandle& AGEHandle, UItemEquipment* Item)
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

				for (FXIGrantedAttribute Attribute : Item->Attributes)
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
				UItemEquipment* MainHand = FindEquippedItemBySlot(EEquipSlot::MainHand);
				UItemEquipment* SubHand = FindEquippedItemBySlot(EEquipSlot::SubHand);

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
				UItemEquipment* Ranged = FindEquippedItemBySlot(EEquipSlot::Ranged);
				
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
		UItemEquipment* MainHand = FindEquippedItemBySlot(EEquipSlot::MainHand);
		UItemEquipment* SubHand = FindEquippedItemBySlot(EEquipSlot::SubHand);

		if(MainHand && MainHand->CombatStyle == ECombatStyle::Hand2Hand)
		{
			Delay += MainHand->Delay;
		}
		else if(SubHand && SubHand->ItemType == EItemType::WeaponMelee)
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
		UItemEquipment* Ranged = FindEquippedItemBySlot(EEquipSlot::Ranged);
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

bool UXIEquipmentManagerComponent::IsItemEquipable(UItemEquipment* Item) const
{
	if(!HeroCharacter || !Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("Warning! The Item or the Hero is invalid."));
		return false;
	}

	FXICharacterHeroActiveJobsLevels CharacterJobsLevels;
	CharacterJobsLevels = HeroCharacter->GetCharacterActiveJobsAndLevels();

	if(!Item->JobRequirements)
	{
		return true;
	}

	if((CharacterJobsLevels.MainJobLevel >= Item->LevelRequirement && Item->JobRequirements->JobTags.HasTagExact(CharacterJobsLevels.MainJobTag)) || (CharacterJobsLevels.SubJobLevel >= Item->LevelRequirement && Item->JobRequirements->JobTags.HasTagExact(CharacterJobsLevels.SubJobTag)))
	{
		return true;
	}
	return false;
}

bool UXIEquipmentManagerComponent::Server_EquipItem_Validate(UItemEquipment* Item, EEquipSlot EquipSlot)
{
	return true;
}

void UXIEquipmentManagerComponent::Server_EquipItem_Implementation(UItemEquipment* Item, EEquipSlot EquipSlot)
{
	if(!Item || !IsItemEquipable(Item))
	{	
		return;
	}

	for(auto& Equipment : EquippedItems)
	{
		//Skip to next iteration of the loop if the EquipSlot is not equal to the Array's equip slot.
		if(!(Equipment.EquipSlot == EquipSlot))
		{
			continue;
		}

		//The item cannot be equipped to that slot!.
		if(!Item->EquipSlot.Contains(EquipSlot))
		{
			UE_LOG(LogTemp, Warning, TEXT("Item cannot be equipped to that slot"));
			return;
		}

		switch (EquipSlot)
		{
			case EEquipSlot::MainHand:
				
				// Unequip the item from Subhand because we're weilding a 2Handed weapon.
				if(!Item->EquipSlot.Contains(EEquipSlot::SubHand))
				{
					for(auto& SubItem : EquippedItems)
					{
						if(SubItem.EquipSlot == EEquipSlot::SubHand)
						{
							SubItem.ItemEquipment = nullptr;
							SetGameplayEffects(SubItem.ActiveGEHandle, nullptr);
							OnUpdateMesh.Broadcast(nullptr, ESkeletalMeshMergeType::SubHand);
							break;
						}
					}
				}

				Equipment.ItemEquipment = Item;
				SetGameplayEffectAttackDelay(GetAttackDelay(true), AGEMeleeDelayTags, true);
				CheckCombatStyle();
				OnUpdateMesh.Broadcast(Item, ESkeletalMeshMergeType::MainHand);
				break;

			case EEquipSlot::SubHand:

				for(auto& MainItem : EquippedItems)
				{
					if(MainItem.EquipSlot == EEquipSlot::MainHand)
					{
						if(MainItem.ItemEquipment)
						{
							if(MainItem.ItemEquipment->EquipSlot.Contains(EEquipSlot::SubHand))
							{
								MainItem.ItemEquipment = nullptr;
								SetGameplayEffects(MainItem.ActiveGEHandle, nullptr);
							}
						}
						break;
					}
				}

				if(Item->ItemType == EItemType::WeaponMelee && !AbilitySystemComponent->HasMatchingGameplayTag(DualWield))
				{
					// Don't equip the subHand item. We can't dual wield.
					return;
				}

				Equipment.ItemEquipment = Item;
				SetGameplayEffectAttackDelay(GetAttackDelay(true), AGEMeleeDelayTags, true);
				CheckCombatStyle();
				OnUpdateMesh.Broadcast(Item, ESkeletalMeshMergeType::SubHand);
				break;

			case EEquipSlot::Ranged:

				Equipment.ItemEquipment = Item;
				SetGameplayEffectAttackDelay(GetAttackDelay(false), AGERangeDelayTags, false);
				/*
				TODO: Add logic to remove ammo if not appropriate.
				*/
				OnUpdateMesh.Broadcast(Item, ESkeletalMeshMergeType::Range);
				break;
			
			case EEquipSlot::Ammo:
				//TODO for Ammo logic.
				break;
			
			case EEquipSlot::Head:
				//Unequips Body equipment if body does not allow head gear.
				for(auto& Body : EquippedItems)
				{
					if(Body.EquipSlot == EEquipSlot::Body)
					{
						if(Body.ItemEquipment && Body.ItemEquipment->GrantedTags.HasTag(NoHeadGear))
						{
							Body.ItemEquipment = nullptr;
							SetGameplayEffects(Body.ActiveGEHandle, nullptr);
							OnUpdateMesh.Broadcast(nullptr, ESkeletalMeshMergeType::Body);
						}
						break;
					}
				}
				Equipment.ItemEquipment = Item;
				OnUpdateMesh.Broadcast(Item, ESkeletalMeshMergeType::Head);
				break;
			
			case EEquipSlot::Body:
				//Unequips Head equipment if body does not allow head gear.
				for(auto& Head : EquippedItems)
				{
					if(Head.EquipSlot == EEquipSlot::Head)
					{
						if(Head.ItemEquipment && Equipment.ItemEquipment->GrantedTags.HasTag(NoHeadGear))
						{
							Head.ItemEquipment = nullptr;
							SetGameplayEffects(Head.ActiveGEHandle, nullptr);
							OnUpdateMesh.Broadcast(nullptr, ESkeletalMeshMergeType::Head);
						}
						break;
					}
				}
				Equipment.ItemEquipment = Item;
				OnUpdateMesh.Broadcast(Item, ESkeletalMeshMergeType::Body);
				break;

			case EEquipSlot::Hands:
				Equipment.ItemEquipment = Item;
				OnUpdateMesh.Broadcast(Item, ESkeletalMeshMergeType::Hands);
				break;

			case EEquipSlot::Legs:
				Equipment.ItemEquipment = Item;
				OnUpdateMesh.Broadcast(Item, ESkeletalMeshMergeType::Legs);
				break;

			case EEquipSlot::Feet:
				Equipment.ItemEquipment = Item;
				OnUpdateMesh.Broadcast(Item, ESkeletalMeshMergeType::Feet);
				break;
		}

		Equipment.ItemEquipment = Item;
		SetGameplayEffects(Equipment.ActiveGEHandle, Equipment.ItemEquipment);
		OnItemEquipped.Broadcast(Item, EquipSlot);
		OnRep_EquippedItems();
		
		return;
	}
	return;
}

bool UXIEquipmentManagerComponent::Server_UnEquipItem_Validate(EEquipSlot EquipSlot)
{
	return true;
}

void UXIEquipmentManagerComponent::Server_UnEquipItem_Implementation(EEquipSlot EquipSlot)
{
	for(auto& Equipment : EquippedItems)
	{
		if(Equipment.EquipSlot == EquipSlot)
		{
			switch(EquipSlot)
			{
				case EEquipSlot::MainHand:
					Equipment.ItemEquipment = nullptr;
					SetGameplayEffectAttackDelay(GetAttackDelay(true), AGEMeleeDelayTags, true);
					OnUpdateMesh.Broadcast(nullptr, ESkeletalMeshMergeType::MainHand);
					CheckCombatStyle();
					break;
				
				case EEquipSlot::SubHand:
					Equipment.ItemEquipment = nullptr;
					SetGameplayEffectAttackDelay(GetAttackDelay(true), AGEMeleeDelayTags, true);
					OnUpdateMesh.Broadcast(nullptr, ESkeletalMeshMergeType::SubHand);
					CheckCombatStyle();
					break;

				case EEquipSlot::Ranged:
					Equipment.ItemEquipment = nullptr;
					SetGameplayEffectAttackDelay(GetAttackDelay(false), AGERangeDelayTags, false);
					OnUpdateMesh.Broadcast(nullptr, ESkeletalMeshMergeType::Range);
					break;

				case EEquipSlot::Head:
					Equipment.ItemEquipment = nullptr;
					OnUpdateMesh.Broadcast(nullptr, ESkeletalMeshMergeType::Head);
					break;

				case EEquipSlot::Body:
					Equipment.ItemEquipment = nullptr;
					OnUpdateMesh.Broadcast(nullptr, ESkeletalMeshMergeType::Body);
					break;

				case EEquipSlot::Hands:
					Equipment.ItemEquipment = nullptr;
					OnUpdateMesh.Broadcast(nullptr, ESkeletalMeshMergeType::Hands);
					break;

				case EEquipSlot::Legs:
					Equipment.ItemEquipment = nullptr;
					OnUpdateMesh.Broadcast(nullptr, ESkeletalMeshMergeType::Legs);
					break;

				case EEquipSlot::Feet:
					Equipment.ItemEquipment = nullptr;
					OnUpdateMesh.Broadcast(nullptr, ESkeletalMeshMergeType::Feet);
					break;
			}

			Equipment.ItemEquipment = nullptr;
			SetGameplayEffects(Equipment.ActiveGEHandle, nullptr);
			OnItemEquipped.Broadcast(nullptr, EquipSlot);
			OnRep_EquippedItems();
		}
	}
}

UItemEquipment* UXIEquipmentManagerComponent::FindEquippedItemBySlot(EEquipSlot EquipSlot) const
{
	for(auto& EquippedItem : EquippedItems)
	{
		if(EquippedItem.EquipSlot == EquipSlot)
		{
			return EquippedItem.ItemEquipment;
		}
	}
	return nullptr;
}

ECombatStyle UXIEquipmentManagerComponent::CheckCombatStyle()
{
	UItemEquipment* MainHand = FindEquippedItemBySlot(EEquipSlot::MainHand);
	UItemEquipment* SubHand = FindEquippedItemBySlot(EEquipSlot::SubHand);

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
		if(CombatStyleReference != ECombatStyle::Unarmed)
		{
			CombatStyleReference = ECombatStyle::Unarmed;
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
}
