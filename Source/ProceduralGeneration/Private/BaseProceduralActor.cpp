// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseProceduralActor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProceduralGeneration/Public/CoreDebugContainer.h"
#include "Containers/Array.h"




//	SET COLLPSE STATUS IN THE FTILE STRUCT
void FTile::SetCollapseStatus(EcollapseStatus CollapseStatuss)
{
	CollapseStatus =CollapseStatuss;
}




// CONSTRUCTOR
ABaseProceduralActor::ABaseProceduralActor()
{
	
	// TURNING OFF TICK
	PrimaryActorTick.bCanEverTick = false;
	
	// CREATING  INSTANCE MESH FOR BASE FLOOR 
	FlorInstanceMesh= CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TileMesh"));

	// SETTING THE ALL TILE FLOAT COUNTER TO 0
	AllTiles_Float = 0 ;
	
}


//BEGIN PLAY
void ABaseProceduralActor::BeginPlay()
{
	Super::BeginPlay();
	
	// SETTING UP INSTANCED MESH COMPONENT FOR FLOOR ACTOR AND ALL THE TILEMESH
	CreteInstanceMeshObjectForTotalTileMesh(TotalTileMesh);
	FlorInstanceMesh->SetStaticMesh(StaticMesh);

	//FOR DEBUG CONTAINER ACTOR
	DebugContainerAcotr = GetWorld()->SpawnActor<ACoreDebugContainer>(FVector::ZeroVector, FRotator::ZeroRotator);

	//GENERATING TILE
	CalculateMeshLength();
	GenerateTile();
	SetDefaultMeshForAllTiles(AllTiles,TotalTileMesh);
	GenerateBaseFloor(AllTiles);
	
	if ( !AllTiles.IsEmpty()  && !TotalTileMesh.IsEmpty() )
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT(" BOTH TILE AND TOTAL MESH AVAILABLE WAVE FUNCTION CALLING  "));}

		//STARTING THE MAIN ALGORITHM
		//WaveFunctionCollapse();
	}
}

// THE MAIN ALGORITHM
void ABaseProceduralActor::WaveFunctionCollapse()
{

		//Adding RemainingTile To All Tile
		RemainingTiles.Reserve(AllTiles.Num());
		for(FTile& Tile : AllTiles)
			{
				RemainingTiles.Add(Tile)  ;
			}
		
	
		// FIRST RANDOM ID FROM STREAM
		int FirstTileID =  UKismetMathLibrary::RandomIntegerFromStream(Map_Height*Map_Width-1,Stream);
		
		//Pick A Random Tile	//For the first time choose from stream
		FTile FirstRandomTile = RemainingTiles[FirstTileID];

		
		//SET SELECTED FTILEMES
		FirstRandomTile.SelectedTiledMesh =RandomMeshFromAvailableMesh(FirstRandomTile);
		
		// ADDING INSTANCE OF THE SELECTED MESH
		AddInstanceMesh(FirstRandomTile);

		// Remove From Remaining Tile
		
		RemainingTiles.RemoveAt(FirstRandomTile.ID-1);
		CollapsedTiles.Add(FirstRandomTile);

		//UPDATE THE SURROUNDING TILES AVAILABLEMESH

		UpdateAvailableMesh_Left(FirstRandomTile);
		UpdateAvailableMesh_Right(FirstRandomTile);
		UpdateAvailableMesh_Up(FirstRandomTile);
		UpdateAvailableMesh_Down(FirstRandomTile);
/*
		while (RemainingTiles.Num()>0)
		{
			// CHOOSE A TILE DEPENDING ENTROPY OF THE TILE 
			FTile Tile = ReturnMeshWithLowEntropy(RemainingTiles);

			// REMOVE FROM REMAINING TILE
			RemainingTiles.RemoveAt(Tile.ID-1);

			// CHOOSE A RANOM MESH FROM AVAILABLE
			Tile.SelectedTiledMesh = RandomMeshFromAvailableMesh(Tile);
			// ADD A INSTANCE TO THE MESH
			AddInstanceMesh(Tile);

			//UPDATING SURROUNDINGS
			UpdateSurroundingMesh(Tile);

			

			
		
		}*/
}

// THIS FUNCTION CREATE THE INSTANCED MESH OBJET FOR ALL THE TILEMESH
void ABaseProceduralActor::CreteInstanceMeshObjectForTotalTileMesh(TArray<FTileMesh> TotalTileMeshes)
{
	for(FTileMesh &tileMesh : TotalTileMeshes)
	{
		tileMesh.InstancedMesh = NewObject<UInstancedStaticMeshComponent>(this);
		tileMesh.InstancedMesh->SetStaticMesh(tileMesh.TileMesh);
	}
}

