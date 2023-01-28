// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProceduralActor.generated.h"





/**
 * @brief FTILE MESH IS THE SINGLE MESH SELECTED CONTAINS LEFT RIGHT UP DOWN SUITABLE MESH ARRAY
 * 
 */


UENUM(BlueprintType)
enum class EcollapseStatus : uint8
{
	NotCollapsed = 0		UMETA(DisplayName = "Not Collapsed"),
	Collapsed =1		UMETA(DisplayName = "Collaped")	
};

USTRUCT(BlueprintType)
struct FMatrixPosition
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Position")
	int Length ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Position")
	int Width ;
};
USTRUCT(BlueprintType)
struct FMatchingTileArray
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	TArray<UStaticMesh*>LeftTileMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	TArray<UStaticMesh*>RightTileMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	TArray<UStaticMesh*>UpTileMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	TArray<UStaticMesh*>DownTileMesh;
	
};

USTRUCT(BlueprintType)
struct FTileMesh
{
	GENERATED_BODY()
	FTileMesh();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	UStaticMesh*TileMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	UStaticMeshComponent*InstancedMesh;
	void SetTileMesh(UStaticMesh* InTileMesh);
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	FMatchingTileArray MatchingTiles;
	FMatchingTileArray GetMatchingTiles ();
	
};

USTRUCT(BlueprintType)
struct FTile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	int ID ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	FTileMesh SelectedTiledMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	FMatrixPosition Position_2D ; 
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	FVector World_Location ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	EcollapseStatus CollapseStatus ;
	void SetCollapseStatus( EcollapseStatus CollapseStatuss);
	//void SetSelectedMesh ( FTileMesh TileMesh);
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	TArray<FTileMesh>  AllAvailableMeshToChooseFrom;
	
	
	
};



USTRUCT()
struct FSelectedMatchingMesh
{
	GENERATED_BODY()
	UStaticMesh* LeftTileMesh;
	UStaticMesh* RightTileMesh;
	UStaticMesh*UpTileMesh;
	UStaticMesh*DownTileMesh;
};



UCLASS()
class PROCEDURALGENERATION_API ABaseProceduralActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseProceduralActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	

	//Variables

	// these are number like 100x100 procedural tile
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Generation")
	int Map_Length ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Generation")
	int Map_Width ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Generation")
	FRandomStream Stream ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	float Actor_Length ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	float Actor_Length_X ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	float Actor_Length_Y ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	UInstancedStaticMeshComponent*InstancedMesh ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	UStaticMesh*StaticMesh ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	bool bwantToSpawnTiles;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	TArray<FTile> AllTiles;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	TArray<FTile> RemainingTiles;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	bool bWantCustomTileSize;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	TArray<FTileMesh>TotalTileMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	float AllTiles_float ;
	//std::vector<int> AllTile_Vec;

	/*
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	UInstancedStaticMeshComponent*Mesh_Left ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	UInstancedStaticMeshComponent*Mesh_Right ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	UInstancedStaticMeshComponent*Mesh_Up ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	UInstancedStaticMeshComponent*Mesh_Down ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	UInstancedStaticMeshComponent*Mesh_LeftUp ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	UInstancedStaticMeshComponent*Mesh_RightUp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	UInstancedStaticMeshComponent*Mesh_LeftDown;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	UInstancedStaticMeshComponent*Mesh_RightDown;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	UInstancedStaticMeshComponent*Mesh_Middle;*/
	
		
	
	
	
	//Functions

	UFUNCTION(BlueprintCallable)
	bool GenerateTile( );
	void CalculateMeshLength();
	void WaveFunctionCollapse();



	// RENEWED FUNCTION WITH NEW ALGO APPROACH

	UFUNCTION(BlueprintCallable)
	void GenerateTile_NEW( TArray<FTile> & GeneratedTile );

	// Generate All Tiles Tile 
	FTile ChooseRandomTile(TArray<FTile>AllTileToChooseFrom);

	// Updating Surrounding Mesh
	UFUNCTION()
	void UpdateAvailableMesh_Left(FTile SelectedTile );
	UFUNCTION()
	void UpdateAvailableMesh_Right(FTile SelectedTile );
	UFUNCTION()
	void UpdateAvailableMesh_Up(FTile SelectedTile );
	UFUNCTION()
	void UpdateAvailableMesh_Down(FTile SelectedTile );

	FTile ReturnMeshWithLowEntropy (TArray<FTile> TotalTile);
	FTileMesh RandomMeshFromAvailableMesh(TArray<FTileMesh>AvailableMeshArray);

	
	
	
};

