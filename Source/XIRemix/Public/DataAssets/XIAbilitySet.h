// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Abilities/XIGameplayAbility.h"
#include "Engine/DataAsset.h"
#include "XIAbilitySet.generated.h"

class UXIAbilitySystemComponent;
 
/**
 * FXIAbilitySet_GameplayAbility
 *
 *  Data used by the ability set to grant gameplay abilities.
 */
USTRUCT(BlueprintType)
struct FXIAbilitySet_GameplayAbility
{
    GENERATED_BODY()
 
public:
 
    // Gameplay ability to grant.
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UXIGameplayAbility> Ability = nullptr;
 
    // Level of ability to grant.
    UPROPERTY(EditDefaultsOnly)
    int32 AbilityLevel = 1;
};
 
 
/**
 * FXIAbilitySet_GameplayEffect
 *
 *  Data used by the ability set to grant gameplay effects.
 */
USTRUCT(BlueprintType)
struct FXIAbilitySet_GameplayEffect
{
    GENERATED_BODY()
 
public:
 
    // Gameplay effect to grant.
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UGameplayEffect> GameplayEffect = nullptr;
 
    // Level of gameplay effect to grant.
    UPROPERTY(EditDefaultsOnly)
    float EffectLevel = 1.0f;
};
 
 
 
/**
 * FXIAbilitySet_GrantedHandles
 *
 *  Data used to store handles to what has been granted by the ability set.
 */
USTRUCT(BlueprintType)
struct FXIAbilitySetHandle
{
    GENERATED_BODY()
     
    bool IsValid() const
    {
        return AbilitySystemComponent.IsValid() && HandleId != 0;
    }
 
private:
    friend class UXIAbilitySet;
 
    void AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle);
    void AddGameplayEffectHandle(const FActiveGameplayEffectHandle& Handle);
 
     
    // Handles to the granted abilities.
    UPROPERTY()
    TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;
 
    // Handles to the granted gameplay effects.
    UPROPERTY()
    TArray<FActiveGameplayEffectHandle> GameplayEffectHandles;
     
    int32 HandleId = 0;
     
    TWeakObjectPtr<UXIAbilitySystemComponent> AbilitySystemComponent = nullptr;
     
    void Reset()
    {
        AbilitySpecHandles.Reset();
        GameplayEffectHandles.Reset();
        AbilitySystemComponent.Reset();
        HandleId = 0;
    }
     
};
 
/**
 * 
 */
UCLASS(BlueprintType, Const)
class XIREMIX_API UXIAbilitySet : public UPrimaryDataAsset
{
    GENERATED_BODY()
public:
 
    UXIAbilitySet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
 
    const TArray<FXIAbilitySet_GameplayAbility>& GetGrantedGameplayAbilities() const { return GrantedGameplayAbilities; }
    const TArray<FXIAbilitySet_GameplayEffect>& GetGrantedGameplayEffects() const { return GrantedGameplayEffects; }
 
    FXIAbilitySetHandle GiveAbilitySetTo(UXIAbilitySystemComponent* ASC, UObject* OverrideSourceObject = nullptr) const;
    FXIAbilitySetHandle GiveAbilitySetToInterface(TScriptInterface<IAbilitySystemInterface> AbilitySystemInterface, UObject* OverrideSourceObject = nullptr) const;
    static void TakeAbilitySet(FXIAbilitySetHandle& AbilitySetHandle);
 
protected:
    // Gameplay abilities to grant when this ability set is granted.
    UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities", meta=(TitleProperty=Ability))
    TArray<FXIAbilitySet_GameplayAbility> GrantedGameplayAbilities;
 
    // Gameplay effects to grant when this ability set is granted.
    UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects", meta=(TitleProperty=GameplayEffect))
    TArray<FXIAbilitySet_GameplayEffect> GrantedGameplayEffects;

};