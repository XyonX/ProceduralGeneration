// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"


UTile::UTile()
{
	ID = 6969;
	FMatrixPosition pos(0,0);
	//SelectedTiledMesh=nullptr;
	CollapseStatus=EcollapseStatus::NotCollapsed;
	Position_2D = pos;
	World_Location = FVector(0,0,0);
}

void UTile::Init(int id, FMatrixPosition pos2d, FVector worldloc, TArray<FTileMesh>& totaltilemesh)
{
	ID=id;
	Position_2D=pos2d;
	World_Location=worldloc;
	AllAvailableMeshToChooseFrom.Reserve(totaltilemesh.Num());
	if(totaltilemesh.IsEmpty())
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Total Mesh Array is Empty !!! Set Default Mesh Failed  "));}
	}
	for ( FTileMesh&MeshElement : totaltilemesh)
	{
		AllAvailableMeshToChooseFrom.Add(MeshElement);
	}
}
/*
UTile::UTile(int id, FMatrixPosition pos2d, FVector worldloc, TArray<FTileMesh>& totaltilemesh)
{
	ID=id;
	Position_2D=pos2d;
	World_Location=worldloc;
	AllAvailableMeshToChooseFrom.Reserve(totaltilemesh.Num());
	if(totaltilemesh.IsEmpty())
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Total Mesh Array is Empty !!! Set Default Mesh Failed  "));}
	}
	for ( FTileMesh&MeshElement : totaltilemesh)
	{
		AllAvailableMeshToChooseFrom.Add(MeshElement);
	}
}*/

//	SET COLLPSE STATUS IN THE FTILE STRUCT
void UTile::SetCollapseStatus(EcollapseStatus CollapseStatuss)
{
	CollapseStatus =CollapseStatuss;
}