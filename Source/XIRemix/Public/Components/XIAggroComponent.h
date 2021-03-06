// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "XIEnums.h"
#include "XIAggroComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActorDetected, AActor*, DetectedActor);

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

	UFUNCTION(BlueprintCallable, Category = "XIRemix|AggroComponent")
	void SetAggroMode(bool bEnableAggro);

	UPROPERTY(BlueprintAssignable)
	FActorDetected OnActorDetected;

	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Detection|Sphere")
	USphereComponent* SphereComponent;

private:
	bool bAggroEnabled = true;

	// Detection Range
	UPROPERTY(EditAnywhere, Category = "Detection")
	float Range = 1000;

	// Detection Angle. 180 is equivalent to 360 degrees.
	UPROPERTY(EditAnywhere, Category = "Detection")
	float Angle = 30;

	// Aggro Type
	UPROPERTY(EditAnywhere, Category = "Detection")
	EXIAggroType XIAggroType;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	AActor* OwnerActor;
	TArray<AActor *> HostileActors;
	
	class UAbilitySystemComponent* HostileASC;
	class UAbilitySystemComponent* OwnerASC;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
