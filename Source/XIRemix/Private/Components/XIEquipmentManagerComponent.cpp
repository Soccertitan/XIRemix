// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/XIEquipmentManagerComponent.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagsManager.h"
#include "Characters/XICharacterBaseHero.h"

// Sets default values for this component's properties
UXIEquipmentManagerComponent::UXIEquipmentManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UXIEquipmentManagerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UXIEquipmentManagerComponent, MainHand, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXIEquipmentManagerComponent, SubHand, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXIEquipmentManagerComponent, Ranged, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXIEquipmentManagerComponent, Ammo, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXIEquipmentManagerComponent, Head, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXIEquipmentManagerComponent, Neck, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXIEquipmentManagerComponent, Ear1, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXIEquipmentManagerComponent, Ear2, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXIEquipmentManagerComponent, Body, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXIEquipmentManagerComponent, Hands, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXIEquipmentManagerComponent, Ring1, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXIEquipmentManagerComponent, Ring2, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXIEquipmentManagerComponent, Back, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXIEquipmentManagerComponent, Waist, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXIEquipmentManagerComponent, Legs, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXIEquipmentManagerComponent, Feet, COND_None, REPNOTIFY_Always);
}

// Called when the game starts
void UXIEquipmentManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	SetIsReplicated(true);

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

				AGEHandle = AbilitySystemComponent->BP_ApplyGameplayEffectSpecToSelf(GEC);
			}
		}
	}
}

void UXIEquipmentManagerComponent::SetGameplayEffectMeleeDelay()
{
	if(GetOwnerRole() != ROLE_Authority || !GEMeleeDelay)
	{
		return;
	}

	float Delay = 340.f;

	if(AbilitySystemComponent)
	{
		// Removes the old Gameplay Effect
		AbilitySystemComponent->RemoveActiveGameplayEffect(AGEMeleeDelay);

		if(MainHand)
		{
			if(MainHand->ItemType == EItemType::WeaponMelee)
			{
				Delay = MainHand->Delay;
			}
		}

		if(SubHand)
		{
			if(SubHand->ItemType == EItemType::WeaponMelee)
			{
				Delay = FMath::Floor((Delay + SubHand->Delay) / 2.f);
			}
		}

		Delay = Delay / 60.f;

		if (MainHand || SubHand)
		{
			FGameplayEffectContextHandle GECH;
			FGameplayEffectSpecHandle GEC = AbilitySystemComponent->MakeOutgoingSpec(GEMeleeDelay, 1.f, GECH);
			FGameplayEffectSpec* Spec = GEC.Data.Get();

			if (Spec)
			{
				Spec->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag("SetByCaller.Attributes.AttackSpeed"), Delay);
				AGEMeleeDelay = AbilitySystemComponent->BP_ApplyGameplayEffectSpecToSelf(GEC);
			}
		}
	}
}

