// Fill out your copyright notice in the Description page of Project Settings.


#include "TileMesh.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"

UTileMesh::UTileMesh()
{
	
}

UTileMesh::~UTileMesh()
{
	// Unregister the component from its owning actor
	if (InstancedMesh != nullptr)
	{
		InstancedMesh->UnregisterComponent();
	}
    
	// Remove the component from the scene, so that it can be garbage collected
	InstancedMesh = nullptr;

	// Remove any references to this component from the owning tiles
	for (int32 i = OwnerTileList.Num() - 1; i >= 0; i--)
	{
		OwnerTileList.RemoveAt(i);
	}
}

void UTileMesh::Init(AActor* owneractor, FTileMeshData* TileMeshData)
{
	TileMesh = TileMeshData->TileMesh;
	OwnerTileList.Empty();
	MeshTag = TileMeshData->MeshTag;
	Tiling = TileMeshData->TilingType;
	Frequency =TileMeshData->Frequency;
	CompatibleMeshTag_Left =TileMeshData->ComaptileMeshTag_Left;
	CompatibleMeshTag_Right = TileMeshData->ComaptileMeshTag_Right;
	CompatibleMeshTag_Up = TileMeshData->ComaptileMeshTag_Up;
	CompatibleMeshTag_Down = TileMeshData->ComaptileMeshTag_Down;

	InstancedMesh =  NewObject<UInstancedStaticMeshComponent>(owneractor);
	InstancedMesh->RegisterComponent();
	InstancedMesh->AttachToComponent(owneractor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	InstancedMesh->SetStaticMesh(TileMesh);
	InstancedMesh->SetVisibility(true);
	
}

void UTileMesh::SetMeshPivot(UStaticMesh* In_Mesh)
{
	FVector BoundsOrigin , BoundsExtent ;
	//In_Mesh->GetLocalBound
}
