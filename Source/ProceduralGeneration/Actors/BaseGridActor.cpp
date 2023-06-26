// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGridActor.h"

#include "ProceduralMeshComponent.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "ProceduralGeneration/Player/TopDownPlayerController.h"
#include "ProceduralGeneration/Tiles/TileData.h"


struct FProcMeshTangent;
// Sets default values
ABaseGridActor::ABaseGridActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GridMesh=CreateDefaultSubobject<UProceduralMeshComponent>("Grid Procedural Mesh");
	SetRootComponent(GridMesh);
	GridMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GridMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	//GridMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//GridMesh->SetVisibility(true);
	




	
	GridSize= FVector(4.0f,4.0f,0.0f);
	CellSize =FVector (1000.0f,1000.0f,1000.0f);
	GridCenter = FVector(0.0f,0.0f,0.0f);
	MaterialEmission=FVector(0.f,0.f,0.f);
	MaterialOpacity=FVector(0.5f,0.5f,0.5f);
}

// Called when the game starts or when spawned
void ABaseGridActor::BeginPlay()
{
	Super::BeginPlay();
	ADelegateHelper::OnMouseMovementDelegate.AddDynamic(this,&ABaseGridActor::Receiver_OnMouseMove);
	TopDownController = Cast<ATopDownPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	
	GenerateGridMesh();
	DrawPositionIndicator();
	
}

// Called every frame
void ABaseGridActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if(TopDownController)
	//PrintDotProduct(TopDownController);
	
}

