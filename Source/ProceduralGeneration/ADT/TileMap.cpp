// Fill out your copyright notice in the Description page of Project Settings.


#include "TileMap.h"

UTileMap::UTileMap()
{
}

void UTileMap::Add(UTile* Tile)
{
	AllTilesPTR [Tile->Position_2D]=Tile ;
}
