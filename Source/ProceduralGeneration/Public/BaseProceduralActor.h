#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include <Templates/SharedPointer.h>
#include "FTile.h"
#include "BaseProceduralActor.generated.h"

// COLLAPSE STATUS ENUM
class ACoreDebugContainer;
struct FMatrixPosition;

// LLinked list for tile		// NOT USING CURRENTLY
USTRUCT()
struct FTileContainer
{
    GENERATED_BODY()
    std::unique_ptr<FTile> Tile;
    FTileContainer* NextTileContainer;

    ~FTileContainer()
    {
        delete NextTileContainer;
    }
};

// CAN BE CONSIDERED AS A SINGLE MESH UNIT CONTAINING ONE MAIN MESH AND OTHER NEEDED VARIABLES

// THE MAIN TILE WE ARE GENERATING AND STORING IN AN ARRAY

// STARTING OF THE MAIN CLASS

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
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
    // Called every frame
    //virtual void Tick(float DeltaTime) override;

    // Variables
    // these are numbers like 100x100 procedural tile
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generation")
    int Map_Height;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generation")
    int Map_Width;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generation")
    FRandomStream Stream;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    float Actor_Length;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    float Actor_Length_X;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    float Actor_Length_Y;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    float Actor_Length_Z;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    UInstancedStaticMeshComponent* FlorInstanceMesh;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    UInstancedStaticMeshComponent* TileMeshInstance;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    UStaticMesh* StaticMesh;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    bool bWantBaseFloor;

    // THE MAIN TILES CONTAINER
    TArray<FTile*> AllTilesPTR;
    TArray<FTile*> RemainingTiles;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile")
    TArray<FTile> AllTilesREF;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    TArray<FTile*> CollapsedTiles;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    bool bWantCustomTileSize;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    TArray<FTileMesh> TotalTileMesh;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    float AllTiles_Float;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Debug")
    ACoreDebugContainer* DebugContainerAcotr;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    FTileMesh DefaultTileMesh;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    FTile DefaultTile;

    // Functions

	// The Main function
	UFUNCTION(BlueprintCallable)
	void WaveFunctionCollapse();

	// Calculate the length of mesh
	void CalculateMeshLength();

	// Generate tile
	// Uses the Calculate Length function data to provide world position
	UFUNCTION(BlueprintCallable)
	bool GenerateTile();

	void SetAllTilesREF(TArray<FTile*>& alltile);

	// Choose a random tile from given array
	// Mainly for first random tile choose
	FTile* ChooseRandomTile(TArray<FTile*> AllTileToChooseFrom);

	// Choose a random mesh from available mesh array
	FTileMesh* RandomMeshFromAvailableMesh(FTile* Tile);

	// This function adds an instance to the selected mesh
	void AddInstanceMesh(int ID, TArray<FTile*> TotalTile);

	void GenerateBaseFloor(TArray<FTile*>& TotalTies);

	// Just call those 4 surrounded function update function
	void UpdateSurroundingMesh(FMatrixPosition Position2D, int SelectedTileID, TArray<FTile*> TotalTile);

	// Updating Surrounding Mesh
	void UpdateAvailableMesh_Left(FMatrixPosition Position2D, int SelectedTileID, TArray<FTile*> TotalTile);
	void UpdateAvailableMesh_Right(FMatrixPosition Position2D, int SelectedTileID, TArray<FTile*> TotalTile);
	void UpdateAvailableMesh_Up(FMatrixPosition Position2D, int SelectedTileID, TArray<FTile*> TotalTile);
	void UpdateAvailableMesh_Down(FMatrixPosition Position2D, int SelectedTileID, TArray<FTile*> TotalTile);

	// Returns mesh with lowest entropy from given array of tiles
	void InitTileMesh(TArray<FTileMesh>& TotalTileMeshes);
	void UpdateCollapsedTileData(int ID, int ArrayPosition, TArray<FTile*> TotalTile, TArray<FTile*> RemainingTilee, TArray<FTile*> TotalCollapsedTile);

	// Returns mesh with lowest entropy from given array of tiles
	int ReturnMeshIDWithLowEntropy(TArray<FTile*> TotalTile);
	FTile* GetTileByID(int ID, TArray<FTile*> TotalTile);
	FTile* GetTileByPosition2D(FMatrixPosition Pos, TArray<FTile*> TotalTile);
	
	
};







