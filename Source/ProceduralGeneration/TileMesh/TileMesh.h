// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "TileMesh.generated.h"

UENUM(BlueprintType)
enum class ETilingType : uint8
{
	BothDirection	UMETA(DisplayName = "Both Direction"),
	Horizontal 		UMETA(DisplayName = "Horizontal"),
	Vertical 		UMETA(DisplayName = "Vertical"),
	UnSupported 	UMETA(DisplayName = "Not Tilable"),
	
};

// This Struct is to determine which  tile to Update First Among the surrounded Tiles
USTRUCT()
struct FTileTypePriority
{
	GENERATED_BODY()
	//the Tag of the Tile Type  We  Want to Prioritize 
	FGameplayTag TileType_Tag ;
	//The Priority
	int Priority ;
	
};

class UTile ;
class UTileMeshData;

USTRUCT(BlueprintType)
struct FTileMeshData : public FTableRowBase
{
	GENERATED_BODY()

	// VARIABLES
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	UStaticMesh*TileMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	FGameplayTag MeshTag ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	ETilingType TilingType ;
	UPROPERTY(EditAnywhere, Category = "My Category", meta = (ClampMin = "0", ClampMax = "1") ,meta = (ToolTip = "Percentage How Much Tile Should Repeat before break (of total Length )"))
	float Frequency;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	FGameplayTagContainer ComaptileMeshTag_Left ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	FGameplayTagContainer ComaptileMeshTag_Right ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	FGameplayTagContainer ComaptileMeshTag_Up ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	FGameplayTagContainer ComaptileMeshTag_Down ;
};

UCLASS()
class PROCEDURALGENERATION_API UTileMesh : public UObject
{
	GENERATED_BODY()

public:

	UTileMesh();
	~UTileMesh();

	void Init(AActor* owneractor , FTileMeshData * FTileMeshData );
	void SetMeshPivot (UStaticMesh * In_Mesh) ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileMesh")
		UStaticMesh* TileMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileMesh")
		ETilingType Tiling ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileMesh")
		float Frequency;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileMesh")
		TArray<UTile*>OwnerTileList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileMesh")
		FGameplayTag MeshTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileMesh")
		FGameplayTagContainer CompatibleMeshTag_Left;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileMesh")
		FGameplayTagContainer CompatibleMeshTag_Right;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileMesh")
		FGameplayTagContainer CompatibleMeshTag_Up;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileMesh")
		FGameplayTagContainer CompatibleMeshTag_Down;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileMesh")
		UInstancedStaticMeshComponent* InstancedMesh;

};
