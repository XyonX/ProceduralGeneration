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

    // THE MAIN TILES CONTAINER			//TODO DELETE THEM LATER
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    TArray<UTile*> AllTilesPTR;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    TArray<UTile*> RemainingTiles;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    TArray<UTile*> CollapsedTiles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	TArray<UTileMesh*> TotalTileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	UTileMesh* DefaultTileMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	UTile* DefaultTile;
	

	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    bool bWantCustomTileSize;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    float AllTiles_Float;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Debug")
    ACoreDebugContainer* DebugContainerAcotr;
    

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
	UTile* ChooseRandomTile(TArray<UTile*>& AllTileToChooseFrom);

	// Choose a random mesh from available mesh array
	UTileMesh* RandomMeshFromAvailableMesh(UTile* Tile);

	// This function adds an instance to the selected mesh
	void AddInstanceMesh(int ID, TArray<UTile*>& TotalTile);

	void GenerateBaseFloor(TArray<UTile*>& TotalTile);

	// Just call those 4 surrounded function update function
	void UpdateSurroundingMesh(UTile* SelectedTile, TArray<UTile*>& TotalTile);

	// Updating Surrounding Mesh
	void UpdateAvailableMesh_Left(UTile* SelectedTile, TArray<UTile*>& TotalTile);
	void UpdateAvailableMesh_Right(UTile* SelectedTile, TArray<UTile*>& TotalTile);
	void UpdateAvailableMesh_Up(UTile* SelectedTile, TArray<UTile*>& TotalTile);
	void UpdateAvailableMesh_Down(UTile* SelectedTile, TArray<UTile*>& TotalTile);

	// Returns mesh with lowest entropy from given array of tiles
	void InitTileMesh(TArray<UTileMesh*>& TotalTileMeshes);
	void UpdateCollapsedTileData(int ID, int ArrayPosition, TArray<UTile*>& TotalTile, TArray<UTile*>& RemainingTilee, TArray<UTile*>&  TotalCollapsedTile);

	// Returns mesh with lowest entropy from given array of tiles
	int ReturnMeshIDWithLowEntropy(TArray<UTile*>&  TotalTile);
	UTile* GetTileByID(int ID,TArray<UTile*>& TotalTile);
	UTile* GetTileByPosition2D(FMatrixPosition Pos, TArray<UTile*>& TotalTile);
	
	
};







