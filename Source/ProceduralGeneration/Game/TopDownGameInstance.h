#pragma once

#include "CoreMinimal.h"
#include "CorePlugin/Data/MeshData.h"
#include "Engine/GameInstance.h"
#include "TopDownGameInstance.generated.h"

class USpawnable;
UCLASS()
class PROCEDURALGENERATION_API UTopDownGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UTopDownGameInstance(const FObjectInitializer& ObjectInitializer);


	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="GI")
	FString SpawnableItemsDataTableName ;
	
	// Data Table storing the static meshes and its properties
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="GI")
	UDataTable*SpawnableItemsData;

	//Main Spawnable Container
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="GI")
	TMap<int32 ,USpawnable*>SpawnableItems;
	//Subset of Spawnable
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="GI")
	TMap<int32 ,USpawnable*>ProceduralSpawnables;

	FMeshProperty DefaultSpawnableProperty;

	UDataTable* ImportData (FString DataTableName);


	void Init_Spawnable (UDataTable*InDT,TMap<int32 ,USpawnable*>&InSpawnables,TMap<int32 ,USpawnable*>&InProceduralSpawnables,UWorld*InWorld);
	USpawnable* GetSpawnableByID (int32 inID) {return SpawnableItems[inID];};
	TMap<int32 ,USpawnable*>* GetAllSpawnables () {return &SpawnableItems;};
	
	virtual void Init() override;

};
