// Fill out your copyright notice in the Description page of Project Settings.


#include "TileMesh.h"
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
	if(InstancedMesh != nullptr)
		delete InstancedMesh ;
}

void UTileMesh::Init(AActor* owneractor, FTileMeshData* TileMeshData)
{
	TileMesh = TileMeshData->TileMesh;
	OwnerTileList.Empty();
	MeshTag = TileMeshData->MeshTag;
	CompatibleMeshTag_Left =TileMeshData->ComaptileMeshTag_Left;
	CompatibleMeshTag_Right = TileMeshData->ComaptileMeshTag_Right;
	CompatibleMeshTag_Up = TileMeshData->ComaptileMeshTag_Up;
	CompatibleMeshTag_Down = TileMeshData->ComaptileMeshTag_Down;

	InstancedMesh =  NewObject<UInstancedStaticMeshComponent>(owneractor);
	InstancedMesh->AttachToComponent(owneractor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	InstancedMesh->SetStaticMesh(TileMesh);
	InstancedMesh->SetVisibility(true);
	
}
