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

	//Setup
	UTileMap();

	//Delete AllThe Elements
	~UTileMap();

	//This Overrides The  [ ] Operator
	// Can Do Both Operation READ or WRITE
	UTile*& operator[](const FVector2D& key)
	{
		return AllTilesPTR[key];
	}

	//Function To Addd
	void Add (UTile* Tile) ;
		
private:
	//Main HashMap
	//std::unordered_map<FMatrixPosition, UTile*> AllTilesPTR;
	// wwrite a new ccode

	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	TMap<FVector2D , UTile*>AllTilesPTR;
};
