// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameplayEffectTypes.h"
#include "XIEnums.h"
#include "XIRemix/XIRemix.h"
#include "Interfaces/XICharacterInterface.h"
#include "XICharacterBase.generated.h"

UCLASS()
class XIREMIX_API AXICharacterBase : public ACharacter, public IAbilitySystemInterface, public IXICharacterInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AXICharacterBase(const class FObjectInitializer& ObjectInitializer);

	// Implements the IXICharacter Interface
	// GetAutoAtkMontage is Implemented in C++
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "XICharacter|Montage")
	UAnimMontage* GetAutoAttackMontage(); virtual UAnimMontage* GetAutoAttackMontage_Implementation() override;

	// GetCharacterName is Implemented in C++
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "XICharacter|Attributes")
	FText GetCharacterName(); virtual FText GetCharacterName_Implementation() override;

	// GetMainTarget is Implemented in C++
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "XICharacter|Attributes")
	AActor* GetMainTarget(); virtual AActor* GetMainTarget_Implementation() override;

	// GetMainTarget is Implemented in C++
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "XICharacter|Attributes")
	AActor* GetSubTarget(); virtual AActor* GetSubTarget_Implementation() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// UPROPERTY(BlueprintAssignable, Category = "XICharacter")
	// FCharacterDiedDelegate OnCharacterDied;

	// Implement IAbilitySystemInterface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "XICharacter")
	virtual bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "XICharacter|Name")
	FText GetCharName() const;

	// Switch on AbilityID to return individual ability levels. Hardcoded to 1 for every ability in this project.
	UFUNCTION(BlueprintCallable, Category = "XICharacter|Abilities")
	virtual int32 GetAbilityLevel(EXIAbilityInputID AbilityID) const;

	// // Removes all CharacterAbilities. Can only be called by the Server. Removing on the Server will remove from Client too.
	// virtual void RemoveCharacterAbilities();

	// /**
	// * Getters for attributes from GlobalAttributeSet
	// **/
	UFUNCTION(BlueprintCallable, Category = "XICharacter|Attributes")
	float GetHitPoints() const;

	UFUNCTION(BlueprintCallable, Category = "XICharacter|Attributes")
	float GetHitPointsMax() const;

	UFUNCTION(BlueprintCallable, Category = "XICharacter|Attributes")
	float GetManaPoints() const;

	UFUNCTION(BlueprintCallable, Category = "XICharacter|Attributes")
	float GetManaPointsMax() const;

	UFUNCTION(BlueprintCallable, Category = "XICharacter|Attributes")
	float GetTacticalPoints() const;

	UFUNCTION(BlueprintCallable, Category = "XICharacter|Attributes")
	float GetTacticalPointsMax() const;
	
	// // Gets the Current value of MoveSpeed
	UFUNCTION(BlueprintCallable, Category = "XICharacter|Attributes")
	float GetMoveSpeed() const;

	UFUNCTION(BlueprintPure, Category = "XICharacter|AnimMontages")
	UAnimMontage* GetAutoAttackMontage_CPP();

	UFUNCTION(BlueprintPure, Category = "XICharacter|AnimMontages")
	UAnimMontage* GetCombatStartMontage();

	UFUNCTION(BlueprintPure, Category = "XICharacter|AnimMontages")
	UAnimMontage* GetCombatExitMontage();

	UFUNCTION(BlueprintPure, Category = "XICharacter|AnimMontages")
	UAnimMontage* GetRandomMontage(TArray <UAnimMontage*> AnimMontage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Replicated, Category = "XICharacter")
	FText CharacterName;

	UPROPERTY(BlueprintReadWrite, Category = "XICharacter|Combat")
	AActor* MainTarget;
	UPROPERTY(BlueprintReadWrite, Category = "XICharacter|Combat")
	AActor* SubTarget;

	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = "XICharacter|Name")
	void Server_SetCharacterName(const FText &Name);
	bool Server_SetCharacterName_Validate(FText Name);
	void Server_SetCharacterName_Implementation(FText Name);

	UPROPERTY()
	class UAbilitySystemComponentGlobal* AbilitySystemComponent;
	UPROPERTY()
	class UAttributeSetGlobal* AttributeSet;

	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	FDelegateHandle HitPointsChangedDelegateHandle;
	FDelegateHandle HitPointsMaxChangedDelegateHandle;

	// Attribute Change Callbacks
	virtual void HitPointsChanged(const FOnAttributeChangeData& Data);
	virtual void HitPointsMaxChanged(const FOnAttributeChangeData& Data);

	// Default abilities for this Character. These will be removed on Character death and regiven if Character respawns.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XICharacter|Abilities")
	TArray<TSubclassOf<class UGameplayAbilityGlobal>> CharacterAbilities;

	// Default attributes for a character for initializing on spawn/respawn.
	// This is an instant GE that overrides the values for attributes that get reset on spawn/respawn.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XICharacter|Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	// These effects are only applied one time on startup
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XICharacter|Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	// Grant abilities on the Server. The Ability Specs will be replicated to the owning client.
	virtual void AddCharacterAbilities();

	// Initialize the Character's attributes. Must run on Server but we run it on Client too
	// so that we don't have to wait. The Server's replication to the Client won't matter since
	// the values should be the same.
	virtual void InitializeAttributes();

	virtual void AddStartupEffects();

	#pragma region CombatMontages

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Unarmed")
	class UAnimMontage* UnarmedStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Unarmed")
	class UAnimMontage* UnarmedExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Unarmed")
	TArray <class UAnimMontage*> UnarmedBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Unarmed")
	class UAnimMontage* UnarmedAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Unarmed")
	class UAnimMontage* UnarmedAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Unarmed")
	class UAnimMontage* UnarmedAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Unarmed")
	class UAnimMontage* UnarmedAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Sword")
	class UAnimMontage* SwordStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Sword")
	class UAnimMontage* SwordExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Sword")
	TArray <class UAnimMontage*> SwordBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Sword")
	class UAnimMontage* SwordAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Sword")
	class UAnimMontage* SwordAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Sword")
	class UAnimMontage* SwordAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Sword")
	class UAnimMontage* SwordAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Axe")
	class UAnimMontage* AxeStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Axe")
	class UAnimMontage* AxeExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Axe")
	TArray <class UAnimMontage*> AxeBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Axe")
	class UAnimMontage* AxeAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Axe")
	class UAnimMontage* AxeAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Axe")
	class UAnimMontage* AxeAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Axe")
	class UAnimMontage* AxeAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Dagger")
	class UAnimMontage* DaggerStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Dagger")
	class UAnimMontage* DaggerExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Dagger")
	TArray <class UAnimMontage*> DaggerBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Dagger")
	class UAnimMontage* DaggerAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Dagger")
	class UAnimMontage* DaggerAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Dagger")
	class UAnimMontage* DaggerAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Dagger")
	class UAnimMontage* DaggerAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Club")
	class UAnimMontage* ClubStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Club")
	class UAnimMontage* ClubExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Club")
	TArray <class UAnimMontage*> ClubBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Club")
	class UAnimMontage* ClubAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Club")
	class UAnimMontage* ClubAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Club")
	class UAnimMontage* ClubAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Club")
	class UAnimMontage* ClubAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Katana")
	class UAnimMontage* KatanaStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Katana")
	class UAnimMontage* KatanaExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Katana")
	TArray <class UAnimMontage*> KatanaBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Katana")
	class UAnimMontage* KatanaAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Katana")
	class UAnimMontage* KatanaAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Katana")
	class UAnimMontage* KatanaAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|Katana")
	class UAnimMontage* KatanaAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|H2H")
	class UAnimMontage* H2HStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|H2H")
	class UAnimMontage* H2HExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|H2H")
	TArray <class UAnimMontage*> H2HBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|H2H")
	class UAnimMontage* H2HAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|H2H")
	class UAnimMontage* H2HAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|H2H")
	class UAnimMontage* H2HAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|H2H")
	class UAnimMontage* H2HAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatSword")
	class UAnimMontage* GreatSwordStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatSword")
	class UAnimMontage* GreatSwordExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatSword")
	TArray <class UAnimMontage*> GreatSwordBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatSword")
	class UAnimMontage* GreatSwordAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatSword")
	class UAnimMontage* GreatSwordAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatSword")
	class UAnimMontage* GreatSwordAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatSword")
	class UAnimMontage* GreatSwordAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatKatana")
	class UAnimMontage* GreatKatanaStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatKatana")
	class UAnimMontage* GreatKatanaExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatKatana")
	TArray <class UAnimMontage*> GreatKatanaBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatKatana")
	class UAnimMontage* GreatKatanaAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatKatana")
	class UAnimMontage* GreatKatanaAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatKatana")
	class UAnimMontage* GreatKatanaAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|GreatKatana")
	class UAnimMontage* GreatKatanaAtkRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|TwoHanded")
	class UAnimMontage* TwoHandedStartCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|TwoHanded")
	class UAnimMontage* TwoHandedExitCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|TwoHanded")
	TArray <class UAnimMontage*> TwoHandedBasicAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|TwoHanded")
	class UAnimMontage* TwoHandedAtkFw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|TwoHanded")
	class UAnimMontage* TwoHandedAtkNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|TwoHanded")
	class UAnimMontage* TwoHandedAtkLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XICharacter|Combat|TwoHanded")
	class UAnimMontage* TwoHandedAtkRight;

#pragma endregion CombatMontages

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "XICharacter|Combat")
	ECombatStyle CombatStyle;
};
