// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/XIAIControllerEnemy.h"

AXIAIControllerEnemy::AXIAIControllerEnemy()
{
    XIThreatTableComponent = CreateDefaultSubobject<UXIThreatTableComponent>(TEXT("XIThreatTableComponent"));
}

UXIThreatTableComponent* AXIAIControllerEnemy::GetXIThreatTableComponent() const
{
    return XIThreatTableComponent;
}