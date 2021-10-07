// Fill out your copyright notice in the Description page of Project Settings.


#include "XIAssetManager.h"
#include "AbilitySystemGlobals.h"

UXIAssetManager& UXIAssetManager::Get() 
{
	UXIAssetManager* Singleton = Cast<UXIAssetManager>(GEngine->AssetManager);

	if (Singleton)
	{
		return *Singleton;
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("Invalid AssetManager in DefaultEngine.ini, must be XIAssetManager!"));
		return *NewObject<UXIAssetManager>();	 // never calls this
	}
}


void UXIAssetManager::StartInitialLoading() 
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
}