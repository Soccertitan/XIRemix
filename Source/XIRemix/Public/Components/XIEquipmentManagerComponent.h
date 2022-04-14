// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventorySystem/ItemEquipment.h"
#include "GameplayEffectTypes.h"
#include "XIEquipmentManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMeshUpdated, UItemEquipment*, Item, ESkeletalMeshMergeType, SKMeshMergeType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FItemChanged, UItemEquipment*, Item, EEquipSlot, EquipSlot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCombatStyleChanged, ECombatStyle, CombatStyle);

USTRUCT(BlueprintType)
struct XIREMIX_API FXIEquippedItemsReference
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemEquipment* MainHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemEquipment* SubHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemEquipment* Ranged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemEquipment* Ammo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemEquipment* Head;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemEquipment* Neck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemEquipment* Ear1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemEquipment* Ear2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemEquipment* Body;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemEquipment* Hands;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemEquipment* Ring1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemEquipment* Ring2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemEquipment* Back;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemEquipment* Waist;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemEquipment* Legs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemEquipment* Feet;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class XIREMIX_API UXIEquipmentManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UXIEquipmentManagerComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintPure, Category = "XIEquipmentManager")
	FXIEquippedItemsReference GetEquippedItems() const;

	UFUNCTION(BlueprintPure, Category = "XIEquipmentManager")
	UItemEquipment* GetMainHandItem() const;

	UFUNCTION(BlueprintPure, Category = "XIEquipmentManager")
	UItemEquipment* GetSubHandItem() const;

	UFUNCTION(BlueprintPure, Category = "XIEquipmentManager")
	UItemEquipment* GetRangedItem() const;

	UFUNCTION(BlueprintPure, Category = "XIEquipmentManager")
	UItemEquipment* GetAmmoItem() const;

	UFUNCTION(BlueprintPure, Category = "XIEquipmentManager")
	bool IsItemEquipable(UItemEquipment* Item) const;

	// Equips an item to a character.
	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = "XIEquipmentManager")
	void Server_EquipItem(UItemEquipment* Item, EEquipSlot EquipSlot);
	bool Server_EquipItem_Validate(UItemEquipment* Item, EEquipSlot EquipSlot);
	void Server_EquipItem_Implementation(UItemEquipment* Item, EEquipSlot EquipSlot);

	// Unequips an Item from a Character.
	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = "XIEquipmentManager")
	void Server_UnEquipItem(EEquipSlot EquipSlot);
	bool Server_UnEquipItem_Validate(EEquipSlot EquipSlot);
	void Server_UnEquipItem_Implementation(EEquipSlot EquipSlot);

	UPROPERTY(BlueprintAssignable)
	FMeshUpdated OnMeshUpdated;

	UPROPERTY(BlueprintAssignable)
	FItemChanged OnItemChanged;

	UPROPERTY(BlueprintAssignable)
	FCombatStyleChanged OnCombatStyleChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Sets attributes for any equippable item. Use the Melee and Ranged versions to apply Delay.
	void SetGameplayEffects(FActiveGameplayEffectHandle& AGEHandle, UItemEquipment* Item);

	// Sets the Melee Delay
	void SetGameplayEffectMeleeDelay();

	// Sets the Range attack delay
	void SetGameplayEffectRangeDelay();

	// Sets every SetByCaller value to 0. Avoiding runtime errors.
	void InitializeSpecSetByCaller(FGameplayEffectSpec* InSpec);

	// Sets the gameplay effects for all equipped Items.
	void InitializeEquippedItems();

	ECombatStyle CheckCombatStyle();

	UPROPERTY(BlueprintReadOnly, Category = "Equipment")
	FXIEquippedItemsReference EquipmentReference;

	UPROPERTY(BlueprintReadOnly, Category = "Equipment")
	ECombatStyle CombatStyleReference;

	// The Gameplay Effect Class for basic Attributes
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UGameplayEffect> GEEquipment;

	// The Gameplay Effect Class for Melee weapon Delay
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UGameplayEffect> GEMeleeDelay;

	// The Gameplay Effect Class for Ranged attack Delay
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UGameplayEffect> GERangeDelay;

	UPROPERTY(BlueprintReadOnly)
	class AXICharacterBaseHero* HeroCharacter;

	// Owner's ASC
	UPROPERTY(BlueprintReadOnly)
	class UAbilitySystemComponent* AbilitySystemComponent;
	
	/*
	// The on rep functions and FActiveGameplayEffect for removing and adding Infinite GEs as items are equipped and removed.
	*/

	UPROPERTY(EditAnywhere, Instanced, ReplicatedUsing = OnRep_MainHand, Category = "Equipment")
	UItemEquipment* MainHand;
	UFUNCTION()
	void OnRep_MainHand();
	UPROPERTY()
	FActiveGameplayEffectHandle AGEMainHand;

	UPROPERTY(EditAnywhere, Instanced, ReplicatedUsing = OnRep_SubHand, Category = "Equipment")
	UItemEquipment* SubHand;
	UFUNCTION()
	void OnRep_SubHand();
	UPROPERTY()
	FActiveGameplayEffectHandle AGESubHand;

	UPROPERTY(EditAnywhere, Instanced, ReplicatedUsing = OnRep_Ranged, Category = "Equipment")
	UItemEquipment* Ranged;
	UFUNCTION()
	void OnRep_Ranged();
	UPROPERTY()
	FActiveGameplayEffectHandle AGERanged;

	UPROPERTY(EditAnywhere, Instanced, ReplicatedUsing = OnRep_Ammo, Category = "Equipment")
	UItemEquipment* Ammo;
	UFUNCTION()
	void OnRep_Ammo();
	UPROPERTY()
	FActiveGameplayEffectHandle AGEAmmo;

	UPROPERTY(EditAnywhere, Instanced, ReplicatedUsing = OnRep_Head, Category = "Equipment")
	UItemEquipment* Head;
	UFUNCTION()
	void OnRep_Head();
	UPROPERTY()
	FActiveGameplayEffectHandle AGEHead;

	UPROPERTY(EditAnywhere, Instanced, ReplicatedUsing = OnRep_Neck, Category = "Equipment")
	UItemEquipment* Neck;
	UFUNCTION()
	void OnRep_Neck();
	UPROPERTY()
	FActiveGameplayEffectHandle AGENeck;

	UPROPERTY(EditAnywhere, Instanced, ReplicatedUsing = OnRep_Ear1, Category = "Equipment")
	UItemEquipment* Ear1;
	UFUNCTION()
	void OnRep_Ear1();
	UPROPERTY()
	FActiveGameplayEffectHandle AGEEar1;

	UPROPERTY(EditAnywhere, Instanced, ReplicatedUsing = OnRep_Ear2, Category = "Equipment")
	UItemEquipment* Ear2;
	UFUNCTION()
	void OnRep_Ear2();
	UPROPERTY()
	FActiveGameplayEffectHandle AGEEar2;

	UPROPERTY(EditAnywhere, Instanced, ReplicatedUsing = OnRep_Body, Category = "Equipment")
	UItemEquipment* Body;
	UFUNCTION()
	void OnRep_Body();
	UPROPERTY()
	FActiveGameplayEffectHandle AGEBody;

	UPROPERTY(EditAnywhere, Instanced, ReplicatedUsing = OnRep_Hands, Category = "Equipment")
	UItemEquipment* Hands;
	UFUNCTION()
	void OnRep_Hands();
	UPROPERTY()
	FActiveGameplayEffectHandle AGEHands;

	UPROPERTY(EditAnywhere, Instanced, ReplicatedUsing = OnRep_Ring1, Category = "Equipment")
	UItemEquipment* Ring1;
	UFUNCTION()
	void OnRep_Ring1();
	UPROPERTY()
	FActiveGameplayEffectHandle AGERing1;

	UPROPERTY(EditAnywhere, Instanced, ReplicatedUsing = OnRep_Ring2, Category = "Equipment")
	UItemEquipment* Ring2;
	UFUNCTION()
	void OnRep_Ring2();
	UPROPERTY()
	FActiveGameplayEffectHandle AGERing2;

	UPROPERTY(EditAnywhere, Instanced, ReplicatedUsing = OnRep_Back, Category = "Equipment")
	UItemEquipment* Back;
	UFUNCTION()
	void OnRep_Back();
	UPROPERTY()
	FActiveGameplayEffectHandle AGEBack;

	UPROPERTY(EditAnywhere, Instanced, ReplicatedUsing = OnRep_Waist, Category = "Equipment")
	UItemEquipment* Waist;
	UFUNCTION()
	void OnRep_Waist();
	UPROPERTY()
	FActiveGameplayEffectHandle AGEWaist;

	UPROPERTY(EditAnywhere, Instanced, ReplicatedUsing = OnRep_Legs, Category = "Equipment")
	UItemEquipment* Legs;
	UFUNCTION()
	void OnRep_Legs();
	UPROPERTY()
	FActiveGameplayEffectHandle AGELegs;

	UPROPERTY(EditAnywhere, Instanced, ReplicatedUsing = OnRep_Feet, Category = "Equipment")
	UItemEquipment* Feet;
	UFUNCTION()
	void OnRep_Feet();
	UPROPERTY()
	FActiveGameplayEffectHandle AGEFeet;

	FActiveGameplayEffectHandle AGEMeleeDelay;
	FActiveGameplayEffectHandle AGERangeDelay;

	//The parent tag of the setbycaller equipment tags.
	UPROPERTY(EditDefaultsOnly, meta = (Categories="SetByCaller"))
	FGameplayTag SetByCallerParent = FGameplayTag::RequestGameplayTag("SetByCaller.Attributes");
	UPROPERTY()
	TArray<FGameplayTag> SetByCallerChildTags;

};
