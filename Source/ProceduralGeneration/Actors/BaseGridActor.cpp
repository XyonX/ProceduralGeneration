// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGridActor.h"

#include "ProceduralMeshComponent.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "ProceduralGeneration/Tiles/TileData.h"


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
	GridCenter = FVector(0.0f,0.0f,0.0f);
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

void ABaseGridActor::OnMouseMove(const FVector2D& MousePosition)
{
	APlayerController*PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	// Convert mouse position to local coordinates relative to the grid
        FVector WorldPosition;
        FVector WorldDirection;
        UGameplayStatics::DeprojectScreenToWorld(PlayerController, MousePosition, WorldPosition, WorldDirection);
		CursorWorldPosition=WorldPosition;
		CursorWorldDirection = WorldDirection;

		UStaticMesh* StaticMesh = TestCube; // Assuming TestCube is a UStaticMesh reference or pointer
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding; // Set the collision handling method according to your needs

		AStaticMeshActor* SpawnedActor = GetWorld()->SpawnActor<AStaticMeshActor>(WorldPosition + (WorldDirection * 100), WorldDirection.Rotation(), SpawnParams);
	if (SpawnedActor)
	{
		UStaticMeshComponent* StaticMeshComponent = SpawnedActor->GetStaticMeshComponent();
		if (StaticMeshComponent)
		{
			StaticMeshComponent->SetStaticMesh(StaticMesh);
		}
	}
    
        FVector LocalPosition = GetTransform().InverseTransformPosition(WorldPosition);
}

TArray<FVector*> ABaseGridActor::GetVerticesByTilePos(FVector2D TilePos)
{
	TArray<FVector*> Verts ;
	FVector* VertLoc = MainContainer.Find(TilePos);
	
	if (VertLoc)
	{
		Verts.Add(VertLoc);
	}
	
	FVector2D Pos =FVector2D(TilePos.X+1,TilePos.Y);
	VertLoc = MainContainer.Find(Pos);
	if (VertLoc)
	{
		Verts.Add(VertLoc);
	}
	
	Pos =FVector2D(TilePos.X,TilePos.Y+1);
	VertLoc = MainContainer.Find(Pos);
	if (VertLoc)
	{
		Verts.Add(VertLoc);
	}

	Pos =FVector2D(TilePos.X+1,TilePos.Y+1);
	VertLoc = MainContainer.Find(Pos);
	if (VertLoc)
	{
		Verts.Add(VertLoc);
	}
	
	return Verts;
	
}

bool ABaseGridActor::GenerateGridMesh()
{
	// Calculate the grid size
	const float HalfWidth = Length_Y * CellSize * 0.5f;
	const float HalfHeight = Length_X * CellSize * 0.5f;

	FVector GridOffset = FVector(GridCenter.X-HalfHeight,GridCenter.Y-HalfWidth,GridCenter.Z);
	
	UWorld* World = GetWorld();

	for (int32 Y = 0; Y <= Length_Y; Y++)
	{
		for (int32 X = 0; X <= Length_X; X++)
		{
			const FVector VertexLocation = FVector(X * CellSize + GridOffset.X, Y * CellSize + GridOffset.Y, GridOffset.Z);

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
				UTileData* Tile = NewObject<UTileData>() ;
				//Tile->Init(Loc2d,VertexLocation,VertexIndex,&Vertices,Length_X,Length_Y);
				Tile->Const(Loc2d,VertexLocation,VertexIndex,Length_X,Length_Y);
				TileMap.Add(Loc2d, Tile);
			}
			
		}
	}

	// Calculate normals (assuming flat grid)
	for (int32 i = 0; i < Vertices.Num(); ++i)
	{
		Normals.Add(FVector(0.0f, 0.0f, -1.0f));
	}

	//int Count =1;
for (int i =0 ; i<Index.Num() ; i++)
	{
		int Count = Index[i];
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
	}


	for	( int i = 0 ; i < AllTiles.Num(); i++)
	{
		// Create a dynamic material instance for each tile
		UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(MaterialTemplate, this);
		// Set the desired color for the tile
		FLinearColor ColorParameter = FLinearColor::MakeRandomColor();
		ColorParameter= ColorParameter.CopyWithNewOpacity(0.5f);
		DynMaterial->SetVectorParameterValue("Base Color", ColorParameter);

		AllTiles[i]->SetMaterial(0, DynMaterial);
		
	}
	
	for(const TPair<FVector2D, UTileData*>& Pair : TileMap)
	{
		UTileData*Tile = Pair.Value;
		Tile->Init(&Vertices);
		// Calculate the center point of the square tile
		FVector Center = Tile->CenterPoint;

		// Calculate the normal vector using two sides of the square tile
		FVector Normal = Tile->Normal;

		// Set the length of the debug line for the normal vector
		float LineLength = 100.0f;

		// Calculate the endpoint of the normal line
		FVector LineEndpoint = Center + Normal * LineLength;

		// Draw the debug line
		DrawDebugLine(GetWorld(), Center, LineEndpoint, FColor::Green, true, -1, 0, 1.0f);
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
		DrawDebugString(GetWorld(), Location, *FString::Printf(TEXT("Position: %f,%f"),Value.X, Value.Y), nullptr, FColor::Red, -1.0F, false);
		//bDrawn =true;
	}
	
}

void ABaseGridActor::DrawNormal()
{
}

