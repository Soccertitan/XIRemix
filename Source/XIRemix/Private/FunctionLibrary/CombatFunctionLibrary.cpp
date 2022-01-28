// Fill out your copyright notice in the Description page of Project Settings.

#include "FunctionLibrary/CombatFunctionLibrary.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Interfaces/XICharacterInterface.h"

bool UCombatFunctionLibrary::CheckTargetWithinRange(AActor* OwnerActor, AActor* TargetActor, float AngleInDegrees, float Range)
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

AActor* UCombatFunctionLibrary::GetMainTarget(AActor* OwnerActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        return XICharacterInt->GetMainTarget();
    }
    return nullptr;
}

AActor* UCombatFunctionLibrary::GetSubTarget(AActor* OwnerActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        return XICharacterInt->GetSubTarget();
    }
    return nullptr;
}

UAnimMontage* UCombatFunctionLibrary::GetAutoAttackMontage(AActor* OwnerActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        return XICharacterInt->GetAutoAttackMontage();
    }
    return nullptr;
}

FText UCombatFunctionLibrary::GetCharacterName(AActor* OwnerActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        return XICharacterInt->GetCharacterName();
    }
    return FText();
}

EXITeam UCombatFunctionLibrary::GetXITeam(AActor* OwnerActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        return XICharacterInt->GetXITeam();
    }
    return EXITeam::Neutral;
}

EXITeamAttitude UCombatFunctionLibrary::GetAttitudeTowardsActor(AActor* OwnerActor, AActor* TargetActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        return XICharacterInt->GetAttitudeTowardsActor(TargetActor);
    }
    return EXITeamAttitude::Neutral;
}