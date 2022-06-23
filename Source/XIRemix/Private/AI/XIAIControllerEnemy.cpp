// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/XIAIControllerEnemy.h"
#include "Characters/XICharacterBaseEnemy.h"
#include "Components/XIAggroComponent.h"
#include "AbilitySystemComponent.h"
#include "FunctionLibrary/XIGameplayFunctionLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

AXIAIControllerEnemy::AXIAIControllerEnemy()
{
    XIThreatTableComponent = CreateDefaultSubobject<UXIThreatTableComponent>(TEXT("XIThreatTableComponent"));
    XIThreatTableComponent->OnHighestThreat.AddUniqueDynamic(this, &AXIAIControllerEnemy::OnHighestThreat);
    bIsAlive = true;
}

UXIThreatTableComponent* AXIAIControllerEnemy::GetXIThreatTableComponent() const
{
    return XIThreatTableComponent;
}

void AXIAIControllerEnemy::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    ControlledPawn = Cast<AXICharacterBaseEnemy>(InPawn);

    if(!ControlledPawn)
    {
        UE_LOG(LogTemp, Error, TEXT("The AI controlled pawn is not a XICharacterBaseEnemy! %s"), *InPawn->GetName());
        return;
    }

    ControlledPawn->OnCharacterDied.AddUniqueDynamic(this, &AXIAIControllerEnemy::OnControlledActorDied);
    ASC = ControlledPawn->GetAbilitySystemComponent();
    XIThreatTableComponent->SetCharacterLevel(ControlledPawn->GetCharacterLevel());
    
    XIAggroComponentRef = ControlledPawn->GetXIAggroComponent();
    if(XIAggroComponentRef)
    {
        XIAggroComponentRef->OnActorDetected.AddUniqueDynamic(this, &AXIAIControllerEnemy::OnActorDetected);
    }

    RunBehaviorTree(BTAsset);
}

void AXIAIControllerEnemy::OnControlledActorDied(AActor* Actor)
{
    bIsAlive = false;
    SetActorTickEnabled(false);
    if(XIAggroComponentRef) XIAggroComponentRef->SetAggroMode(false);
}

void AXIAIControllerEnemy::OnActorDetected(AActor* Actor)
{
    if (bIsAlive)
    {
        SetMainTarget(Actor);
    }
}

void AXIAIControllerEnemy::OnHighestThreat(AActor* Actor)
{
    if(Actor)
    {
        if(UXIGameplayFunctionLibrary::IsAlive(Actor))
        {
            SetMainTarget(Actor);
            if(XIAggroComponentRef)
            {
                XIAggroComponentRef->SetAggroMode(false);
            }
        }
        else
        {
            XIThreatTableComponent->RemoveTargetActor(Actor);
        }
    }
    else
    {
        if(ASC)
        {
            ASC->RemoveActiveGameplayEffectBySourceEffect(WeaponsOutGE, nullptr, -1);
        }
        if(XIAggroComponentRef) XIAggroComponentRef->SetAggroMode(true);
        Blackboard->SetValueAsObject(FName::FName("MainTarget"), nullptr);
    }
}

void AXIAIControllerEnemy::SetMainTarget(AActor* Actor)
{
    if(!bIsAlive)
    {
        return;
    }
    
    if(TargetedActor)
    {
        TargetedActor->OnCharacterDied.RemoveAll(this);
    }
    
    TargetedActor = Cast<AXICharacterBase>(Actor);
    if(!TargetedActor)
    {
        UE_LOG(LogTemp, Error, TEXT("XIAIControllerEnemy: Unable to cast the Targeted Actor into a AXICharacterBase"));
        return;
    }

    TargetedActor->OnCharacterDied.AddUniqueDynamic(this, &AXIAIControllerEnemy::OnTargetDied);
    Blackboard->SetValueAsObject(FName::FName("MainTarget"), TargetedActor);
    SetActorTickEnabled(true);
    ControlledPawn->SetMainTarget(TargetedActor);
    if(XIAggroComponentRef) XIAggroComponentRef->SetAggroMode(false);
    
    FGameplayEffectContextHandle Handle;
    if(ASC) ASC->BP_ApplyGameplayEffectToSelf(WeaponsOutGE, 1.f, Handle);
}

void AXIAIControllerEnemy::OnTargetDied(AActor* Actor)
{
    Blackboard->SetValueAsObject(FName::FName("MainTarget"), nullptr);
    XIThreatTableComponent->RemoveTargetActor(Actor);
}