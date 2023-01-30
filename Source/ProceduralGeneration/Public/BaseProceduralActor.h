// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "BaseProceduralActor.generated.h"


// COLLAPSE STATUS ENUM
class ACoreDebugContainer ;


UENUM(BlueprintType)
enum class EcollapseStatus : uint8
{
	NotCollapsed = 0		UMETA(DisplayName = "Not Collapsed"),
	Collapsed =1		UMETA(DisplayName = "Collaped")	
};

// 2D STRUCT FOR STORING XY LOCATION

USTRUCT(BlueprintType)
struct FMatrixPosition
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Position")
	int Length ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Position")
	int Width ;
};

// CAN BE CONSIDE AS A SINGLE MESH UNIT CONTAIN ONE MAIN MESH AND OTHER NEEDED VARS

USTRUCT(BlueprintType)
struct FTileMesh
{
	GENERATED_BODY()
	//FTileMesh();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	UStaticMesh*TileMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	FGameplayTag MeshTag ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	FGameplayTagContainer ComaptileMeshTag_Left ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	FGameplayTagContainer ComaptileMeshTag_Right ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	FGameplayTagContainer ComaptileMeshTag_Up ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	FGameplayTagContainer ComaptileMeshTag_Down ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	UInstancedStaticMeshComponent*InstancedMesh;
	
};

// THE MAIN TILE WE ARE GENERETING  AND STORING IN AN ARRAY

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


//									//
// STARTING OF THE MAIN CLASS		//
//									//


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

	
	//					//
	//Variables			//
	//					//

	
	// these are number like 100x100 procedural tile
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Generation")
	int Map_Height ;
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
	float Actor_Length_Z;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	UInstancedStaticMeshComponent*FlorInstanceMesh ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	UInstancedStaticMeshComponent*TileMeshInstance;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	UStaticMesh*StaticMesh ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	bool bWantBaseFloor;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	TArray<FTile> AllTiles;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	TArray<FTile> RemainingTiles;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	TArray<FTile> CollapsedTiles;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	bool bWantCustomTileSize;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	TArray<FTileMesh>TotalTileMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	float AllTiles_Float ;
	UPROPERTY(VisibleAnywhere , BlueprintReadWrite,Category="Debug")
	ACoreDebugContainer* DebugContainerAcotr;
		
	
	
	//					//
	//Functions			//
	//					//

	
	// THE MAIN FUNCTION
	UFUNCTION(BlueprintCallable)
	void WaveFunctionCollapse();

	// CALCULATE THE LENGTH OF MESH 
	void CalculateMeshLength();

	// GENERATE TILE									// USES THE CALCULATE LENGTH FUNCTION DATA TO PROVIDE WORLD POSITION 
	UFUNCTION(BlueprintCallable)
	bool GenerateTile( );
	
	//   THESE CHOOSE RANDOM TILE FROM GIVEN ARRAY		// MAINLY FOR FIRST RANDOM TILE CHOOSE
	FTile ChooseRandomTile(TArray<FTile>AllTileToChooseFrom);

	//CHOOSE A RANDOM MESH FROM   AVAILABLE MESH ARRAY
	FTileMesh RandomMeshFromAvailableMesh(FTile Tile );

	// THIS FUNCTION ADD AN INSTANCE TO THE  SELECTED MESH
	UFUNCTION()
	void AddInstanceMesh (FTile SelectedTile);
	UFUNCTION()
	void GenerateBaseFloor (TArray<FTile>TotalTies);
	UFUNCTION()
	void SetDefaultMeshForAllTiles (TArray<FTile> TotalTiles ,TArray<FTileMesh> TotalMesh );

	// JUST CALL THOSE 4 SURROUNDED  FUNCTION UPDATE FUNCTION 
	void UpdateSurroundingMesh (FTile SelectedTile);

	
	// Updating Surrounding Mesh
	UFUNCTION()
	void UpdateAvailableMesh_Left(FTile SelectedTile );
	UFUNCTION()
	void UpdateAvailableMesh_Right(FTile SelectedTile );
	UFUNCTION()
	void UpdateAvailableMesh_Up(FTile SelectedTile );
	UFUNCTION()
	void UpdateAvailableMesh_Down(FTile SelectedTile );
	// RETURNS MESH WITH LOWEST ENTROPY FROM GIVEN ARRAY OF TILES
	void CreteInstanceMeshObjectForTotalTileMesh (TArray<FTileMesh>& TotalTileMeshes);
	
	
	// RETURNS MESH WITH LOWEST ENTROPY FROM GIVEN ARRAY OF TILES
	FTile ReturnMeshWithLowEntropy (TArray<FTile> TotalTile);

	
};





