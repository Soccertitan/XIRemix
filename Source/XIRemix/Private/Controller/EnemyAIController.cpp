// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/EnemyAIController.h"

AEnemyAIController::AEnemyAIController()
{
    SetGenericTeamId(FGenericTeamId(3));
}

ETeamAttitude::Type AEnemyAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
    if (const APawn* OtherPawn = Cast<APawn>(&Other)) 
    {
     
        // DEFAULT BEHAVIOR---------------------------------------------------
        if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
        {
            return Super::GetTeamAttitudeTowards(*OtherPawn->GetController());
        }
    }
    return ETeamAttitude::Neutral;
}