void UXIEquipmentManagerComponent::SetGameplayEffectRangeDelay()
{
	if(GetOwnerRole() != ROLE_Authority || !GERangeDelay)
	{
		return;
	}

	if(AbilitySystemComponent)
	{
		// Removes the old Gameplay Effect
		AbilitySystemComponent->RemoveActiveGameplayEffect(AGERangeDelay);

		float Delay = 340.f;

		if(Ranged)
		{
			if(Ranged->ItemType == EItemType::WeaponRange)
			{
				Delay = Ranged->Delay;
				Delay = Delay / 110.f;

				FGameplayEffectContextHandle GECH;
				FGameplayEffectSpecHandle GEC = AbilitySystemComponent->MakeOutgoingSpec(GERangeDelay, 1.f, GECH);
				FGameplayEffectSpec* Spec = GEC.Data.Get();

				if (Spec)
				{
					Spec->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag("SetByCaller.Attributes.RangedAttackSpeed"), Delay);
					AGERangeDelay = AbilitySystemComponent->BP_ApplyGameplayEffectSpecToSelf(GEC);
				}
			}
		}
	}
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
	if(!HeroCharacter)
	{
		return false;
	}

	FXICharacterHeroActiveJobsLevels CharacterJobsLevels;
	CharacterJobsLevels = HeroCharacter->GetCharacterActiveJobsAndLevels();

	if((CharacterJobsLevels.MainJobLevel >= Item->LevelRequirement && Item->JobRequirements.HasTagExact(CharacterJobsLevels.MainJobTag)) || (CharacterJobsLevels.SubJobLevel >= Item->LevelRequirement && Item->JobRequirements.HasTagExact(CharacterJobsLevels.SubJobTag)))
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
	if(!Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("The Item to equip is invalid."));
		return;
	}

	switch (EquipSlot)
	{
		case EEquipSlot::MainHand:
			if(Item->EquipSlot.Contains(EEquipSlot::MainHand) && IsItemEquipable(Item))
			{
				if(!Item->EquipSlot.Contains(EEquipSlot::SubHand))
				{
					SubHand = nullptr;
					SetGameplayEffects(AGESubHand, SubHand);
					OnRep_SubHand();
				}
				MainHand = Item;
				CheckCombatStyle();
				SetGameplayEffects(AGEMainHand, MainHand);
				SetGameplayEffectMeleeDelay();
				OnRep_MainHand();
			}
			break;

		case EEquipSlot::SubHand:
			if(Item->EquipSlot.Contains(EEquipSlot::SubHand) && IsItemEquipable(Item))
			{
				if(!MainHand->EquipSlot.Contains(EEquipSlot::SubHand))
				{
					MainHand = nullptr;
					SetGameplayEffects(AGEMainHand, MainHand);
					OnRep_MainHand();
				}
				SubHand = Item;
				CheckCombatStyle();
				SetGameplayEffects(AGESubHand, SubHand);
				SetGameplayEffectMeleeDelay();
				OnRep_SubHand();
			}
			break;

		case EEquipSlot::Ranged:
			if(Item->EquipSlot.Contains(EEquipSlot::Ranged) && IsItemEquipable(Item))
			{
				Ranged = Item;
				SetGameplayEffects(AGERanged, Ranged);
				SetGameplayEffectRangeDelay();
				OnRep_Ranged();
			}
			break;

		case EEquipSlot::Ammo:
			if(Item->EquipSlot.Contains(EEquipSlot::Ammo) && IsItemEquipable(Item))
			{
				Ammo = Item;
				SetGameplayEffects(AGEAmmo, Ammo);
				OnRep_Ammo();
			}
			break;

		case EEquipSlot::Head:
			if(Item->EquipSlot.Contains(EEquipSlot::Head) && IsItemEquipable(Item))
			{
				Head = Item;
				SetGameplayEffects(AGEHead, Head);
				OnRep_Head();
			}
			break;

		case EEquipSlot::Neck:
			if(Item->EquipSlot.Contains(EEquipSlot::Neck) && IsItemEquipable(Item))
			{
				Neck = Item;
				SetGameplayEffects(AGENeck, Neck);
				OnRep_Neck();
			}
			break;

		case EEquipSlot::Ear1:
			if(Item->EquipSlot.Contains(EEquipSlot::Ear1) && IsItemEquipable(Item))
			{
				Ear1 = Item;
				SetGameplayEffects(AGEEar1, Ear1);
				OnRep_Ear1();
			}
			break;

		case EEquipSlot::Ear2:
			if(Item->EquipSlot.Contains(EEquipSlot::Ear2) && IsItemEquipable(Item))
			{
				Ear2 = Item;
				SetGameplayEffects(AGEEar2, Ear2);
				OnRep_Ear2();
			}
			break;

		case EEquipSlot::Body:
			if(Item->EquipSlot.Contains(EEquipSlot::Body) && IsItemEquipable(Item))
			{
				Body = Item;
				SetGameplayEffects(AGEBody, Body);
				OnRep_Body();
			}
			break;

		case EEquipSlot::Hands:
			if(Item->EquipSlot.Contains(EEquipSlot::Hands) && IsItemEquipable(Item))
			{
				Hands = Item;
				SetGameplayEffects(AGEHands, Hands);
				OnRep_Hands();
			}
			break;

		case EEquipSlot::Ring1:
			if(Item->EquipSlot.Contains(EEquipSlot::Ring1) && IsItemEquipable(Item))
			{
				Ring1 = Item;
				SetGameplayEffects(AGERing1, Ring1);
				OnRep_Ring1();
			}
			break;

		case EEquipSlot::Ring2:
			if(Item->EquipSlot.Contains(EEquipSlot::Ring2) && IsItemEquipable(Item))
			{
				Ring2 = Item;
				SetGameplayEffects(AGERing2, Ring2);
				OnRep_Ring2();
			}
			break;

		case EEquipSlot::Back:
			if(Item->EquipSlot.Contains(EEquipSlot::Back) && IsItemEquipable(Item))
			{
				Back = Item;
				SetGameplayEffects(AGEBack, Back);
				OnRep_Back();
			}
			break;

		case EEquipSlot::Waist:
			if(Item->EquipSlot.Contains(EEquipSlot::Waist) && IsItemEquipable(Item))
			{
				Waist = Item;
				SetGameplayEffects(AGEWaist, Waist);
				OnRep_Waist();
			}
			break;

		case EEquipSlot::Legs:
			if(Item->EquipSlot.Contains(EEquipSlot::Legs) && IsItemEquipable(Item))
			{
				Legs = Item;
				SetGameplayEffects(AGELegs, Legs);
				OnRep_Legs();
			}
			break;

		case EEquipSlot::Feet:
			if(Item->EquipSlot.Contains(EEquipSlot::Feet) && IsItemEquipable(Item))
			{
				Feet = Item;
				SetGameplayEffects(AGEFeet, Feet);
				OnRep_Feet();
			}
			break;
	}
	return;
}

