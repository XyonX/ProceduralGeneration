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
/*
UDataTable* UTopDownGameInstance::ImportData(const FString& DataTablePath)
{
//return   Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *DataTablePath));

	FString AssetPath = FString::Printf(TEXT("/ProceduralGeneration/Data/%s.%s"), *SpawnableItemsDataTableName, *SpawnableItemsDataTableName);
	//FString AssetPath = FString::Printf(TEXT("ProceduralGeneration/Data/DT_MeshProperty.DT_MeshProperty"));
	//return   Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *DataTablePath));
	return   Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *AssetPath));
}*/

UDataTable* UTopDownGameInstance::ImportData(FString DataTableName)
{
	FString AssetPath = FString::Printf(TEXT("/ProceduralGeneration/Data/%s.%s"), *DataTableName, *DataTableName);
	return   Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *AssetPath));
}

void UTopDownGameInstance::Init_Spawnable(UDataTable* inDT, TArray<USpawnable*>& inSpawnables)
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
		Spawnable->Init(MP->Mesh,MP->Icon,MP->TilingType,MP->MeshPivotPosition,MP->MeshQuadrantPosition);
		inSpawnables.Add(Spawnable);
	}
	

	
}

void UTopDownGameInstance::Init_Spawnable(UDataTable* inDT, TMap<int32, USpawnable*>& inSpawnables)
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
		Spawnable->Init(MP->Mesh,MP->Icon,MP->TilingType,MP->MeshPivotPosition,MP->MeshQuadrantPosition);
		inSpawnables.Add(Spawnable->GetID(),Spawnable);
	}
}

void UTopDownGameInstance::Init()
{
	Super::Init();

	// Usage example:
	FString DataTablePath = "/ProceduralGeneration/Data/DT_MeshProperty.DT_MeshProperty";
	UDataTable* LoadedDataTable =ImportData(SpawnableItemsDataTableName);
	if (LoadedDataTable)
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Data Table Found "));}
	}
	
	Init_Spawnable(LoadedDataTable,SpawnableItems);
}
