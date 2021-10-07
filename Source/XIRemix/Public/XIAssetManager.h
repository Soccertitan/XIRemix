// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "XIAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class XIREMIX_API UXIAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	static UXIAssetManager& Get();

	/** Starts initial load, gets called from InitializeObjectReferences */
	virtual void StartInitialLoading() override;
};
