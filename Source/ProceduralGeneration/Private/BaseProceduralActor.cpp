// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProceduralActor.h"

#include "Components/InstancedStaticMeshComponent.h"


// Sets default values
ABaseProceduralActor::ABaseProceduralActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InstancedMesh= CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TileMesh"));
	
}

// Called when the game starts or when spawned
void ABaseProceduralActor::BeginPlay()
{
	Super::BeginPlay();
	InstancedMesh->SetStaticMesh(StaticMesh);
	CalculateMeshLength();
	GenerateTile();
	
	
}

// Called every frame
void ABaseProceduralActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ABaseProceduralActor::GenerateTile()
{
	
	for (int i = 0 ; i<= Map_Length ; i++)
	{
		for (int j = 0 ; j<= Map_Width ; j++)
		{
			int id =(i*9)+j+1 ;
			FTile Tile ;
			Tile.ID = id ;
			Tile.Position_2D.Width=j+1;
			Tile.Position_2D.Length=i+1;
			if(bWantCustomTileSize)
			{
				Tile.World_Location = FVector (i*Actor_Length , j*Actor_Length,0.0f);
			}
			Tile.World_Location = FVector (i*Actor_Length_X , j*Actor_Length_Y,0.0f);
			
			AllTiles.Add(Tile);
			if(bwantToSpawnTiles)
			{
				if(InstancedMesh)
				{
					FTransform SpawnTransform ;
					SpawnTransform.SetLocation(Tile.World_Location);
					InstancedMesh->AddInstance(SpawnTransform,true);
				}
				
			}
		}
	}
}

void ABaseProceduralActor::CalculateMeshLength()
{
	//FBox BoundingBox  ;
	//AActor*Ac ;
	//Ac->GetActorBounds()
	//Actor_Length = BoundingBox.
	FVector Center ;
	FVector Extent;
	StaticMesh->GetBoundingBox().GetCenterAndExtents(Center,Extent);
	Actor_Length_X = (Extent.X-Center.X)*2;
	Actor_Length_Y = (Extent.Y-Center.Y)*2;
}

