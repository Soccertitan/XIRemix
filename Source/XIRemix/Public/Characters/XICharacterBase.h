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
#include "DataAssets/XICharacterAnimMontages.h"
#include "DataAssets/XIAbilitySet.h"
#include "DataAssets/XIStatsGrowthRank.h"
#include "DataAssets/XIStatsGrowthData.h"
#include "XICharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate, AActor*, DeadActor);

UCLASS()
class XIREMIX_API AXICharacterBase : public ACharacter, public IAbilitySystemInterface, public IXICharacterInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AXICharacterBase(const class FObjectInitializer& ObjectInitializer);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintAssignable, Category = "XICharacter")
	FCharacterDiedDelegate OnCharacterDied;

	// Implement IAbilitySystemInterface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// Switch on AbilityID to return individual ability levels. Hardcoded to 1 for every ability in this project.
	UFUNCTION(BlueprintCallable, Category = "XICharacter|Abilities")
	virtual int32 GetAbilityLevel(EXIAbilityInputID AbilityID) const;

	// // Removes all CharacterAbilities. Can only be called by the Server. Removing on the Server will remove from Client too.
	// virtual void RemoveCharacterAbilities();

	// IXICharacter Interface Implementations
	virtual class AXICharacterBase* GetXICharacterBase() override;
	virtual FText GetCharacterName() const override;
	virtual AActor* GetMainTarget() const override;
	virtual void SetMainTarget(AActor* TargetActor) override;
	virtual AActor* GetSubTarget() const override;
	virtual EXITeamAttitude GetAttitudeTowardsActor(AActor* OtherActor) const override;
	virtual EXITeam GetXITeam() const override;
	virtual float GetCapsuleRadius() const override;
	virtual bool IsAlive() const override;
	virtual UXICharacterAnimMontages* GetXICharacterAnimMontages() const override;
	virtual UAnimMontage* GetAutoAttackMontage() const override;
	virtual UXIStatsGrowthRank* GetXIStatsGrowthRank() const override;
	virtual UXIStatsGrowthData* GetXIStatsGrowthData() const override;

	FORCEINLINE UCurveTable* GetSkillRankCurveTable() const {return SkillRankCurveTable;}

	// /**
	// * Getters for attributes from GlobalAttributeSet
	// **/
	virtual float GetHitPoints() const override;
	virtual float GetHitPointsMax() const override;
	virtual float GetManaPoints() const override;
	virtual float GetManaPointsMax() const override;
	virtual float GetTacticalPoints() const override;
	virtual float GetTacticalPointsMax() const override;
	virtual float GetMoveSpeed() const override;
	virtual float GetCharacterLevel() const override;

	UFUNCTION(BlueprintPure, Category = "XICharacter|AnimMontages")
	UAnimMontage* GetCombatStartMontage();

	UFUNCTION(BlueprintPure, Category = "XICharacter|AnimMontages")
	UAnimMontage* GetCombatExitMontage();

	// Server sets the character name.
	UFUNCTION(BlueprintCallable, Category = "XICharacter|Name")
	void SetCharacterName(FText Name);

	UFUNCTION(Server, WithValidation, Reliable)
	void Server_SetCharacterName(const FText& Name);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XICharacter|Combat")
	class UXICharacterAnimMontages* AnimMontages;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Replicated, Category = "XICharacter")
	FText CharacterName;

	UPROPERTY(BlueprintReadWrite, Category = "XICharacter|Combat")
	AActor* MainTarget;
	UPROPERTY(BlueprintReadWrite, Category = "XICharacter|Combat")
	AActor* SubTarget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, ReplicatedUsing = OnRep_CombatStyle, Category = "XICharacter|Combat")
	ECombatStyle CombatStyle;
	UFUNCTION()
	void OnRep_CombatStyle();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "XICharacter")
	EXITeam XITeam;

	// UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XICharacter")
	// Widget TargetUI; // Future Implementation

	UPROPERTY(EditAnywhere)
	class UXIAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY()
	class UAttributeSetGlobal* AttributeSet;

	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;


	// Attribute Change Callbacks
	FDelegateHandle HitPointsChangedDelegateHandle;
	FDelegateHandle HitPointsMaxChangedDelegateHandle;
	FDelegateHandle ManaPointsChangedDelegateHandle;
	FDelegateHandle TacticalPointsChangedDelegateHandle;
	virtual void HitPointsChanged(const FOnAttributeChangeData& Data);
	virtual void HitPointsMaxChanged(const FOnAttributeChangeData& Data);
	virtual void ManaPointsChanged(const FOnAttributeChangeData& Data);
	virtual void TacticalPointsChanged(const FOnAttributeChangeData& Data);

	//Default Abilities and Effects for this character.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XICharacter|Abilities")
	TArray<UXIAbilitySet*> AbilitySets;

	// Default attributes for a character for initializing on spawn/respawn.
	// This is an instant GE that overrides the values for attributes that get reset on spawn/respawn.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XICharacter|Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	//Stats Growth Ranking data to determine stats.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XICharacter|Abilities")
	UXIStatsGrowthRank* StatsGrowthRank;

	//Referenced by StatsGrowthRank to get the value for calculating Stat Growth
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XICharacter|Abilities")
	UXIStatsGrowthData* StatsGrowthData;

	//For Heros; a curve table that maps a Skill Rank to max combat skill. For Enemies, maps the combat skills to level.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XICharacter|Abilities")
	UCurveTable* SkillRankCurveTable;

	// Grant abilities on the Server. The Ability Specs will be replicated to the owning client.
	virtual void AddCharacterAbilities();

	// Initialize the Character's attributes. Must run on Server but we run it on Client too
	// so that we don't have to wait. The Server's replication to the Client won't matter since
	// the values should be the same.
	virtual void InitializeAttributes();

	//Default Death Event. Should be overridden by child classes.
	void Die();
};
