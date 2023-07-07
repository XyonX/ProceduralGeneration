// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreSpawner.h"



bool UCoreSpawner::ImportSpawnable(UTopDownGameInstance*InGameInstance , TMap<int32,USpawnable*>* OutSpawnable)
{
	if(InGameInstance)
	{
		OutSpawnables = InGameInstance->GetAllSpawnables();
		return true;
	}
	return false;
}
