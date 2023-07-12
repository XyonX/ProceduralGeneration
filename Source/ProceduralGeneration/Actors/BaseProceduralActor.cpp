// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseProceduralActor.h"
#include "ProceduralGeneration/Game/TopDownGameInstance.h"
#include "ProceduralGeneration/Generator/CoreGenerator.h"
#include "ProceduralGeneration/Spawner/CoreSpawner.h"




ABaseProceduralActor::ABaseProceduralActor()
{
	// TURNING OFF TICK
	PrimaryActorTick.bCanEverTick = false;
	
}

void ABaseProceduralActor::BeginPlay()
{
	
	Super::BeginPlay();
	SetupInput();
	
	TopDownGameInstance=Cast<UTopDownGameInstance>(GetGameInstance());
	

	if(RunGenerator() == false)
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Generator Failed !!!  "));
		}
		return;
	}
	if(RunSpawner() ==false)
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Spawner Failed !!!  "));
		}
		return;
	}
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Generation Successfull !!!  "));
	}

}

void ABaseProceduralActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABaseProceduralActor::SetupInput()
{
	
	// Get the player controller
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController)
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Controller Not found "));}
		return;
	}
	
}

bool ABaseProceduralActor::RunGenerator()
{
	// Create a new instance of UCoreGenerator class
	//Generator = NewObject<UCoreGenerator>(this, CustomGenerator);
	//Generator->Init(ControllerWidget,FloorMesh,NumTiles_X,CustomGenerator);
	//Generator->AddUIEntry();
	//return  Generator->Run(AllTilesPTR,TotalSpawnables);
	return false;
}

bool ABaseProceduralActor::RunSpawner()
{
	//Spawner = NewObject<UCoreSpawner>(this,DefaultSpawner);
	//Spawner->Init(&AllTilesPTR,TotalSpawnables,DefaultTile,DefaultSpawnable,NumTiles_X,NumTiles_Y);

	//return  Spawner->Run();
	return false;
}