bool UXIEquipmentManagerComponent::Server_UnEquipItem_Validate(EEquipSlot EquipSlot)
{
	return true;
}

void UXIEquipmentManagerComponent::Server_UnEquipItem_Implementation(EEquipSlot EquipSlot)
{
	switch (EquipSlot)
	{
		case EEquipSlot::MainHand:
			MainHand = nullptr;
			CheckCombatStyle();
			SetGameplayEffects(AGEMainHand, MainHand);
			SetGameplayEffectMeleeDelay();
			OnRep_MainHand();
			break;
		case EEquipSlot::SubHand:
			SubHand = nullptr;
			CheckCombatStyle();
			SetGameplayEffects(AGESubHand, SubHand);
			SetGameplayEffectMeleeDelay();
			OnRep_SubHand();
			break;
		case EEquipSlot::Ranged:
			Ranged = nullptr;
			SetGameplayEffects(AGERanged, Ranged);
			SetGameplayEffectRangeDelay();
			OnRep_Ranged();
			break;
		case EEquipSlot::Ammo:
			Ammo = nullptr;
			SetGameplayEffects(AGEAmmo, Ammo);
			OnRep_Ammo();
			break;
		case EEquipSlot::Head:
			Head = nullptr;
			SetGameplayEffects(AGEHead, Head);
			OnRep_Head();
			break;
		case EEquipSlot::Neck:
			Neck = nullptr;
			SetGameplayEffects(AGENeck, Neck);
			OnRep_Neck();
			break;
		case EEquipSlot::Ear1:
			Ear1 = nullptr;
			SetGameplayEffects(AGEEar1, Ear1);
			OnRep_Ear1();
			break;
		case EEquipSlot::Ear2:	
			Ear2 = nullptr;
			SetGameplayEffects(AGEEar2, Ear2);
			OnRep_Ear2();
			break;
		case EEquipSlot::Body:	
			Body = nullptr;
			SetGameplayEffects(AGEBody, Body);
			OnRep_Body();
			break;
		case EEquipSlot::Hands:
			Hands = nullptr;
			SetGameplayEffects(AGEHands, Hands);
			OnRep_Hands();
			break;
		case EEquipSlot::Ring1:
			Ring1 = nullptr;
			SetGameplayEffects(AGERing1, Ring1);
			OnRep_Ring1();
			break;
		case EEquipSlot::Ring2:
			Ring2 = nullptr;
			SetGameplayEffects(AGERing2, Ring2);
			OnRep_Ring2();
			break;
		case EEquipSlot::Back:
			Back = nullptr;
			SetGameplayEffects(AGEBack, Back);
			OnRep_Back();
			break;
		case EEquipSlot::Waist:
			Waist = nullptr;
			SetGameplayEffects(AGEWaist, Waist);
			OnRep_Waist();
			break;
		case EEquipSlot::Legs:
			Legs = nullptr;
			SetGameplayEffects(AGELegs, Legs);
			OnRep_Legs();
			break;
		case EEquipSlot::Feet:
			Feet = nullptr;
			SetGameplayEffects(AGEFeet, Feet);
			OnRep_Feet();
			break;
	}
}

FXIEquippedItemsReference UXIEquipmentManagerComponent::GetEquippedItems() const
{
	return EquipmentReference;
}

UItemEquipment* UXIEquipmentManagerComponent::GetMainHandItem() const
{
	return MainHand;
}

UItemEquipment* UXIEquipmentManagerComponent::GetSubHandItem() const
{
	return SubHand;
}

UItemEquipment* UXIEquipmentManagerComponent::GetRangedItem() const
{
	return Ranged;
}

UItemEquipment* UXIEquipmentManagerComponent::GetAmmoItem() const
{
	return Ammo;
}

ECombatStyle UXIEquipmentManagerComponent::CheckCombatStyle()
{
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
	SetGameplayEffects(AGEMainHand, MainHand);
	SetGameplayEffects(AGESubHand, SubHand);
	SetGameplayEffects(AGERanged, Ranged);
	SetGameplayEffects(AGEAmmo, Ammo);
	SetGameplayEffects(AGEHead, Head);
	SetGameplayEffects(AGENeck, Neck);
	SetGameplayEffects(AGEEar1, Ear1);
	SetGameplayEffects(AGEEar2, Ear2);
	SetGameplayEffects(AGEBody, Body);
	SetGameplayEffects(AGEHands, Hands);
	SetGameplayEffects(AGERing1, Ring1);
	SetGameplayEffects(AGERing2, Ring2);
	SetGameplayEffects(AGEBack, Back);
	SetGameplayEffects(AGEWaist, Waist);
	SetGameplayEffects(AGELegs, Legs);
	SetGameplayEffects(AGEFeet, Feet);
	SetGameplayEffectMeleeDelay();
	SetGameplayEffectRangeDelay();
	CheckCombatStyle();
}

