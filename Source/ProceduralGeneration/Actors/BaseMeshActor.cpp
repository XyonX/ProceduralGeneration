// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMeshActor.h"


// Sets default values
ABaseMeshActor::ABaseMeshActor()
{
	PrimaryActorTick.bCanEverTick = false;
	MeshCompoonent= CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	SetRootComponent(MeshCompoonent);
}

// Called when the game starts or when spawned
void ABaseMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseMeshActor::Init(UStaticMesh*inMesh,UMaterialInstanceDynamic*inMaterial)
{
	Mesh=inMesh;
	Material=inMaterial;
	
	if(MeshCompoonent)
	{
		MeshCompoonent->SetStaticMesh(Mesh);
		MeshCompoonent->CreateAndSetMaterialInstanceDynamic(0);
	}
}
