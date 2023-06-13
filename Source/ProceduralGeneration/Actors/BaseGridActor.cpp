// Fill out your copyright notice in the Description page of Project Settings.


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
	Length_X=16;
	Length_Y=16;
	CellSize=10;
}

// Called when the game starts or when spawned
void ABaseGridActor::BeginPlay()
{
	Super::BeginPlay();
	GenerateGridMesh();
	DrawPositionIndicator();
	
}

// Called every frame
void ABaseGridActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ABaseGridActor::GenerateGridMesh()
{
	// Calculate the grid size
		const float HalfWidth = Length_Y * CellSize * 0.5f;
	const float HalfHeight = Length_X * CellSize * 0.5f;
	
	UWorld* World = GetWorld();

	for (int32 Y = 0; Y <= Length_Y; ++Y)
	{
		for (int32 X = 0; X <= Length_X; ++X)
		{
			const FVector VertexLocation = FVector(X * CellSize - HalfHeight, Y * CellSize - HalfWidth, 0.0f);

			// Add vertex
			Vertices.Add(VertexLocation);
			FVector2D Loc2d = FVector2D (X,Y);
			MainContainer.Add(Loc2d, VertexLocation);

			// Add UVs
			const FVector2D UV((float)X / Length_X, (float)Y / Length_Y);
			UVs.Add(UV);

			// Skip the last row and column as they won't form triangles
			if (X < Length_X && Y < Length_Y)
			{
				const int32 VertexIndex = Y * (Length_X + 1) + X;
				Index.Add(VertexIndex);

				// Create triangles
				Triangles.Add(VertexIndex);
				Triangles.Add(VertexIndex + 1);
				Triangles.Add(VertexIndex + Length_X + 1);

				Triangles.Add(VertexIndex + Length_X + 1);
				Triangles.Add(VertexIndex + 1);
				Triangles.Add(VertexIndex + Length_X + 2);
				
			}
		}
	}

	// Calculate normals (assuming flat grid)
	for (int32 i = 0; i < Vertices.Num(); ++i)
	{
		Normals.Add(FVector(0.0f, 0.0f, -1.0f));
	}

	int Count =0;
	for (const TPair<FVector2D, FVector>& Pair : MainContainer)
	{
		const FVector2D& Key = Pair.Key;
		FVector Value = Pair.Value;

		if(Key.X < Length_X && Key.Y < Length_Y)
		{
			TArray<int32>CTriangles;
			// Create triangles
			CTriangles.Add(Count);
			CTriangles.Add(Count + 1);
			CTriangles.Add(Count + Length_X + 1);

			CTriangles.Add(Count + Length_X + 1);
			CTriangles.Add(Count + 1);
			CTriangles.Add(Count + Length_X + 2);
		
			UProceduralMeshComponent* PMesh = NewObject<UProceduralMeshComponent>(this);
			PMesh->CreateMeshSection(0, Vertices, CTriangles, Normals, UVs, TArray<FColor>(), TArray<FProcMeshTangent>(), false);
			PMesh->RegisterComponent();
			AllTiles.Add(PMesh);
			Count++ ;
			
		}
	

	}

	for	( int i = 0 ; i < AllTiles.Num(); i++)
	{
		// Create a dynamic material instance for each tile
		UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(MaterialTemplate, this);
		// Set the desired color for the tile
		FLinearColor ColorParameter = FLinearColor::MakeRandomColor();
		DynMaterial->SetVectorParameterValue("Base Color", ColorParameter);

		AllTiles[i]->SetMaterial(0, DynMaterial);
		
	}
	
	return true;
}

void ABaseGridActor::DrawPositionIndicator()
{

	UWorld* World = GetWorld();  // Get a reference to the current world

	/*for (FVector Ver : Vertices)
	{
		FVector Location = Ver;
		//DrawDebugSphere(World,Location,50,20,FColor::Red,true,-1);
		DrawDebugPoint(World,Location,20,FColor::Green,true,-1,0);//depth priority of 0 means always visible
		DrawDebugString(GetWorld(), Location, *FString::Printf(TEXT("Position: %d,%d"),Ver.Y, Ver.X), nullptr, FColor::Red, -1.0F, false);
		//bDrawn =true;
	}*/

	
	for (const TPair<FVector2D, FVector>& Pair : MainContainer)
	{
		const FVector2D& Key = Pair.Key;
		FVector Value = Pair.Value;
		FVector Location = Value;
		//DrawDebugSphere(World,Location,50,20,FColor::Red,true,-1);
		DrawDebugPoint(World,Location,20,FColor::Green,true,-1,0);//depth priority of 0 means always visible
		DrawDebugString(GetWorld(), Location, *FString::Printf(TEXT("Position: %d,%d"),Key.X, Key.Y), nullptr, FColor::Red, -1.0F, false);
		//bDrawn =true;
	}
	
}

