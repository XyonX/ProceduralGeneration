// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "CorePlugin/Spawnables/Spawnable.h"
#include "ProceduralGeneration/Game/TopDownGameInstance.h"
#include "UObject/Object.h"
#include "CoreSpawner.generated.h"

/**
 This class  Handel Mesh Spawning Related Logics
 -TileMesh Replaced With Spawner
 */
UCLASS()
class PROCEDURALGENERATION_API UCoreSpawner : public UObject
{
	GENERATED_BODY()

public:

	bool ImportSpawnable (UTopDownGameInstance*InGameInstance , TMap<int32,USpawnable*>* OutSpawnable );

protected:

	
	

private:

	UPROPERTY()
	UDataTable*MeshPropertyDataTable;
	UPROPERTY()
	TMap<int32,USpawnable*>* TotalSpawnable;

	UPROPERTY()
	UTopDownGameInstance*TopDownGameInstance;
};
