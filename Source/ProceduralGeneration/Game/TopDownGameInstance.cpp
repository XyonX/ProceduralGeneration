// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownGameInstance.h"

#include "CorePlugin/Data/MeshData.h"
#include "CorePlugin/Spawnables/Spawnable.h"
#include "Engine/Texture2DArray.h"
#include "ThumbnailRendering/ThumbnailManager.h"
#include "UObject/ConstructorHelpers.h"

UTopDownGameInstance::UTopDownGameInstance(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	
}


UDataTable* UTopDownGameInstance::ImportData(FString DataTableName)
{
	FString AssetPath = FString::Printf(TEXT("/ProceduralGeneration/Data/%s.%s"), *DataTableName, *DataTableName);
	return   Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *AssetPath));
}

void UTopDownGameInstance::Init_Spawnable(UDataTable* inDT, TMap<int32, USpawnable*>& inSpawnables,UWorld*inWorld)
{
	TArray<FMeshProperty*>AllMeshProperties;
	inDT->GetAllRows<FMeshProperty>(TEXT(""),AllMeshProperties);

	if (AllMeshProperties.IsEmpty())
	{
		return;
	}
	//UThumbnailManager& ThumbnailManager = UThumbnailManager::Get();
	
	for (FMeshProperty*MP : AllMeshProperties)
	{
		USpawnable * Spawnable = NewObject<USpawnable>();
		Spawnable->Init(MP);
		Spawnable->CreateInstance(inWorld);
		inSpawnables.Add(Spawnable->GetID(),Spawnable);
		if(Spawnable->IsAProceduralSpawnable())
		{
			ProceduralSpawnables.Add(Spawnable->GetID(),Spawnable);
		}
	}
}

void UTopDownGameInstance::Init()
{
	Super::Init();

	// Usage example:
	FString DataTablePath = "/ProceduralGeneration/Data/DT_MeshProperty.DT_MeshProperty";
	UDataTable* LoadedDataTable =ImportData(SpawnableItemsDataTableName);
	UWorld*CurrentWorld=GetWorld();
	if(WorldContext)
	{
		Init_Spawnable(LoadedDataTable,SpawnableItems,CurrentWorld);
	}
	
}
