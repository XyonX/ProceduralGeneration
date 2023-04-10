// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralGeneration/Tiles/Tile.h"
#include "UObject/Object.h"
#include "TileMap.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALGENERATION_API UTileMap : public UObject
{
	GENERATED_BODY()

public:
	// Constructor to initialize the unordered_map
	//UTileMap() : AllTilesPTR() {}
	UTileMap();
	
	UTile*& operator[](const FMatrixPosition& key)
	{
		return AllTilesPTR[key];
	}

	void Add (UTile* Tile) ;
		
private:


	std::unordered_map<FMatrixPosition, UTile*> AllTilesPTR;
	
};
