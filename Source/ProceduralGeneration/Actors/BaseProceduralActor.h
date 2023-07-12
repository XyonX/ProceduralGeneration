#pragma once
#include "CoreMinimal.h"
#include "CoreUI/DockTab/GenerationControllerTab.h"
#include "GameFramework/Actor.h"
#include "BaseProceduralActor.generated.h"


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

	UTopDownGameInstance*TopDownGameInstance;

	
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

	/**UI FUNCTIONS */
	void ToggleTab();
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	bool OnDelegate ();
	static FOnGenerateButtonClick GenerateClickDelegate_Actor ;


	
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
	
	
};







