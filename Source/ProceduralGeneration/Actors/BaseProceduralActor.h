#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "ProceduralGeneration/Debugging/CoreDebugContainer.h"
#include "LevelEditor.h"
#include "LevelEditorActions.h"
#include "CoreUI/DockTab/GenerationControllerTab.h"
#include "Editor/LevelEditor/Public/LevelEditorActions.h"
#include "ProceduralGeneration/Generator/CoreGenerator.h"
#include "BaseProceduralActor.generated.h"


// COLLAPSE STATUS ENUM
class ACoreDebugContainer;
struct FMatrixPosition;
class UTile;
class UTileMesh;
struct FTileMeshData;

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
    UStaticMesh* FloorMesh;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    bool bWantBaseFloor;
	bool bIsFirstGenDone ;
	bool bIsGenSaturated;

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
	
    //Data
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Data")
	UDataTable* TileMeshDataAsset ;
	TArray<FTileMeshData*>TileMeshDataArray ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString TileMeshDataAssetName = "DT_TileMesh";
	FName TileMeshDataAssetName_FName = "DT_TileMesh";

	//Debugger	custom debug manager class
	TDebugger Debugger ;

	//INPUT
	//Create a input Component and bind it with the fucntion
	void SetupInput();
	
	// Context THAT CONTAINS INPUT ACTIONS CAN HAVE MORE THAN ONE 
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input mapping Context")
	class UInputMappingContext*ProceduralGenerationMapping;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input Actions")
	class UInputAction* OpenUIAction;
	
	

	//UI
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="UI")
	FName TabID ;
	//The Actual Dock TaB
	TSharedPtr<SDockTab> MyDockTab;
	TSharedPtr<SGenerationControllerTab> ControllerWidget;
	
	static TSharedPtr<SWindow>ControllerWindow ;

	//UI FUNCTIONS
	void ToggleTab();
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	bool OnReGenerate();
	bool OnDelegate ();
	static FOnGenerateButtonClick GenerateClickDelegate_Actor ;


	// Default  Generator  if   custom   generator  is  not  available
	UPROPERTY()
	TSubclassOf<UCoreGenerator>DefaultGenerator;

	//user can select the    custom generator ifd    they  want to  use  custom  algorithm
	UPROPERTY()
	TSubclassOf<UCoreGenerator> CustomGenerator;
	
	//TSharedPtr<UCoreGenerator>Generator;
	UPROPERTY()
	 UCoreGenerator* Generator;

	bool RunGenerator ();
	
	

	
	//Setting up initial variables 
	bool Init();

	// gets the tilemesh data from data table 
    bool GetTileMeshData();

	// setup the data in totaltilemesh
	bool SetTileMeshData ();
	void InitTileMesh(TArray<UTileMesh*>& totaltilemeshes ,TArray<FTileMeshData*>& totaltilemeshedatas);
	
	// The Main function
	UFUNCTION(BlueprintCallable)
	void WaveFunctionCollapse();

	// Calculate the length of mesh
	void CalculateMeshLength();

	// Generate tile
	// Uses the Calculate Length function data to provide world position
	UFUNCTION(BlueprintCallable)
	bool GenerateTile();
	void SetTileLength(int Length_X ,int Length_Y);

	// Choose a random tile from given array
	// Mainly for first random tile choose
	UTile* ChooseRandomTile(TArray<UTile*>& AllTileToChooseFrom);

	// Choose a random mesh from available mesh array
	UTileMesh* RandomMeshFromAvailableMesh(UTile* Tile);

	// This function adds an instance to the selected mesh
	void AddInstanceMesh(UTile* SelectedTile);

	void GenerateBaseFloor(TArray<UTile*>& TotalTile);

	// Just call those 4 surrounded function update function
	void UpdateSurroundingMesh(UTile* SelectedTile, TArray<UTile*>& TotalTile);

	// Updating Surrounding Mesh
	void UpdateAvailableMesh_Left(UTile* SelectedTile,UTile* LeftNeighbour);
	void UpdateAvailableMesh_Right(UTile* SelectedTile, UTile* RightNeighbour);
	void UpdateAvailableMesh_Up(UTile* SelectedTile, UTile* UpNeighbour);
	void UpdateAvailableMesh_Down(UTile* SelectedTile, UTile* DownNeighbour);

	// Returns mesh with lowest entropy from given array of tiles
	void UpdateCollapsedTileData(UTile*Tile , TArray<UTile*>& TotalTile, TArray<UTile*>& RemainingTilee, TArray<UTile*>&  TotalCollapsedTile);

	// Returns mesh with lowest entropy from given array of tiles
	UTile* ReturnTileWithLowestEntropy(TArray<UTile*>&  TotalTile);
	UTile* GetTileByID(int ID,TArray<UTile*>& TotalTile);
	UTile* GetTileByPosition2D(FMatrixPosition Pos, TArray<UTile*>& TotalTile);
	
	
};







