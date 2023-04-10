// Fill out your copyright notice in the Description page of Project Settings.


#include "TileMap.h"

UTileMap::UTileMap()
{
}

UTileMap::~UTileMap()
{
	/*for (auto& Pair : AllTilesPTR)
	{
		UTile* Tile = Pair.second;
		Tile->ConditionalBeginDestroy();
	}

	UTile* Tile = AllTilesPTR[i];
	Tile->ConditionalBeginDestroy();
	AllTilesPTR.RemoveAt(i);*/
	for (auto it = AllTilesPTR.begin(); it != AllTilesPTR.end(); )
	{
		UTile* Tile = it->second;
		it = AllTilesPTR.erase(it);
		Tile->ConditionalBeginDestroy();
	}
}

void UTileMap::Add(UTile* Tile)
{
	AllTilesPTR [Tile->Position_2D]=Tile ;
}
