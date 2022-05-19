// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventorySystem/ItemEquipment.h"
#include "GameplayEffectTypes.h"
#include "XIEquipmentManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpdateMesh, UItemEquipment*, Item, ESkeletalMeshMergeType, SKMeshMergeType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCombatStyleChanged, ECombatStyle, CombatStyle);

USTRUCT(BlueprintType)
struct XIREMIX_API FXIEquippedItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EEquipSlot EquipSlot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UItemEquipment* ItemEquipment;

	UPROPERTY()
	FActiveGameplayEffectHandle ActiveGEHandle;

	FXIEquippedItem()
	{
		EquipSlot = EEquipSlot::MainHand;
		ItemEquipment = nullptr;
	}

	FXIEquippedItem(EEquipSlot InEquipSlot, UItemEquipment* InItem)
	{
		EquipSlot = InEquipSlot;
		ItemEquipment = InItem;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class XIREMIX_API UXIEquipmentManagerComponent : public UActorComponent
{
	GENERATED_BODY()

	friend class AXICharacterBaseHero;

public:	
	// Sets default values for this component's properties
	UXIEquipmentManagerComponent();

	UFUNCTION(BlueprintPure, Category = "XIEquipmentManager")
	FORCEINLINE TArray<FXIEquippedItem> GetEquippedItems() const { return EquippedItems; };

	UFUNCTION(BlueprintPure, Category = "XIEquipmentManager")
	UItemEquipment* FindEquippedItemBySlot(EEquipSlot EquipSlot) const;

	UFUNCTION(BlueprintPure, Category = "XIEquipmentManager")
	bool IsItemEquipable(UItem* Item) const;

	/**Server equips the item.*/
	UFUNCTION(BlueprintCallable, Category = "XIEquipmentManager")
	void EquipItem(UItem* Item, EEquipSlot EquipSlot);

	UFUNCTION(Server, WithValidation, Reliable)
	void Server_EquipItem(UItem* Item, EEquipSlot EquipSlot);

	/**Server un-equips the item.*/
	UFUNCTION(BlueprintCallable, Category = "XIEquipmentManager")
	void UnEquipItem(EEquipSlot EquipSlot);

	UFUNCTION(Server, WithValidation, Reliable)
	void Server_UnEquipItem(EEquipSlot EquipSlot);

	UPROPERTY(BlueprintAssignable)
	FUpdateMesh OnUpdateMesh;

	UPROPERTY(BlueprintAssignable)
	FEquipmentUpdated OnEquipmentUpdated;

	UPROPERTY(BlueprintAssignable)
	FCombatStyleChanged OnCombatStyleChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;

	// Sets attributes for any equippable item. Use the Melee and Ranged versions to apply Delay.
	void SetGameplayEffects(FActiveGameplayEffectHandle& AGEHandle, UItemEquipment* Item);

	// Sets the attack delay
	void SetGameplayEffectAttackDelay(float Delay, FActiveGameplayEffectHandle& AGEHandle, bool bIsMelee);

	float GetAttackDelay(bool bIsMelee) const;

	// Sets every SetByCaller value to 0. Avoiding runtime errors.
	void InitializeSpecSetByCaller(FGameplayEffectSpec* InSpec);

	// Sets the gameplay effects for all equipped Items.
	void InitializeEquippedItems();

	ECombatStyle CheckCombatStyle();

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_EquippedItems, Category = "Equipment")
	TArray<FXIEquippedItem> EquippedItems;
	UFUNCTION()
	void OnRep_EquippedItems();

	UPROPERTY(BlueprintReadOnly, Category = "Equipment")
	ECombatStyle CombatStyleReference;

	// The Infinite Gameplay Effect Class for modifying Attributes
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects")
	TSubclassOf<class UGameplayEffect> GEEquipment;

	// The Instant Gameplay Effect Class for Melee weapon Delay
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects")
	TSubclassOf<class UGameplayEffect> GEMeleeAttackDelay;

	// The Instant Gameplay Effect Class for Ranged attack Delay
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects")
	TSubclassOf<class UGameplayEffect> GERangeAttackDelay;

	// A blank Infinite Gameplay Effect Class to apply Weapon Tags
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects")
	TSubclassOf<class UGameplayEffect> GEWeaponTags;

	UPROPERTY(BlueprintReadOnly)
	class AXICharacterBaseHero* HeroCharacter;

	// Owner's ASC
	UPROPERTY(BlueprintReadOnly)
	class UAbilitySystemComponent* AbilitySystemComponent;

	// Used to apply weapon type Tags
	FActiveGameplayEffectHandle AGEMeleeDelayTags;
	FActiveGameplayEffectHandle AGERangeDelayTags;

	//The parent tag of the setbycaller equipment tags.
	UPROPERTY(EditDefaultsOnly, meta = (Categories="SetByCaller"))
	FGameplayTag SetByCallerParent = FGameplayTag::RequestGameplayTag("SetByCaller.Attributes");
	UPROPERTY()
	TArray<FGameplayTag> SetByCallerChildTags;

	/*
	// GameplayTags for Comparison
	*/
	FGameplayTag DualWield = FGameplayTag::RequestGameplayTag("Passive.DualWield");
	FGameplayTag DualWielding = FGameplayTag::RequestGameplayTag("State.Gameplay.DualWielding");
	FGameplayTag NoHeadGear = FGameplayTag::RequestGameplayTag("Passive.NoHeadGear");

private:

	UPROPERTY()
	int32 ReplicatedItemsKey;

};
