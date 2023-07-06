// Fill out your copyright notice in the Description page of Project Settings.


#include "RuntimeAppearanceEditor.h"
#include "KismetProceduralMeshLibrary.h"


// Sets default values
ARuntimeAppearanceEditor::ARuntimeAppearanceEditor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARuntimeAppearanceEditor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARuntimeAppearanceEditor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARuntimeAppearanceEditor::ExtractMeshData()
{
	UKismetProceduralMeshLibrary::CopyProceduralMeshFromStaticMeshComponent(CharacterMeshComponent,0,PMC,false);

	 PMS_FullBody= PMC->GetProcMeshSection(0);

	UKismetProceduralMeshLibrary::GetSectionFromStaticMesh(CharacterMesh,0,Index,Vertices,Triangles,Normals,UVs,Tangents);

	
	PMC->GetProcMeshSection(0);
}

