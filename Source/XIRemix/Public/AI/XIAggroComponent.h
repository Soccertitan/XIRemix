// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "XIEnums.h"
#include "XIAggroComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class XIREMIX_API UXIAggroComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UXIAggroComponent();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	AActor* OwnerActor;
	TArray<AActor *> HostileActors;

	class UAbilitySystemComponent* HostileASC;
	class UAbilitySystemComponent* OwnerASC;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Detection|Sphere")
	USphereComponent* SphereComponent;

	// Detection Range
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Detection")
	float Range = 1000;

	// Detection Angle. 180 is equivalent to 360 degrees.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Detection")
	float Angle = 30;

	// Aggro Type
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Detection")
	EXIAggroType XIAggroType;

	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
