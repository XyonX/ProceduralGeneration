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

void UTile::Init(int id, FMatrixPosition pos2d,FVector2D Unscaledloc, TArray<UTileMesh*>& totaltilemesh)
{
	ID=id;
	Position_2D=pos2d;
	World_Location_2D_UnScaled =Unscaledloc;
	World_Location = FVector(0.f,0.f,0.f);
	AllAvailableMeshToChooseFrom.Reserve(totaltilemesh.Num());
	if(totaltilemesh.IsEmpty())
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Total Mesh Array is Empty !!! Set Default Mesh Failed  "));}
	}
	for ( UTileMesh* MeshElement : totaltilemesh)
	{
		AllAvailableMeshToChooseFrom.Add(MeshElement);
	}
}

UTile::~UTile()
{
	
	SelectedTiledMesh = nullptr;
	for (int32 i = AllAvailableMeshToChooseFrom.Num() - 1; i >= 0; i--)
	{
		AllAvailableMeshToChooseFrom.RemoveAt(i);
	}
}

//	SET COLLPSE STATUS IN THE FTILE STRUCT
void UTile::SetCollapseStatus(EcollapseStatus CollapseStatuss)
{
	CollapseStatus =CollapseStatuss;
}
