﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGridActor.h"

#include "ProceduralMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"


struct FProcMeshTangent;
// Sets default values
ABaseGridActor::ABaseGridActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GridMesh=CreateDefaultSubobject<UProceduralMeshComponent>("Grid Preocedural Mesh");
	NumColumns=16;
	NumRows=16;
	CellSize=4;
}

// Called when the game starts or when spawned
void ABaseGridActor::BeginPlay()
{
	Super::BeginPlay();
	GenerateGridMesh();
	
}

// Called every frame
void ABaseGridActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ABaseGridActor::GenerateGridMesh()
{
	// Calculate the grid size
	const float HalfWidth = NumColumns * CellSize * 0.5f;
	const float HalfHeight = NumRows * CellSize * 0.5f;
	
	UWorld* World = GetWorld();

	for (int32 Row = 0; Row <= NumRows; ++Row)
	{
		for (int32 Col = 0; Col <= NumColumns; ++Col)
		{
			const FVector VertexLocation = FVector(Col * CellSize - HalfWidth, Row * CellSize - HalfHeight, 0.0f);

			// Add vertex
			Vertices.Add(VertexLocation);

			// Add UVs
			const FVector2D UV((float)Col / NumColumns, (float)Row / NumRows);
			UVs.Add(UV);

			// Skip the last row and column as they won't form triangles
			if (Row < NumRows && Col < NumColumns)
			{
				const int32 VertexIndex = Row * (NumColumns + 1) + Col;
				Index.Add(VertexIndex);

				// Create triangles
				Triangles.Add(VertexIndex);
				Triangles.Add(VertexIndex + 1);
				Triangles.Add(VertexIndex + NumColumns + 1);

				Triangles.Add(VertexIndex + NumColumns + 1);
				Triangles.Add(VertexIndex + 1);
				Triangles.Add(VertexIndex + NumColumns + 2);
				
			}
		}
	}

	// Calculate normals (assuming flat grid)
	for (int32 i = 0; i < Vertices.Num(); ++i)
	{
		Normals.Add(FVector(0.0f, 0.0f, -1.0f));
	}

	// Update the grid mesh
	GridMesh->CreateMeshSection(0, Vertices, Triangles, Normals, UVs, TArray<FColor>(), TArray<FProcMeshTangent>(), false);

	// Create a dynamic material instance for each tile
	UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(MaterialTemplate, this);
	// Set the desired color for the tile
	FLinearColor ColorParameter = FLinearColor::MakeRandomColor();
	DynMaterial->SetVectorParameterValue("Base Color", ColorParameter);

	GridMesh->SetMaterial(0, DynMaterial);



	return true;
}