void ABaseGridActor::Receiver_OnMouseMove(FVector HitLoc)
{
	for (const TPair<FVector2D, UTileData*>& Pair : TileMap)
	{
		const FVector2D& Key = Pair.Key;
		UTileData* Tile = Pair.Value;
		
		FBox BoxBounds = Tile->BoundingBox;
		bool IsWithinBounds = BoxBounds.IsInside(HitLoc);
		
		UMaterialInstanceDynamic* DynMaterial = MaterialContainer[Key];
		if(IsWithinBounds)
		{
			CursorHitTile = Tile;
			TopDownController->HitTile=CursorHitTile;
			FVector OPCT =FVector (1.0f,1.0f,1.0f);
			DynMaterial->SetVectorParameterValue("Opacity",OPCT);
		}
		else
		{
			DynMaterial->SetVectorParameterValue("Opacity",MaterialOpacity);
		}
			
	}
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

void ABaseGridActor::PrintDotProduct(ATopDownPlayerController* TDController)
{
	
	for (const TPair<FVector2D, UTileData*>& Pair : TileMap)
	{
		const FVector2D& Key = Pair.Key;
		UTileData* Tile = Pair.Value;
		float DotP =FVector::DotProduct(Tile->Normal,TopDownController->CursorWorldDirection);
		DrawDebugString(GetWorld(), Tile->CenterPoint, *FString::Printf(TEXT("Dot: %f"),DotP), nullptr, FColor::Red, -1.0F, false,1);
	}
}
void ABaseGridActor::TileHoverEffect()
{
	
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
	const float HalfWidth = GridSize.Y * CellSize.Y * 0.5f;
	const float HalfHeight = GridSize.X * CellSize.X * 0.5f;

	FVector GridOffset = FVector(GridCenter.X-HalfHeight,GridCenter.Y-HalfWidth,GridCenter.Z);

	for (int32 Y = 0; Y <= GridSize.Y; Y++)
	{
		for (int32 X = 0; X <= GridSize.X; X++)
		{
			const FVector VertexLocation = FVector(X * CellSize.X + GridOffset.X, Y
				* CellSize.Y + GridOffset.Y, GridOffset.Z);

			// Add vertex
			Vertices.Add(VertexLocation);
			FVector2D Loc2d = FVector2D (X,Y);
			MainContainer.Add(Loc2d, VertexLocation);

			// Add UVs
			const FVector2D UV((float)X / (GridSize.X+1), (float)Y / (GridSize.Y+1));
			UVs.Add(UV);

			// Skip the last row and column as they won't form triangles
			if (X < GridSize.X && Y < GridSize.Y)
			{
				const int32 VertIndex = Y * (GridSize.X + 1) + X;
				VertexIndex.Add(VertIndex);
				UTileData* Tile = NewObject<UTileData>() ;
				//Tile->Init(Loc2d,VertexLocation,VertexIndex,&Vertices,Length_X,Length_Y);
				
				Tile->Const(Loc2d,VertexLocation,VertIndex,GridSize,CellSize);
				TileMap.Add(Loc2d, Tile);
			}
			
		}
	}

	// Calculate normals (assuming flat grid)
	for (int32 i = 0; i < Vertices.Num(); ++i)
	{
		Normals.Add(FVector(0.0f, 0.0f, 1.0f));
	}

	//int Count =1;
for (int32 i =0 ; i<VertexIndex.Num() ; i++)
	{
		int Count = VertexIndex[i];
		TArray<int32>CTriangles;
		TArray<FVector>CollisionShape;
	
		int32 A =Count;
		int32 B =Count + GridSize.X + 1;
		int32 C =Count + GridSize.X + 2;
		int32 D =Count + 1;
		// Create triangles
		CTriangles.Add(A);
		CTriangles.Add(B);
		CTriangles.Add(C);

		CTriangles.Add(C);
		CTriangles.Add(D);
		CTriangles.Add(A);
		CollisionShape.Add(Vertices[A]);
		CollisionShape.Add(Vertices[B]);
		CollisionShape.Add(Vertices[C]);
		CollisionShape.Add(Vertices[D]);
	
		GridMesh->CreateMeshSection(VertexIndex[i], Vertices, CTriangles, Normals, UVs, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
	
		AllCollisionShape.Add(CollisionShape);
		GridMesh->SetCollisionConvexMeshes(AllCollisionShape);


		FProcMeshSection MeshSection;

	}
	
	for(const TPair<FVector2D, UTileData*>& Pair : TileMap)
	{
		FVector2D Key = Pair.Key;
		UTileData*Tile = Pair.Value;
		Tile->Init(&Vertices);

		UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(MaterialTemplate, this);
		// Set the desired color for the tile
		FLinearColor ColorParameter = FLinearColor::MakeRandomColor();
		//ColorParameter.A =0.1;
		DynMaterial->SetVectorParameterValue("Base_Color", ColorParameter);
		FVector OPCT =MaterialOpacity;
		FVector EMSV =MaterialEmission;
		DynMaterial->SetVectorParameterValue("Opacity", OPCT);
		DynMaterial->SetVectorParameterValue("Emissive_Color", EMSV);
		GridMesh->SetMaterial(Tile->Index,DynMaterial);
		MaterialContainer.Add(Key,DynMaterial);
		
		// Calculate the center point of the square tile
		FVector Center = Tile->CenterPoint;

		// Calculate the normal vector using two sides of the square tile
		FVector Normal = Tile->Normal;

		// Set the length of the debug line for the normal vector
		float LineLength = 100.0f;

		// Calculate the endpoint of the normal line
		FVector LineEndpoint = Center + (Normal * LineLength);

		// Draw the debug line
		DrawDebugLine(GetWorld(), Center, LineEndpoint, FColor::Green, true, -1, 0, 1.0f);
		DrawDebugBox(GetWorld(), Tile->BoundingBox.GetCenter(),Tile->BoundingBox.GetExtent(),FColor::Green,true,-1.0f );
	}
	GridMesh->SetCollisionConvexMeshes(AllCollisionShape);
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
		DrawDebugPoint(World,Location,10,FColor::Green,true,-1,0);//depth priority of 0 means always visible
		DrawDebugString(GetWorld(), Location, *FString::Printf(TEXT(" %f,%f"),Value.X, Value.Y), nullptr, FColor::Red, -1.0F, false);
		//bDrawn =true;
	}
	/*for (const TPair<FVector2D, UTileData*>& Pair : TileMap)
	{
		const FVector2D& Key = Pair.Key;
		UTileData* Tile = Pair.Value;
		FVector Location = Tile->LocationWorld;
		//DrawDebugSphere(World,Location,50,20,FColor::Red,true,-1);
		DrawDebugPoint(World,Location,20,FColor::Green,true,-1,0);//depth priority of 0 means always visible
		DrawDebugString(GetWorld(), Location, *FString::Printf(TEXT("Position: %f,%f"),Tile->LocationWorld.X, Tile->LocationWorld.Y), nullptr, FColor::Red, -1.0F, false);
		//bDrawn =true;
		//PrintDotProduct(TopDownController);

		
		
	}*/
	
}


