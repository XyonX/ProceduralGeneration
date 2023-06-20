#pragma once

#include "CoreMinimal.h"
#include "MeshData.generated.h"

UCLASS(BlueprintType)
class PROCEDURALGENERATION_API UMeshData : public UDataAsset
{
	GENERATED_BODY()

public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Generation")
	//TArray<FVector> Vertices;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Generation")
	//TArray<int32> Indices;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Data")
	TArray<UStaticMesh*>PrefabBuildings;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Data")
	TArray<UStaticMesh*>Walls;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Data")
	TArray<UStaticMesh*>Roads1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Data")
	TArray<UStaticMesh*>Roads2;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Data")
	TArray<UStaticMesh*>Roads3;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Data")
	TArray<UStaticMesh*>RoadJunction;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Data")
	TArray<UStaticMesh*>SideWalk1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Data")
	TArray<UStaticMesh*>SideWalk2;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Data")
	TArray<UStaticMesh*>SideWalk3;
	
};