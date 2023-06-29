// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreUI/UI/TopDownIngameScreen.h"
#include "GameFramework/Actor.h"
#include "ProceduralGeneration/Game/TopDownGameInstance.h"
#include "Widgets/Layout/SGridPanel.h"
#include "UIActor.generated.h"

UCLASS()
class PROCEDURALGENERATION_API AUIActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AUIActor();
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	

	/** Dat Variables */
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="UI")
	float Height;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="UI")
	float Width;
	
	
	
	/** Getter And Setter */

	UTopDownIngameScreen*GetInGameWidget () { return IngameScreen;}


	
	//functions
	void SpawnUI_UMG_1 ();
	void SpawnUI_Slate_1 ();



	
private:

	UTopDownGameInstance*TDGameInstance;
	UTopDownIngameScreen*IngameScreen ;
	TSharedPtr<SBottomBuildingsPanel>BottomPanelWidget ;
	
	
	
};
