// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"


UTile::UTile()
{
	ID = 6969;
	FVector2D pos(0,0);
	//SelectedTiledMesh=nullptr;
	CollapseStatus=EcollapseStatus::NotCollapsed;
	Position_2D = pos;
	World_Location = FVector(0,0,0);
}

void UTile::Init(int id, FVector2D pos2d, FVector2D Unscaledloc, TMap<int32, USpawnable*>* TotalSpawnables)
{
	ID=id;
	Position_2D=pos2d;
	World_Location_2D_UnScaled =Unscaledloc;
	World_Location = FVector(0.f,0.f,0.f);
	AllAvailableSpawnableToChooseFrom.Reserve(TotalSpawnables->Num());
	if(TotalSpawnables->IsEmpty())
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Total Mesh Array is Empty !!! Set Default Mesh Failed  "));}
	}
	for ( auto& pair : TotalSpawnables)
	{
		AllAvailableSpawnableToChooseFrom.Add(pair.Value);
	}
}

UTile::~UTile()
{
	SelectedSpawnable=nullptr;
}

//	SET COLLPSE STATUS IN THE FTILE STRUCT
void UTile::SetCollapseStatus(EcollapseStatus CollapseStatuss)
{
	CollapseStatus =CollapseStatuss;
}
