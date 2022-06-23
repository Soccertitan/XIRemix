// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/XIGameplayFunctionLibrary.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Interfaces/XICharacterInterface.h"
#include "Interfaces/XIAggroInterface.h"
#include "Interfaces/XIThreatTableInterface.h"
#include "Interfaces/XITargetSystemInterface.h"
#include "Interfaces/XIEquipmentManagerInterface.h"

bool UXIGameplayFunctionLibrary::CheckTargetWithinRange(AActor* OwnerActor, AActor* TargetActor, float AngleInDegrees, float Range)
{
    if ((!OwnerActor) | (!TargetActor))
    {
        return false;
    }

    // Is Target Actor infront of SourceActor?
    float DotProduct = FVector::DotProduct((TargetActor->GetActorLocation() - OwnerActor->GetActorLocation()).GetSafeNormal(), OwnerActor->GetActorForwardVector());
    if (!(DotProduct >= UKismetMathLibrary::DegCos(AngleInDegrees)))
    {
        return false;
    }

    // Line Trace to Actor, Checking if any static objects are between the player. Saves having to add in an ignore actors array.

    FHitResult HitResult;
    TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
    TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
    TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));

    bool bHitActor = OwnerActor->GetWorld()->LineTraceSingleByObjectType(
        HitResult,
        OwnerActor->GetActorLocation(),
        TargetActor->GetActorLocation(),
        TraceObjectTypes
    );

    if (bHitActor)
    {
        return false;
    }
    
    float Distance = FVector::Dist(OwnerActor->GetActorLocation(), TargetActor->GetActorLocation());
    if (Distance <= Range)
    {
        return true;
    }

    return false;
}

AActor* UXIGameplayFunctionLibrary::GetMainTarget(AActor* OwnerActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        return XICharacterInt->GetMainTarget();
    }
    return nullptr;
}

void UXIGameplayFunctionLibrary::SetMainTarget(AActor* OwnerActor, AActor* TargetActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        XICharacterInt->SetMainTarget(TargetActor);
    }
}

AActor* UXIGameplayFunctionLibrary::GetSubTarget(AActor* OwnerActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        return XICharacterInt->GetSubTarget();
    }
    return nullptr;
}

FText UXIGameplayFunctionLibrary::GetCharacterName(AActor* OwnerActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        return XICharacterInt->GetCharacterName();
    }
    return FText();
}

EXITeam UXIGameplayFunctionLibrary::GetXITeam(AActor* OwnerActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        return XICharacterInt->GetXITeam();
    }
    return EXITeam::Neutral;
}

EXITeamAttitude UXIGameplayFunctionLibrary::GetAttitudeTowardsActor(AActor* OwnerActor, AActor* TargetActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        return XICharacterInt->GetAttitudeTowardsActor(TargetActor);
    }
    return EXITeamAttitude::Neutral;
}

float UXIGameplayFunctionLibrary::GetCapsuleRadius(AActor* OwnerActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        return XICharacterInt->GetCapsuleRadius();
    }
    return 0.0f;
}

float UXIGameplayFunctionLibrary::GetCharacterLevel(AActor* OwnerActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        return XICharacterInt->GetCharacterLevel();
    }
    return 0.0f;
}

bool UXIGameplayFunctionLibrary::IsAlive(AActor* OwnerActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        return XICharacterInt->IsAlive();
    }
    return false;
}

#pragma region AnimMontages

UAnimMontage* UXIGameplayFunctionLibrary::GetAutoAttackMontage(AActor* OwnerActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        return XICharacterInt->GetAutoAttackMontage();
    }
    return nullptr;
}

UXICharacterAnimMontages* UXIGameplayFunctionLibrary::GetXICharacterAnimMontages(AActor* OwnerActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        return XICharacterInt->GetXICharacterAnimMontages();
    }
    return nullptr;
}

#pragma endregion AnimMontages

UXIThreatTableComponent* UXIGameplayFunctionLibrary::GetXIThreatTableComponent(AController* AIController)
{
    IXIThreatTableInterface* XIThreatInt = Cast<IXIThreatTableInterface>(AIController);
    if(XIThreatInt)
    {
        return XIThreatInt->GetXIThreatTableComponent();
    }
    return nullptr;
}

UXIAggroComponent* UXIGameplayFunctionLibrary::GetXIAggroComponent(AActor* OwnerActor)
{
    IXIAggroInterface* XIEnemyInt = Cast<IXIAggroInterface>(OwnerActor);
    if(XIEnemyInt)
    {
        return XIEnemyInt->GetXIAggroComponent();
    }
    return nullptr;
}

UXITargetSystemComponent* UXIGameplayFunctionLibrary::GetXITargetSystemComponent(AActor* OwnerActor)
{
    IXITargetSystemInterface* XITargetInt = Cast<IXITargetSystemInterface>(OwnerActor);
    if(XITargetInt)
    {
        return XITargetInt->GetXITargetSystemComponent();
    }
    return nullptr;
}

UXIEquipmentManagerComponent* UXIGameplayFunctionLibrary::GetXIEquipmentManagerComponent(AActor* OwnerActor)
{
    IXIEquipmentManagerInterface* XIEquipInt = Cast<IXIEquipmentManagerInterface>(OwnerActor);
    if(XIEquipInt)
    {
        return XIEquipInt->GetXIEquipmentManagerComponent();
    }
    return nullptr;
}