// CALCULATE LENGTH OF THE  FLOOR MESH 
void ABaseProceduralActor::CalculateMeshLength()
{
	if(StaticMesh ==nullptr)
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("  Tile Size Calculation Failed"));}
		return;
	}
	FVector Center ;
	FVector Extent;
	StaticMesh->GetBoundingBox().GetCenterAndExtents(Center,Extent);
	Actor_Length_X = (Extent.X-Center.X)*2;
	Actor_Length_Y = (Extent.Y-Center.Y)*2;
	Actor_Length_Z = (Extent.Z-Center.Z)*2;
}

//THIS FUNCTION GENERATES TILES 
bool ABaseProceduralActor::GenerateTile()
{
	bool GenerationDone= false;
	for (int i = 0 ; i< Map_Height ; i++)
	{
		for (int j = 0 ; j< Map_Width ; j++)
		{
			
			int id;
			id=(i*10)+j+1;
			FTile Tile ;
			Tile.ID = id ;
			AllTiles_Float ++ ;
			Tile.Position_2D.Width=j+1;
			Tile.Position_2D.Length=i+1;
			Tile.World_Location = FVector (i*Actor_Length_X , j*Actor_Length_Y,0.0f);
			AllTiles.Add(Tile);
		}
	}
	GenerationDone=true;
	return GenerationDone;
}

// THIS FUNCTION CHOOSE RANDOM TILE FROM GIVEN ARRAY
FTile ABaseProceduralActor::ChooseRandomTile(TArray<FTile> AllTileToChooseFrom)
{
	
	int RandomTile = FMath::RandRange(0,AllTileToChooseFrom.Num() );
	return AllTiles[RandomTile];
}

//ADD STATIC MESH INSTANCE
void ABaseProceduralActor::AddInstanceMesh(FTile SelectedTile)
{
	FTileMesh SelectedTileMesh = SelectedTile.SelectedTiledMesh;
	UInstancedStaticMeshComponent*Comp = SelectedTileMesh.InstancedMesh;
	if(SelectedTileMesh.TileMesh)
	{
		FTransform SpawnTransform ;
		SpawnTransform.SetLocation(SelectedTile.World_Location);
		Comp->AddInstance(SpawnTransform);
	}
}

void ABaseProceduralActor::GenerateBaseFloor(TArray<FTile> TotalTies)
{
	if(!bWantBaseFloor)
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("  want base floor : false "));}
		return;
	}
	if(TotalTies.IsEmpty())
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("  TotalTile Empty Base Floor Generation Aborted "));}
		return;
	}
	if(FlorInstanceMesh)
	{
		for(FTile Tile : TotalTies)
		{
			FTransform Transform ;
			Transform.SetLocation(Tile.World_Location);
			FlorInstanceMesh->AddInstance(Transform);
		}
	}
}

void ABaseProceduralActor::SetDefaultMeshForAllTiles(TArray<FTile> TotalTiles ,TArray<FTileMesh> TotalMesh )
{
	if(TotalTiles.IsEmpty())
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT(" ALLTiles Array is Empty !!! Set Default Mesh Failed  "));}
		return;
	}
	if(TotalMesh.IsEmpty())
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT(" Total Mesh Array is Empty !!! Set Default Mesh Failed  "));}
	}
	
	for(FTile Tiles : TotalTiles)
	{
		Tiles.AllAvailableMeshToChooseFrom.Reserve(TotalMesh.Num());
		for ( FTileMesh& MeshElement : TotalTileMesh)
		{
			Tiles.AllAvailableMeshToChooseFrom.Add(MeshElement);
		}
	}
}

// THIS FUNCTION UPDATE SURROUNDING MAINLY CALL THOSE 4 FUNCTION
void ABaseProceduralActor::UpdateSurroundingMesh(FTile SelectedTile)
{
	UpdateAvailableMesh_Left(SelectedTile);
	UpdateAvailableMesh_Right(SelectedTile);
	UpdateAvailableMesh_Up(SelectedTile);
	UpdateAvailableMesh_Down(SelectedTile);
}

// UPDATE LEFT SIDE OF THE SELECTED MESH
void ABaseProceduralActor::UpdateAvailableMesh_Left(FTile SelectedTile)
{
	
	
	if(SelectedTile.ID-10 <0 )
	{
		return;
	}
	FTile LeftNeighbour  = AllTiles[SelectedTile.ID-10];
	TArray<FTileMesh> UpdatedAvailableTileMesh;
	TArray<FTileMesh> AvailableMesh = LeftNeighbour.AllAvailableMeshToChooseFrom ;

	if( LeftNeighbour.CollapseStatus==EcollapseStatus::Collapsed)
	{
		return;
	}
	

	for (FTileMesh AvailableTileMesh_Left : LeftNeighbour.AllAvailableMeshToChooseFrom )
	{
		if(AvailableTileMesh_Left.ComaptileMeshTag_Right.HasTag(SelectedTile.SelectedTiledMesh.MeshTag))
			UpdatedAvailableTileMesh.Add(AvailableTileMesh_Left);
	}
	AllTiles[SelectedTile.ID-10].AllAvailableMeshToChooseFrom =UpdatedAvailableTileMesh;
	
}

