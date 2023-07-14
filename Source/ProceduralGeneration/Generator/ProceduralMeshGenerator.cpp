// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralMeshGenerator.h"

TArray<UTile*>* UProceduralMeshGenerator::Run()
{
	Super::Run();
	GenerateGridMesh();
	return &Grid;
}

bool UProceduralMeshGenerator::GenerateTile_HeightMap(FVector2D InGridSize, FVector2D InTileSize,
	TArray<UTile*>& OutGrid)
{
	int index=0;
	for (int Y = 0 ; Y<  InGridSize.Y ; Y++)
	{
		for (int X = 0 ; X< InGridSize.X ; X++)
		{
			
			index++;
			FVector2D Pos2D(X,Y);
			
			// create a new instance of UTile with NewObject
			UTile* Tile = NewObject<UTile>();

			float Height =HeightMap[Y*(GridSize.Y+1)+X];

			FVector WorldLoc = FVector (X*TileSize.X,Y*TileSize.Y,Height);

			TilesLocationData.Add(WorldLoc);
			
			Tile->Init(index,Pos2D,WorldLoc);


			OutGrid.Add(Tile);
			
		}
	}
	return true;
}
bool UProceduralMeshGenerator::GenerateGridMesh()
{
	AActor* Owner = GetTypedOuter<AActor>();
	if (Owner == nullptr)
	{
		return false;
	}

	// Create and attach the UProceduralMeshComponent to the AActor
	ProceduralMesh = NewObject<UProceduralMeshComponent>(Owner);
	ProceduralMesh->SetupAttachment(Owner->GetRootComponent()); 
	ProceduralMesh->RegisterComponent();
	ProceduralMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); 
	ProceduralMesh->SetVisibility(true);
	ProceduralMesh->Activate();

	return true;
	
}
