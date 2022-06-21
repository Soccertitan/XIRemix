// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "XIThreatTableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHighestThreat, AActor*, TargetActor);

USTRUCT(BlueprintType)
struct XIREMIX_API FThreatTableStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	AActor* Actor;

	UPROPERTY(BlueprintReadOnly)
	float VolatileEnmity;

	UPROPERTY(BlueprintReadOnly)
	float CumulativeEnmity;

	FThreatTableStruct()
	{
		Actor = nullptr;
		VolatileEnmity = 0;
		CumulativeEnmity = 0;
	}

	bool operator==(const FThreatTableStruct& V) const
	{
		return Actor == V.Actor;
	}
	bool operator!=(const FThreatTableStruct& V) const
	{
		return Actor != V.Actor;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class XIREMIX_API UXIThreatTableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UXIThreatTableComponent();

	UPROPERTY(BlueprintAssignable, Category = "XIRemix|XIThreatTable")
	FHighestThreat OnHighestThreat;

	UFUNCTION(BlueprintCallable, Category = "XIRemix|XIThreatTable")
	void AddEnmity(AActor* TargetActor, float InVolatileEnmity, float InCumulativeEnmity, bool bOverrideEnmity);

	UFUNCTION(BlueprintCallable, Category = "XIRemix|XIThreatTable")
	void RemoveTargetActor(AActor* TargetActor);

	UFUNCTION(BlueprintCallable, Category = "XIRemix|XIThreatTable")
	void ApplyDamageEnmity(AActor* TargetActor, float Damage, float EnmityRate);

	UFUNCTION(BlueprintCallable, Category = "XIRemix|XIThreatTable")
	void ApplyHealEnmity(AActor* TargetActor, float HealedTargetLevel, float Heal, float EnmityRate);

	UFUNCTION(BlueprintCallable, Category = "XIRemix|XIThreatTable")
	void ApplyDamageTakenEnmity(AActor* TargetActor, float Damage, float TargetMaxHP);

	// Returns true if actor is found and has enmity.
	UFUNCTION(BlueprintCallable, Category = "XIRemix|XIThreatTable")
	bool GetTargetActorEnmity(AActor* TargetActor, float& OutVolatileEnmity, float& OutCumulativeEnmity) const;

	UFUNCTION(BlueprintCallable, Category = "XIRemix|XIThreatTable")
	void SetCharacterLevel(float Level);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;	

	UFUNCTION()
	void CheckHighestEnmity();

	UPROPERTY(BlueprintReadWrite, Category = "XIRemix|XIThreatTable")
	TArray <FThreatTableStruct> ThreatTable;

	UPROPERTY()
	AActor* HighestThreatActor;

	UPROPERTY()
	float ClampMin = 0;

	UPROPERTY(EditAnywhere)
	float ClampMax = 30000;

	UPROPERTY(EditAnywhere)
	float VolatileEnimtyDecayRate = 60;

	// Level of the character that owns this component.
	UPROPERTY()
	float CharacterLevel;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
