﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CoreSpawner.generated.h"

class UTile;
class USpawnable;
/**
 This class  Handel Mesh Spawning Related Logics
 -TileMesh Replaced With Spawner
 */
UCLASS()
class PROCEDURALGENERATION_API UCoreSpawner : public UObject
{
	GENERATED_BODY()

public:
	UCoreSpawner();
//	UCoreSpawner(TArray<UTile*>*InTotalTiles, TMap<int32,USpawnable*>*InTotalSpawnables , int InMap_Height , int InMap_Width)();

	
	bool Init (TArray<UTile*>*InTotalTiles, TMap<int32,USpawnable*>*InTotalSpawnables,int InMap_Height , int InMap_Width);
	void SetTotalTiles (TArray<UTile*>*InTotalTiles);
	void SetTotalSpawnables (TMap<int32,USpawnable*>* InTotalSpawnables);



	//Generation Function

	// Choose a random mesh from available mesh array
	USpawnable* RandomSpawnableFromAvailableSpawnable(UTile* InTile);
	// This function adds an instance to the selected mesh
	void AddInstanceMesh(UTile* InSelectedTile);
	// Returns mesh with lowest entropy from given array of tiles
	void UpdateCollapsedTileData(UTile*InTile , TArray<UTile*>* InRemainingTiles, TArray<UTile*>*  InTotalCollapsedTile);

	// Just call those 4 surrounded function update function
	void UpdateSurroundingMesh(UTile* SelectedTile, TArray<UTile*>* InTotalTile);

	// Updating Surrounding Mesh
	void UpdateAvailableMesh_Left(UTile* SelectedTile,UTile* LeftNeighbour);
	void UpdateAvailableMesh_LeftUp(UTile* SelectedTile,UTile* LeftUpNeighbour);
	void UpdateAvailableMesh_LeftDown(UTile* SelectedTile,UTile* LeftDownNeighbour);
	void UpdateAvailableMesh_Right(UTile* SelectedTile, UTile* RightNeighbour);
	void UpdateAvailableMesh_RightUp(UTile* SelectedTile, UTile* RightUpNeighbour);
	void UpdateAvailableMesh_RightDown(UTile* SelectedTile, UTile* RightDownNeighbour);
	void UpdateAvailableMesh_Up(UTile* SelectedTile, UTile* UpNeighbour);
	void UpdateAvailableMesh_Down(UTile* SelectedTile, UTile* DownNeighbour);


	// Returns mesh with lowest entropy from given array of tiles
	UTile* ReturnTileWithLowestEntropy(TArray<UTile*>*  InTotalTiles);
	UTile* GetTileByID(int ID,TArray<UTile*>* InTotalTiles);
	UTile* GetTileByPosition2D(FVector2D Pos, TArray<UTile*>* InTotalTiles);



	void WaveFunctionCollapse ();
	bool Run ();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generation")
	FRandomStream Stream;
	UPROPERTY()
	USpawnable*DefaultSpawnable;
	bool bIsGenSaturated;


	int Map_Height ;
	int Map_Width ;
	

private:
	

	TArray<UTile*>* TotalTiles;
	TMap<INT32,USpawnable*>*TotalSpawnables;

	UPROPERTY()
	TArray<UTile*> RemainingTiles;
	UPROPERTY()
	TArray<UTile*> CollapsedTiles;
	UPROPERTY()
	TArray<UTile*> SaturatedTiles;
	
	
	
};
