#pragma once
#include <Templates/SharedPointer.h>
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include <memory>

#include "CoreDebugContainer.h"
#include "Tile.h"
#include "BaseProceduralActor.generated.h"




// COLLAPSE STATUS ENUM
class ACoreDebugContainer;
struct FMatrixPosition;

/*
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
};*/

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
    UInstancedStaticMeshComponent* FlorInstanceMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	UInstancedStaticMeshComponent* DefaultInstanceMeshComponent;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    UInstancedStaticMeshComponent* TileMeshInstance;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    UStaticMesh* StaticMesh;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    bool bWantBaseFloor;

    // THE MAIN TILES CONTAINER
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    TArray<TSharedPtr<UTile>> AllTilesPTR;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    TArray<TSharedPtr<UTile>> RemainingTiles;
    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    TArray<TSharedPtr<UTile>> CollapsedTiles;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	TArray<UTile*> AllTiles;
	

	
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
    UTile* DefaultTile;

	//Debugger	custom debug manager class
	TDebugger Debugger ;
	
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
	void SetTileLength(int Lenght ,int Width);

	// Choose a random tile from given array
	// Mainly for first random tile choose
	TSharedPtr<UTile> ChooseRandomTile(TArray<TSharedPtr<UTile>>& AllTileToChooseFrom);

	// Choose a random mesh from available mesh array
	FTileMesh& RandomMeshFromAvailableMesh(TSharedPtr<UTile> Tile);

	// This function adds an instance to the selected mesh
	void AddInstanceMesh(int ID, TArray<TSharedPtr<UTile>>& TotalTile);

	void GenerateBaseFloor(TArray<TSharedPtr<UTile>>& TotalTile);

	// Just call those 4 surrounded function update function
	void UpdateSurroundingMesh(TSharedPtr<UTile> SelectedTile, TArray<TSharedPtr<UTile>>& TotalTile);

	// Updating Surrounding Mesh
	void UpdateAvailableMesh_Left(TSharedPtr<UTile> SelectedTile, TArray<TSharedPtr<UTile>>& TotalTile);
	void UpdateAvailableMesh_Right(TSharedPtr<UTile> SelectedTile, TArray<TSharedPtr<UTile>>& TotalTile);
	void UpdateAvailableMesh_Up(TSharedPtr<UTile> SelectedTile, TArray<TSharedPtr<UTile>>& TotalTile);
	void UpdateAvailableMesh_Down(TSharedPtr<UTile> SelectedTile, TArray<TSharedPtr<UTile>>& TotalTile);

	// Returns mesh with lowest entropy from given array of tiles
	void InitTileMesh(TArray<FTileMesh>& TotalTileMeshes);
	void UpdateCollapsedTileData(int ID, int ArrayPosition, TArray<TSharedPtr<UTile>>& TotalTile, TArray<TSharedPtr<UTile>>& RemainingTilee, TArray<TSharedPtr<UTile>>&  TotalCollapsedTile);

	// Returns mesh with lowest entropy from given array of tiles
	int ReturnMeshIDWithLowEntropy(TArray<TSharedPtr<UTile>>&  TotalTile);
	TSharedPtr<UTile> GetTileByID(int ID,TArray<TSharedPtr<UTile>>& TotalTile);
	TSharedPtr<UTile> GetTileByPosition2D(FMatrixPosition Pos, TArray<TSharedPtr<UTile>>& TotalTile);
	
	
};







