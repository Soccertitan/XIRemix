// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TargetPlateWidget.h"

float UTargetPlateWidget::GetHitPointsPercent()
{
    return HitPoints / FMath::Max(HitPointsMax, 1.f);
}