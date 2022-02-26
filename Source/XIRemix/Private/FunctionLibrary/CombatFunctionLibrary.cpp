// Fill out your copyright notice in the Description page of Project Settings.

#include "FunctionLibrary/CombatFunctionLibrary.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Interfaces/XICharacterInterface.h"
#include "Interfaces/XIEnemyCharacterInterface.h"
#include "Interfaces/XIThreatTableInterface.h"
#include "Interfaces/XITargetSystemInterface.h"

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

void UCombatFunctionLibrary::SetMainTarget(AActor* OwnerActor, AActor* TargetActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        XICharacterInt->SetMainTarget(TargetActor);
    }
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

float UCombatFunctionLibrary::GetCapsuleRadius(AActor* OwnerActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        return XICharacterInt->GetCapsuleRadius();
    }
    return 0.0f;
}

#pragma region AnimMontages

UAnimMontage* UCombatFunctionLibrary::GetAutoAttackMontage(AActor* OwnerActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        return XICharacterInt->GetAutoAttackMontage();
    }
    return nullptr;
}

UAnimMontage* UCombatFunctionLibrary::GetBlackMagicMontage(AActor* OwnerActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        return XICharacterInt->GetBlackMagicMontage();
    }
    return nullptr;
}

UAnimMontage* UCombatFunctionLibrary::GetWhiteMagicMontage(AActor* OwnerActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        return XICharacterInt->GetWhiteMagicMontage();
    }
    return nullptr;
}

UAnimMontage* UCombatFunctionLibrary::GetSummonerMagicMontage(AActor* OwnerActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        return XICharacterInt->GetSummonerMagicMontage();
    }
    return nullptr;
}

UAnimMontage* UCombatFunctionLibrary::GetNinjitsuMagicMontage(AActor* OwnerActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        return XICharacterInt->GetNinjitsuMagicMontage();
    }
    return nullptr;
}

UAnimMontage* UCombatFunctionLibrary::GetBlueMagicMontage(AActor* OwnerActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        return XICharacterInt->GetBlueMagicMontage();
    }
    return nullptr;
}

UAnimMontage* UCombatFunctionLibrary::GetGeoMagicMontage(AActor* OwnerActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        return XICharacterInt->GetGeoMagicMontage();
    }
    return nullptr;
}

UAnimMontage* UCombatFunctionLibrary::GetJobAbilityMontage(AActor* OwnerActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        return XICharacterInt->GetJobAbilityMontage();
    }
    return nullptr;
}

UAnimMontage* UCombatFunctionLibrary::GetJobAbilityCombatMontage(AActor* OwnerActor)
{
    IXICharacterInterface* XICharacterInt = Cast<IXICharacterInterface>(OwnerActor);
    if(XICharacterInt)
    {
        return XICharacterInt->GetJobAbilityCombatMontage();
    }
    return nullptr;
}

#pragma endregion AnimMontages

UXIThreatTableComponent* UCombatFunctionLibrary::GetXIThreatTableComponent(AController* AIController)
{
    IXIThreatTableInterface* XIThreatInt = Cast<IXIThreatTableInterface>(AIController);
    if(XIThreatInt)
    {
        return XIThreatInt->GetXIThreatTableComponent();
    }
    return nullptr;
}

UXIAggroComponent* UCombatFunctionLibrary::GetXIAggroComponent(AActor* OwnerActor)
{
    IXIEnemyCharacterInterface* XIEnemyInt = Cast<IXIEnemyCharacterInterface>(OwnerActor);
    if(XIEnemyInt)
    {
        return XIEnemyInt->GetXIAggroComponent();
    }
    return nullptr;
}

UXITargetSystemComponent* UCombatFunctionLibrary::GetXITargetSystemComponent(AActor* OwnerActor)
{
    IXITargetSystemInterface* XITargetInt = Cast<IXITargetSystemInterface>(OwnerActor);
    if(XITargetInt)
    {
        return XITargetInt->GetXITargetSystemComponent();
    }
    return nullptr;
}