#pragma region OnRepFunctions

void UXIEquipmentManagerComponent::OnRep_MainHand()
{
	EquipmentReference.MainHand = MainHand;
	OnMeshUpdated.Broadcast(MainHand, ESkeletalMeshMergeType::MainHand);
	OnItemChanged.Broadcast(MainHand, EEquipSlot::MainHand);
}

void UXIEquipmentManagerComponent::OnRep_SubHand()
{
	EquipmentReference.SubHand = SubHand;
	OnMeshUpdated.Broadcast(SubHand, ESkeletalMeshMergeType::SubHand);
	OnItemChanged.Broadcast(SubHand, EEquipSlot::SubHand);
}

void UXIEquipmentManagerComponent::OnRep_Ranged()
{
	EquipmentReference.Ranged = Ranged;
	OnMeshUpdated.Broadcast(Ranged, ESkeletalMeshMergeType::Range);
	OnItemChanged.Broadcast(Ranged, EEquipSlot::Ranged);
}

void UXIEquipmentManagerComponent::OnRep_Ammo()
{
	EquipmentReference.Ammo = Ammo;
	OnItemChanged.Broadcast(Ammo, EEquipSlot::Ammo);
}

void UXIEquipmentManagerComponent::OnRep_Head()
{
	EquipmentReference.Head = Head;
	OnMeshUpdated.Broadcast(Head, ESkeletalMeshMergeType::Head);
	OnItemChanged.Broadcast(Head, EEquipSlot::Head);
}

void UXIEquipmentManagerComponent::OnRep_Neck()
{
	EquipmentReference.Neck = Neck;
	OnItemChanged.Broadcast(Neck, EEquipSlot::Neck);
}

void UXIEquipmentManagerComponent::OnRep_Ear1()
{
	EquipmentReference.Ear1 = Ear1;
	OnItemChanged.Broadcast(Ear1, EEquipSlot::Ear1);
}

void UXIEquipmentManagerComponent::OnRep_Ear2()
{
	EquipmentReference.Ear2 = Ear2;
	OnItemChanged.Broadcast(Ear2, EEquipSlot::Ear2);
}

void UXIEquipmentManagerComponent::OnRep_Body()
{
	EquipmentReference.Body = Body;
	OnMeshUpdated.Broadcast(Body, ESkeletalMeshMergeType::Body);
	OnItemChanged.Broadcast(Body, EEquipSlot::Body);
}

void UXIEquipmentManagerComponent::OnRep_Hands()
{
	EquipmentReference.Hands = Hands;
	OnMeshUpdated.Broadcast(Hands, ESkeletalMeshMergeType::Hands);
	OnItemChanged.Broadcast(Hands, EEquipSlot::Hands);
}

void UXIEquipmentManagerComponent::OnRep_Ring1()
{
	EquipmentReference.Ring1 = Ring1;
	OnItemChanged.Broadcast(Ring1, EEquipSlot::Ring1);
}

void UXIEquipmentManagerComponent::OnRep_Ring2()
{
	EquipmentReference.Ring2 = Ring2;
	OnItemChanged.Broadcast(Ring2, EEquipSlot::Ring2);
}

void UXIEquipmentManagerComponent::OnRep_Back()
{
	EquipmentReference.Back = Back;
	OnItemChanged.Broadcast(Back, EEquipSlot::Back);
}

void UXIEquipmentManagerComponent::OnRep_Waist()
{
	EquipmentReference.Waist = Waist;
	OnItemChanged.Broadcast(Waist, EEquipSlot::Waist);
}

void UXIEquipmentManagerComponent::OnRep_Legs()
{
	EquipmentReference.Legs = Legs;
	OnMeshUpdated.Broadcast(Legs, ESkeletalMeshMergeType::Legs);
	OnItemChanged.Broadcast(Legs, EEquipSlot::Legs);
}

void UXIEquipmentManagerComponent::OnRep_Feet()
{
	EquipmentReference.Feet = Feet;
	OnMeshUpdated.Broadcast(Feet, ESkeletalMeshMergeType::Feet);
	OnItemChanged.Broadcast(Feet, EEquipSlot::Feet);
}	

#pragma endregion OnRepFunctions
	