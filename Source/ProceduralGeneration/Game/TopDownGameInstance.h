#pragma once

#include "CoreMinimal.h"
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

	//Processed Imported Data
	//UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="GI")
	//TArray<USpawnable*>SpawnableItems;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="GI")
	TMap<int32 ,USpawnable*>SpawnableItems;

	UDataTable* ImportData (FString DataTableName);

	void Init_Spawnable (UDataTable*inDT,TArray<USpawnable*>&inSpawnables);
	void Init_Spawnable (UDataTable*inDT,TMap<int32 ,USpawnable*>&inSpawnables,UWorld*InWorld);
	USpawnable* GetSpawnableByID (int32 inID) {return SpawnableItems[inID];};
	
	virtual void Init() override;

};
