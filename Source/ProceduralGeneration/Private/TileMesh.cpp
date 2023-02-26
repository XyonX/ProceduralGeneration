// Fill out your copyright notice in the Description page of Project Settings.


#include "TileMesh.h"

#include "Tile.h"
#include "Components/InstancedStaticMeshComponent.h"


UTileMesh::UTileMesh()
{
	
}

UTileMesh::~UTileMesh()
{
	
	for (int32 i = OwnerTileList.Num() - 1; i >= 0; i--)
	{
		OwnerTileList.RemoveAt(i);
	}
	delete InstancedMesh ;
}

void UTileMesh::Init(AActor* owneractor)
{
	Owner =owneractor;
	InstancedMesh =  NewObject<UInstancedStaticMeshComponent>(owneractor);
	InstancedMesh->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	InstancedMesh->SetStaticMesh(TileMesh);
	InstancedMesh->SetVisibility(true);
}
