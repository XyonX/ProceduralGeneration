/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/


#include "Tile.h"
#include "CorePlugin/Spawnables/Spawnable.h"

UTile::UTile()
{
	Index = 6969;
	FVector2D pos(0,0);
	//SelectedTiledMesh=nullptr;
	CollapseStatus=EcollapseStatus::NotCollapsed;
	Position_2D = pos;
	World_Location = FVector(0,0,0);
}
UTile::~UTile()
{
	SelectedSpawnable=nullptr;
}

void UTile::Init(int InIndex, FVector2D InPos2D,FVector InWorldLocation)
{
	Index=InIndex;
	Position_2D= InPos2D;
	World_Location = InWorldLocation;


}

bool UTile::AllocateSpawnables(TMap<int32, USpawnable*>* InTotalSpawnables)
{
	AllocatedSpawnables.Reserve(InTotalSpawnables->Num());
	if(InTotalSpawnables->IsEmpty())
	{
		return false;
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Total Mesh Array is Empty !!! Set Default Mesh Failed  "));}
	}
	for ( auto& pair : *InTotalSpawnables)
	{
		AllocatedSpawnables.Add(pair.Value);
	}
	return true;
	

}

//	SET COLLPSE STATUS IN THE FTILE STRUCT
void UTile::SetCollapseStatus(EcollapseStatus CollapseStatuss)
{
	CollapseStatus =CollapseStatuss;
}
