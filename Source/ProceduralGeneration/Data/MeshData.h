#pragma once

#include "CoreMinimal.h"
#include "MeshData.generated.h"


UENUM(BlueprintType)
enum class ETilingType : uint8
{
	UnSupported 	UMETA(DisplayName = "Not Tilable"),
	Horizontal 		UMETA(DisplayName = "Horizontal"),
	Vertical 		UMETA(DisplayName = "Vertical"),
	BothDirection	UMETA(DisplayName = "Both Direction"),
	
	
};
UENUM(BlueprintType)
enum class EMeshPivot : uint8
{
	Middle 	UMETA(DisplayName = "Middle Centered"),
	Cornered 		UMETA(DisplayName = "Cornered Centered "),
	
};
UENUM(BlueprintType)
enum class EMeshQuadrant : uint8
{
	First 	UMETA(DisplayName = "Mesh At First Local Quadrant"),
	Second 		UMETA(DisplayName = "Mesh At Second Quadrant "),
	Third 		UMETA(DisplayName = "Mesh At Third Quadrant "),
	Fourth 		UMETA(DisplayName = "Mesh At Fourth Quadrant "),
	
};

USTRUCT(BlueprintType)
struct FMeshProperty : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MeshData")
	UStaticMesh* Mesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MeshData")
	ETilingType TilingType;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MeshData")
	EMeshPivot MeshPivotPosition;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MeshData")
	EMeshQuadrant MeshQuadrantPosition;
	
};

UCLASS(BlueprintType)
class PROCEDURALGENERATION_API UMeshData : public UDataAsset
{
	GENERATED_BODY()

public:
	
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