/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/


#include "TileMap.h"

UTileMap::UTileMap() : AllTilesPTR()
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
	/*for (auto it = AllTilesPTR.begin(); it != AllTilesPTR.end(); )
	{
		UTile* Tile = it->second;
		it = AllTilesPTR.erase(it);
		Tile->ConditionalBeginDestroy();
	}*/
}

void UTileMap::Add(UTile* Tile)
{
	//AllTilesPTR.emplace(Tile->Position_2D,Tile );
}
