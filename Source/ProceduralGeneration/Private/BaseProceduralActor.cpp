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
		WaveFunctionCollapse();
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
		Stream.GenerateNewSeed();
		int FirstTileID =  UKismetMathLibrary::RandomIntegerFromStream(RemainingTiles.Num()-1,Stream);
		
		//Pick A Random Tile	//For the first time choose from stream
		FTile& FirstRandomTile = RemainingTiles[FirstTileID];
		
		// ADDING INSTANCE OF THE SELECTED MESH
		AddInstanceMesh(FirstTileID+1,AllTiles);
		//Update  Collapsed Tile Data
		UpdateCollapsedTileData(FirstRandomTile.ID,FirstTileID,AllTiles,RemainingTiles,CollapsedTiles);

		//UPDATE THE SURROUNDING TILES AVAILABLEMESH

		UpdateAvailableMesh_Left(FirstRandomTile,AllTiles);
		UpdateAvailableMesh_Right(FirstRandomTile,AllTiles);
		UpdateAvailableMesh_Up(FirstRandomTile,AllTiles);
		UpdateAvailableMesh_Down(FirstRandomTile,AllTiles);

	/*	while (RemainingTiles.Num()>0)
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
void ABaseProceduralActor::CreteInstanceMeshObjectForTotalTileMesh(TArray<FTileMesh>& TotalTileMeshes)
{
	for(FTileMesh &tileMesh : TotalTileMeshes)
	{
		tileMesh.InstancedMesh = NewObject<UInstancedStaticMeshComponent>(this);
		tileMesh.InstancedMesh->SetStaticMesh(tileMesh.TileMesh);
	}
}

void ABaseProceduralActor::UpdateCollapsedTileData(int ID ,int ArrayPosition , TArray<FTile>& TotalTile ,TArray<FTile>& RemainingTile, TArray<FTile>& TotalCollapsedTile)
{
	//Update Collapse Status in the main tile

	FTile&CollapsedTile = TotalTile[ID];
	CollapsedTile.CollapseStatus=EcollapseStatus::Collapsed;

	//Remove From Remaining Title
	RemainingTiles.RemoveAt(ArrayPosition);

	// Add th the collapsed tile
	TotalCollapsedTile.Add(CollapsedTile);
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
	int id=0;
	for (int i = 0 ; i< Map_Height ; i++)
	{
		for (int j = 0 ; j< Map_Width ; j++)
		{
			
			
			
			FTile Tile ;
			id++;
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



void ABaseProceduralActor::GenerateBaseFloor(TArray<FTile> TotalTies)
{
	if(!bWantBaseFloor)
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("  want base floor : false "));}
		return;
	}
	if(TotalTies.IsEmpty())
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("  TotalTile Empty Base Floor Generation Aborted "));}
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

void ABaseProceduralActor::SetDefaultMeshForAllTiles(TArray<FTile> &TotalTiles ,TArray<FTileMesh>& TotalMesh )
{
	if(TotalTiles.IsEmpty())
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" ALLTiles Array is Empty !!! Set Default Mesh Failed  "));}
		return;
	}
	if(TotalMesh.IsEmpty())
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Total Mesh Array is Empty !!! Set Default Mesh Failed  "));}
	}
	
	for(FTile &Tiles : TotalTiles)
	{
		Tiles.AllAvailableMeshToChooseFrom.Reserve(TotalMesh.Num());
		for ( FTileMesh& MeshElement : TotalTileMesh)
		{
			Tiles.AllAvailableMeshToChooseFrom.Add(MeshElement);
		}
	}
}

// THIS FUNCTION UPDATE SURROUNDING MAINLY CALL THOSE 4 FUNCTION
void ABaseProceduralActor::UpdateSurroundingMesh(FTile& SelectedTile , TArray<FTile>&TotalTile)
{
	UpdateAvailableMesh_Left(SelectedTile ,TotalTile);
	UpdateAvailableMesh_Right(SelectedTile,TotalTile);
	UpdateAvailableMesh_Up(SelectedTile,TotalTile);
	UpdateAvailableMesh_Down(SelectedTile,TotalTile);
}

// UPDATE LEFT SIDE OF THE SELECTED MESH
void ABaseProceduralActor::UpdateAvailableMesh_Left(FTile& SelectedTile , TArray<FTile>&TotalTile)
{
	
	
	if(SelectedTile.ID-10 <0 )
	{
		return;
	}
	FTile& LeftNeighbour  = AllTiles[SelectedTile.ID-10];
	TArray<FTileMesh> UpdatedAvailableTileMesh;
	TArray<FTileMesh>& AvailableMesh = LeftNeighbour.AllAvailableMeshToChooseFrom ;

	if( LeftNeighbour.CollapseStatus==EcollapseStatus::Collapsed)
	{
		return;
	}
	

	for (FTileMesh& AvailableTileMesh_Left : AvailableMesh )
	{
		if(AvailableTileMesh_Left.ComaptileMeshTag_Right.HasTag(SelectedTile.SelectedTiledMesh.MeshTag))
			UpdatedAvailableTileMesh.Add(AvailableTileMesh_Left);
	}
	AllTiles[SelectedTile.ID-10].AllAvailableMeshToChooseFrom =UpdatedAvailableTileMesh;
	
}

// UPDATE RIGHT SIDE OF THE SELECTED MESH
void ABaseProceduralActor::UpdateAvailableMesh_Right(FTile& SelectedTile , TArray<FTile>&TotalTile)
{
	if(SelectedTile.ID+10 > AllTiles_Float  )
	{
		return;
	}
	FTile& RightNeighbour  = AllTiles[SelectedTile.ID+10];
	TArray<FTileMesh> UpdatedAvailableTileMesh;
	TArray<FTileMesh>& AvailableMesh = RightNeighbour.AllAvailableMeshToChooseFrom ;
	if(RightNeighbour.CollapseStatus==EcollapseStatus::Collapsed)
	{
		return;
	}

	for (FTileMesh& AvailableTileMesh_Right : AvailableMesh )
	{
		if(AvailableTileMesh_Right.ComaptileMeshTag_Left.HasTag(SelectedTile.SelectedTiledMesh.MeshTag))
			UpdatedAvailableTileMesh.Add(AvailableTileMesh_Right);
	}
	AllTiles[SelectedTile.ID+10].AllAvailableMeshToChooseFrom =UpdatedAvailableTileMesh;
}

// UPDATE UP SIDE OF SELECTED MESH
void ABaseProceduralActor::UpdateAvailableMesh_Up(FTile& SelectedTile , TArray<FTile>&TotalTile)
{
	if(SelectedTile.ID+1 > AllTiles_Float )
	{
		return;
	}
	FTile& UpNeighbour  = AllTiles[SelectedTile.ID+1];
	TArray<FTileMesh> UpdatedAvailableTileMesh;
	TArray<FTileMesh> &AvailableMesh = UpNeighbour.AllAvailableMeshToChooseFrom ;
	if(UpNeighbour.CollapseStatus==EcollapseStatus::Collapsed)
	{
		return;
	}
	for (FTileMesh& AvailableTileMesh_Up : AvailableMesh )
	{
		if(AvailableTileMesh_Up.ComaptileMeshTag_Down.HasTag(SelectedTile.SelectedTiledMesh.MeshTag))
			UpdatedAvailableTileMesh.Add(AvailableTileMesh_Up);
	}
	AllTiles[SelectedTile.ID+1].AllAvailableMeshToChooseFrom =UpdatedAvailableTileMesh;
}

// UPDATE DOWN SIDE OF SELECTED MESH 
void ABaseProceduralActor::UpdateAvailableMesh_Down(FTile& SelectedTile , TArray<FTile>&TotalTile)
{
	{
		FTile& DownNeighbour  = AllTiles[SelectedTile.ID-1];
		TArray<FTileMesh> UpdatedAvailableTileMesh;
		TArray<FTileMesh>& AvailableMesh = DownNeighbour.AllAvailableMeshToChooseFrom ;
	
		if(SelectedTile.ID+1 <= 0  ||  DownNeighbour.CollapseStatus==EcollapseStatus::Collapsed)
		{
			return;
		}
		for (FTileMesh AvailableTileMesh_Down : AvailableMesh )
		{
			if(AvailableTileMesh_Down.ComaptileMeshTag_Up.HasTag(SelectedTile.SelectedTiledMesh.MeshTag))
				UpdatedAvailableTileMesh.Add(AvailableTileMesh_Down);
		}
		AllTiles[SelectedTile.ID-1].AllAvailableMeshToChooseFrom =UpdatedAvailableTileMesh;
	}
}

// RETURNS TILE WITH LOWEST ENTROPY 
int ReturnMeshIDWithLowEntropy (TArray<FTile>& TotalTile)
{
	int LowestNumberOfTile =999;
	FTile TileWithLowEntropy;
	for(FTile& Tile : TotalTile )
	{
		if(Tile.AllAvailableMeshToChooseFrom.Num()<LowestNumberOfTile )
		{

			LowestNumberOfTile=Tile.AllAvailableMeshToChooseFrom.Num();
			TileWithLowEntropy =Tile;
		}
	}
	return TileWithLowEntropy.ID;
}


// CHOOSE AN RAND0M ARRAY FROM GIVEN ARRAY OF FTILEMESH BASED ON ENTROPY
FTileMesh& ABaseProceduralActor::RandomMeshFromAvailableMesh(FTile& Tile)
{
	static FTileMesh& DefaultMesh=DefaultTileMesh ;
	//if(Tile.AllAvailableMeshToChooseFrom.Num() == 0)
	if(Tile.AllAvailableMeshToChooseFrom.IsEmpty())
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("   Available mesh list is empty For this tile unable to select any random Mesh "));}
		return DefaultMesh;
	}
	
	int RandomMESH = FMath::RandRange(0,Tile.AllAvailableMeshToChooseFrom.Num()-1 );
	FTileMesh&SelectedTileMesh = Tile.AllAvailableMeshToChooseFrom[RandomMESH];
	return SelectedTileMesh;
}

void ABaseProceduralActor::AddInstanceMesh(int ID, TArray<FTile>& TotalTile)
{
	FTile&SelectedTile = TotalTile[ID-1];
	
	SelectedTile.SelectedTiledMesh = RandomMeshFromAvailableMesh(SelectedTile);
	if(SelectedTile.SelectedTiledMesh.TileMesh ==nullptr  )
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Instance Add Failedd Selected Tile Didint have any Selected  Mesh "));}
		return;
	}
	if(SelectedTile.SelectedTiledMesh.TileMesh != nullptr)
	{
		FTransform SpawnTransform ;
		SpawnTransform.SetLocation(TotalTile[ID-1].World_Location);
		SelectedTile.SelectedTiledMesh.InstancedMesh->AddInstance(SpawnTransform);
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green,  TEXT(" INSTANCE ADING DONE "));}
	}
}






