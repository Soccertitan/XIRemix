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

	FORCEINLINE FThreatTableStruct();

	UPROPERTY(BlueprintReadWrite)
	AActor* Actor = nullptr;

	UPROPERTY(BlueprintReadWrite)
	float ThreatLevel = 0;

	bool operator==(const FThreatTableStruct& V) const;
	bool operator!=(const FThreatTableStruct& V) const;
};

FORCEINLINE FThreatTableStruct::FThreatTableStruct()
{
}

FORCEINLINE bool FThreatTableStruct::operator==(const FThreatTableStruct& V) const
{
	return Actor == V.Actor;
}

FORCEINLINE bool FThreatTableStruct::operator!=(const FThreatTableStruct& V) const
{
	return Actor != V.Actor;
}


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class XIREMIX_API UXIThreatTableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UXIThreatTableComponent();

	UPROPERTY(BlueprintAssignable)
	FHighestThreat OnHighestThreat;

	UFUNCTION(BlueprintCallable)
	void AddThreat(AActor* TargetActor, float ThreatAmount);

	UFUNCTION(BlueprintCallable)
	void RemoveThreatActor(AActor* TargetActor);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;	

	UFUNCTION()
	void CheckHighestThreat();

	UPROPERTY(BlueprintReadWrite)
	TArray <FThreatTableStruct> ThreatTable;

	UPROPERTY()
	AActor* HighestThreatActor;

};
