/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/
#include "BaseProceduralActor.h"
#include "ProceduralGeneration/Game/TopDownGameInstance.h"
#include "ProceduralGeneration/Generator/CoreGenerator.h"
#include "ProceduralGeneration/Spawner/CoreSpawner.h"




ABaseProceduralActor::ABaseProceduralActor()
{
	// TURNING OFF TICK
	PrimaryActorTick.bCanEverTick = false;

	CustomGenerator=UCoreGenerator::StaticClass();
	CustomSpawner=UCoreSpawner::StaticClass();
	
}

void ABaseProceduralActor::BeginPlay()
{
	
	Super::BeginPlay();
	
	TopDownGameInstance=Cast<UTopDownGameInstance>(GetGameInstance());

	if(RunGenerator() == false)
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Generator Failed !!!  "));
		}
		return;
	}
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Grid Created !!!  "));
	}
	
	
/*	for (	UTile*Tile : (*Grid)  )
	{
		DrawDebugPoint(GetWorld(),Tile->GetWorldLocation(),10,FColor::Green,true,-1,0);//depth priority of 0 means always visible
		DrawDebugString(GetWorld(), Tile->GetWorldLocation(), *FString::Printf(TEXT(" %f,%f"),Tile->GetWorldLocation().X, Tile->GetWorldLocation().Y), nullptr, FColor::Red, -1.0F, false);
	}*/
	/*
	if(RunSpawner() ==false)
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Spawner Failed !!!  "));
		}
		return;
	}
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Generation Successfull !!!  "));
	}*/

}

void ABaseProceduralActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

bool ABaseProceduralActor::RunGenerator()
{
	// Create a new instance of UCoreGenerator class
	Generator = NewObject<UCoreGenerator>(this, CustomGenerator);
	Generator->Run();
	return true;
	
/*	if(Generator)
	{
		Grid= Generator->Run();
		if(!Grid->IsEmpty())
		{
			return true;
		}
	}
	return false;*/
}

bool ABaseProceduralActor::RunSpawner()
{
	//Spawner = NewObject<UCoreSpawner>(this,DefaultSpawner);
	//Spawner->Init(&AllTilesPTR,TotalSpawnables,DefaultTile,DefaultSpawnable,NumTiles_X,NumTiles_Y);
	//return  Spawner->Run();
	return false;
}

void ABaseProceduralActor::GenerateTerrainAsync()
{

}










