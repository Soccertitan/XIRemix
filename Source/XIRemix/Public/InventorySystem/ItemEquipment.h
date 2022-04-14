// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InventorySystem/Item.h"
#include "ItemEquipment.generated.h"

USTRUCT(BlueprintType)
struct XIREMIX_API FXISKMeshEquipment
{
	GENERATED_BODY()
 
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERace Race;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* Mesh;

};

USTRUCT(BlueprintType)
struct XIREMIX_API FXIGrantedAttribute
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories="SetByCaller.Attributes"))
	FGameplayTag AttributeTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;
};

/**
 * 
 */
UCLASS()
class XIREMIX_API UItemEquipment : public UItem
{
	GENERATED_BODY()

public:

	UItemEquipment();

	USkeletalMesh* GetMesh(ERace Race, bool bWeaponInSubHand);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|Equipment")
	TArray<EEquipSlot> EquipSlot;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|Equipment")
	float LevelRequirement;

	/* Leave empty to include all Jobs*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|Equipment", meta = (Categories="State.Job"))
	FGameplayTagContainer JobRequirements;

	/*
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|Equipment")
	FGameplayTagContainer SpecialTraits;
	*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|Equipment|Attributes", meta = (EditCondition="ItemType == EItemType::WeaponMelee || ItemType == EItemType::WeaponRange || ItemType == EItemType::Ammo", EditConditionHides))
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|Equipment|Attributes", meta = (EditCondition="ItemType == EItemType::WeaponMelee || ItemType == EItemType::WeaponRange || ItemType == EItemType::Ammo", EditConditionHides))
	float Delay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|Equipment|Attributes", meta = (EditCondition="ItemType == EItemType::WeaponMelee || ItemType == EItemType::WeaponRange || ItemType == EItemType::Ammo", EditConditionHides, Categories="Weapon"))
	FGameplayTag WeaponType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|Equipment|Attributes", meta = (EditCondition="ItemType == EItemType::WeaponMelee || ItemType == EItemType::WeaponRange || ItemType == EItemType::Ammo", EditConditionHides, Categories="DamageType"))
	FGameplayTagContainer DamageTypes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|Equipment|Attributes", meta = (EditCondition="ItemType == EItemType::WeaponMelee", EditConditionHides))
	ECombatStyle CombatStyle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|Equipment|Attributes")
	TArray<FXIGrantedAttribute> Attributes;

	UPROPERTY(BlueprintReadWrite, Category = "Item|Equipment")
	bool bIsEquipped;

protected:

	//For any item that can only be 'equipped' into a single slot.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|Equipment|Mesh")
	TArray<FXISKMeshEquipment> SKMeshDefault;

	// For One Handed weapons that can be equipped in the SubHand in addtion to MainHand.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item|Equipment|Mesh")
	TArray<FXISKMeshEquipment> SKMeshWeaponSubHand;
};