// UPDATE RIGHT SIDE OF THE SELECTED MESH
void ABaseProceduralActor::UpdateAvailableMesh_Right(FTile SelectedTile)
{
	FTile RightNeighbour  = AllTiles[SelectedTile.ID+10];
	TArray<FTileMesh> UpdatedAvailableTileMesh;
	TArray<FTileMesh> AvailableMesh = RightNeighbour.AllAvailableMeshToChooseFrom ;
	if(SelectedTile.ID+10 > AllTiles_Float  ||  RightNeighbour.CollapseStatus==EcollapseStatus::Collapsed)
	{
		return;
	}

	for (FTileMesh AvailableTileMesh_Right : RightNeighbour.AllAvailableMeshToChooseFrom )
	{
		if(AvailableTileMesh_Right.ComaptileMeshTag_Left.HasTag(SelectedTile.SelectedTiledMesh.MeshTag))
			UpdatedAvailableTileMesh.Add(AvailableTileMesh_Right);
	}
	AllTiles[SelectedTile.ID+10].AllAvailableMeshToChooseFrom =UpdatedAvailableTileMesh;
}

// UPDATE UP SIDE OF SELECTED MESH
void ABaseProceduralActor::UpdateAvailableMesh_Up(FTile SelectedTile)
{
	FTile UpNeighbour  = AllTiles[SelectedTile.ID+1];
	TArray<FTileMesh> UpdatedAvailableTileMesh;
	TArray<FTileMesh> AvailableMesh = UpNeighbour.AllAvailableMeshToChooseFrom ;
	
	if(SelectedTile.ID+1 > AllTiles_Float  ||  UpNeighbour.CollapseStatus==EcollapseStatus::Collapsed)
	{
		return;
	}

	for (FTileMesh AvailableTileMesh_Up : UpNeighbour.AllAvailableMeshToChooseFrom )
	{
		if(AvailableTileMesh_Up.ComaptileMeshTag_Down.HasTag(SelectedTile.SelectedTiledMesh.MeshTag))
			UpdatedAvailableTileMesh.Add(AvailableTileMesh_Up);
	}
	AllTiles[SelectedTile.ID+1].AllAvailableMeshToChooseFrom =UpdatedAvailableTileMesh;
}

// UPDATE DOWN SIDE OF SELECTED MESH 
void ABaseProceduralActor::UpdateAvailableMesh_Down(FTile SelectedTile)
{
	{
		FTile DownNeighbour  = AllTiles[SelectedTile.ID-1];
		TArray<FTileMesh> UpdatedAvailableTileMesh;
		TArray<FTileMesh> AvailableMesh = DownNeighbour.AllAvailableMeshToChooseFrom ;
	
		if(SelectedTile.ID+1 <= 0  ||  DownNeighbour.CollapseStatus==EcollapseStatus::Collapsed)
		{
			return;
		}
		for (FTileMesh AvailableTileMesh_Down : DownNeighbour.AllAvailableMeshToChooseFrom )
		{
			if(AvailableTileMesh_Down.ComaptileMeshTag_Up.HasTag(SelectedTile.SelectedTiledMesh.MeshTag))
				UpdatedAvailableTileMesh.Add(AvailableTileMesh_Down);
		}
		AllTiles[SelectedTile.ID-1].AllAvailableMeshToChooseFrom =UpdatedAvailableTileMesh;
	}
}

// RETURNS TILE WITH LOWEST ENTROPY 
FTile ABaseProceduralActor::ReturnMeshWithLowEntropy(TArray<FTile> TotalTile)
{
	int LowestNumberOfTile =999;
	FTile TileWithLowEntropy;
	for(FTile Tile : TotalTile )
	{
		if(Tile.AllAvailableMeshToChooseFrom.Num()<LowestNumberOfTile )
		{

			LowestNumberOfTile=Tile.AllAvailableMeshToChooseFrom.Num();
			TileWithLowEntropy =Tile;
		}
	}
	return TileWithLowEntropy;
}


// CHOOSE AN RAND0M ARRAY FROM GIVEN ARRAY OF FTILEMESH BASED ON ENTROPY
FTileMesh ABaseProceduralActor::RandomMeshFromAvailableMesh(FTile Tile)
{
	//if(Tile.AllAvailableMeshToChooseFrom.Num() == 0)
	if(Tile.AllAvailableMeshToChooseFrom.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("No Mesh found!"));
		return FTileMesh();
	}
	
	int RandomMESH = FMath::RandRange(0,Tile.AllAvailableMeshToChooseFrom.Num()-1 );
	return Tile.AllAvailableMeshToChooseFrom[RandomMESH];
}






