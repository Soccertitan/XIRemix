// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/XIItem.h"
#include "GameplayTagContainer.h"
#include "DataAssets/XIJobTagCollection.h"
#include "XIItemEquipment.generated.h"

USTRUCT(BlueprintType)
struct XIREMIX_API FXIEquipmentSKMeshMap
{
	GENERATED_BODY()
 
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ERace Race;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMesh* Default;

	// Skeletal Mesh for Hand-2-Hand and one handed weapons.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMesh* SubHand;

};

USTRUCT(BlueprintType)
struct XIREMIX_API FXIWeaponMontageMap
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ERace Race;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* CombatStart;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* CombatExit;

};

USTRUCT(BlueprintType)
struct XIREMIX_API FXIItemAttributes
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories="SetByCaller.Attributes"))
	FGameplayTag AttributeTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Value;
};

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew)
class XIREMIX_API UXIItemEquipment : public UXIItem
{
	GENERATED_BODY()

public:

	UXIItemEquipment();

	//Gets the default mesh for an equipment item.
	USkeletalMesh* GetMesh(ERace Race);
	USkeletalMesh* GetMesh(ERace Race, bool bWeaponInSubHand);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Equipment")
	TArray<EEquipSlot> EquipSlot;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Equipment")
	float LevelRequirement;

	/* Leave empty to include all Jobs*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Equipment")
	UXIJobTagCollection* JobRequirements;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Equipment")
	FGameplayTagContainer GrantedTags;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Equipment|Attributes", meta = (EditCondition="ItemType == EItemType::WeaponMelee || ItemType == EItemType::WeaponRange || ItemType == EItemType::Ammo", EditConditionHides))
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Equipment|Attributes", meta = (EditCondition="ItemType == EItemType::WeaponMelee || ItemType == EItemType::WeaponRange || ItemType == EItemType::Ammo", EditConditionHides))
	float Delay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Equipment|Attributes", meta = (EditCondition="ItemType == EItemType::WeaponMelee || ItemType == EItemType::WeaponRange || ItemType == EItemType::Instrument || ItemType == EItemType::Ammo", EditConditionHides, Categories="Weapon"))
	FGameplayTag WeaponType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Equipment|Attributes", meta = (EditCondition="ItemType == EItemType::WeaponMelee || ItemType == EItemType::WeaponRange || ItemType == EItemType::Ammo", EditConditionHides, Categories="DamageType"))
	FGameplayTagContainer DamageTypes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Equipment|Attributes")
	TArray<FXIItemAttributes> Attributes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Equipment|Animation", meta = (EditCondition="ItemType == EItemType::WeaponMelee", EditConditionHides))
	ECombatStyle CombatStyle;

	/**The Equipment component that has this item equipped*/
	UPROPERTY()
	class UXIEquipmentManagerComponent* OwningEquipmentManager;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Equipment|Animation", meta = (EditCondition="ItemType == EItemType::WeaponMelee", EditConditionHides))
	TArray<FXIWeaponMontageMap> WeaponMontageMap;

	//For any item that can only be 'equipped' into a single slot.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Equipment|Mesh", meta = (EditCondition="ItemType == EItemType::WeaponMelee || ItemType == EItemType::WeaponRange || ItemType == EItemType::Shield || ItemType == EItemType::Instrument || ItemType == EItemType::Armor", EditConditionHides))
	TArray<FXIEquipmentSKMeshMap> SKMeshMap;	
};
