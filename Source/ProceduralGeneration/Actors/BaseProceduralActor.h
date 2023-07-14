#pragma once
#include "CoreMinimal.h"
#include "CoreUI/DockTab/GenerationControllerTab.h"
#include "GameFramework/Actor.h"
#include "BaseProceduralActor.generated.h"


class UTile;
class UTopDownGameInstance;
class UCoreSpawner;
class UCoreGenerator;
class SGenerationControllerTab;
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

	UPROPERTY()
	UTopDownGameInstance*TopDownGameInstance;
	
	/**user can select the    custom generator if they  want to  use  custom  algorithm */
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Defaults")
	TSubclassOf<UCoreGenerator> CustomGenerator;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Defaults")
	TSubclassOf<UCoreSpawner> CustomSpawner;
	
	bool RunGenerator ();
	bool RunSpawner ();


private:

	UPROPERTY()
	UCoreGenerator* Generator;
	UPROPERTY()
	UCoreSpawner* Spawner;


	TArray<UTile*>* Grid;
	
	
};







