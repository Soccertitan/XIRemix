// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XITargetPlateWidget.h"

float UXITargetPlateWidget::GetHitPointsPercent()
{
    return HitPoints / FMath::Max(HitPointsMax, 1.f);
}