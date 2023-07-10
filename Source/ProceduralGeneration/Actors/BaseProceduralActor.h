#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelEditorActions.h"
#include "CoreUI/DockTab/GenerationControllerTab.h"
#include "ProceduralGeneration/Debugging/CoreDebugContainer.h"
#include "BaseProceduralActor.generated.h"

class UCoreGenerator;
class UCoreSpawner;
class UTopDownGameInstance;
class USpawnable;
class ACoreDebugContainer;
class UTile;
class UTileMesh;



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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generation")
    int Map_Height =4;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generation")
    int Map_Width =4;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    UInstancedStaticMeshComponent* FlorInstanceMeshComponent;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    UStaticMesh* FloorMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    TArray<UTile*> AllTilesPTR;
	TMap<int32 ,USpawnable*>* TotalSpawnables;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	UTile* DefaultTile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	USpawnable* DefaultSpawnable;
	UPROPERTY()
	UTopDownGameInstance*TopDownGameInstance;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Debug")
    ACoreDebugContainer* DebugContainerActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString TileMeshDataAssetName = "DT_TileMesh";
	FName TileMeshDataAssetName_FName = "DT_TileMesh";
	TDebugger Debugger ;

	
	//INPUT
	//Create a input Component and bind it with the fucntion
	void SetupInput();
	
	// Context THAT CONTAINS INPUT ACTIONS CAN HAVE MORE THAN ONE 
	UPROPERTY (EditDefaultsOnly,BlueprintReadWrite,Category="Input mapping Context")
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
	bool OnDelegate ();
	static FOnGenerateButtonClick GenerateClickDelegate_Actor ;


	// Default  Generator  if   custom   generator  is  not  available

	TSubclassOf<UCoreGenerator>DefaultGenerator;
	TSubclassOf<UCoreSpawner>DefaultSpawner;

	//user can select the    custom generator ifd    they  want to  use  custom  algorithm
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Defaults")
	TSubclassOf<UCoreGenerator> CustomGenerator;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Defaults")
	TSubclassOf<UCoreSpawner> CustomSpawner;
	
	//TSharedPtr<UCoreGenerator>Generator;
	UPROPERTY()
	UCoreGenerator* Generator;
	UPROPERTY()
	UCoreSpawner* Spawner;
	

	bool RunGenerator ();
	bool RunSpawner ();
	
	
};







