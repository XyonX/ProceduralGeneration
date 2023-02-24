// Fill out your copyright notice in the Description page of Project Settings.


#include "FTileMesh.h"
#include "Components/InstancedStaticMeshComponent.h"

void FTileMesh::Init(AActor* owneractor)
{
	Owner =owneractor;
	InstancedMesh = NewObject<UInstancedStaticMeshComponent>(Owner);
	InstancedMesh->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	InstancedMesh->SetStaticMesh(TileMesh);
	InstancedMesh->SetVisibility(true);
}
