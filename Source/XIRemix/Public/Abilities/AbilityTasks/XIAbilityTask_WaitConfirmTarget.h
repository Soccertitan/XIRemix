// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "XIAbilityTask_WaitConfirmTarget.generated.h"

class UUserWidget;
class UWidgetComponent;
class APlayerController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FXIWaitConfirmCancelTargetDelegate, AActor*, TargetActor);

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIAbilityTask_WaitConfirmTarget : public UAbilityTask
{
	GENERATED_BODY()

public:

	UXIAbilityTask_WaitConfirmTarget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintAssignable)
	FXIWaitConfirmCancelTargetDelegate OnConfirm;

	UPROPERTY(BlueprintAssignable)
	FXIWaitConfirmCancelTargetDelegate OnCancel;
	
	UFUNCTION()
	void OnConfirmCallback();

	UFUNCTION()
	void OnCancelCallback();

	UFUNCTION()
	void OnLocalConfirmCallback();

	UFUNCTION()
	void OnLocalCancelCallback();
	/**
	 * Starts targeting for a local player. TODO More Info
	 * @param TargetingRange The max range to target an actor.
	 * @param TargetWidgetClass The widget class to visualy represent the currently targeted actor.
	 * @param TargetWidgetRelativeLocation The relative location of the widget from the parent socket.
	 * @param TargetWidgetParentSocket The socket for attaching the widget too.
	 * @param InitialTarget The default actor to visually represent the target.
	 * @param XITeamAttitude The filter to detmine which actors to target.
	*/
	UFUNCTION(BlueprintCallable, meta=(HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true", DisplayName="Wait for Confirm Target Input"), Category="Ability|Tasks")
	static UXIAbilityTask_WaitConfirmTarget* WaitConfirmCancel(
		UGameplayAbility* OwningAbility,
		AActor* InitialTarget,
		EXITeamAttitude XITeamAttitude,
		TSubclassOf<UUserWidget> TargetWidgetClass,
		FVector TargetWidgetRelativeLocation,
		float TargetWidgetDrawSize = 32.f,
		FName TargetWidgetParentSocket = FName("target"),
		float TargetingRange = 1500.0f);

	virtual void Activate() override;

protected:

	virtual void OnDestroy(bool AbilityEnding) override;

	bool RegisteredCallbacks;

	UPROPERTY()
	float TargetingRange;

	UPROPERTY()
	TSubclassOf<UUserWidget> TargetWidgetClass;
	UPROPERTY()
	UWidgetComponent* TargetWidgetComponent;
	UPROPERTY()
	FVector TargetWidgetRelativeLocation;
	UPROPERTY()
	float TargetWidgetDrawSize;
	UPROPERTY()
	FName TargetWidgetParentSocket;

	UPROPERTY()
	APlayerController* OwnerPlayerController;
	UPROPERTY()
	UCameraComponent* CameraComponent;

	UPROPERTY()
	AActor* TargetedActor;
	UPROPERTY()
	APawn* OwnerPawn;

	UPROPERTY()
	EXITeamAttitude XITeamAttitude;

	UPROPERTY()
	class UXIAbilitySystemComponent* XIASC;

	void SetupLocalPlayerController();

	TArray<AActor *> GetTargetableActorsFromTrace() const;
	AActor* FindNearestTarget(TArray<AActor*> Actors) const;
	bool LineTraceForActor(AActor* OtherActor, TArray<AActor*> ActorsToIgnore = TArray<AActor*>()) const;
	bool LineTrace(FHitResult& HitResult, const AActor* OtherActor, const TArray<AActor*> ActorsToIgnore) const;
	bool IsInViewport(const AActor* TargetActor) const;

	UFUNCTION()
	void TargetActor(float Direction);
	void SwitchTargetActor(TArray<AActor*> PerceivedActors, float Direction);

	void TargetSelected(AActor* TargetActor);
	void CreateAndAttachTargetSelectedWidgetComponent(AActor* TargetActor);

};
