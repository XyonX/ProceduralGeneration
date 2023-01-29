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



//SET TILE MESH IN THE FTILEMESH STRUCT
void FTileMesh::SetTileMesh(UStaticMesh* InTileMesh)
{
	TileMesh = InTileMesh;
	InstancedMesh->SetStaticMesh(TileMesh);
}


// RETURNS THE MATCHING TILES ARRAY FOR THE FTILEMESH CONTAINS 4 SURROUNDING  MESH
FMatchingTileArray FTileMesh::GetMatchingTiles()
{
	return MatchingTiles;
}


// CONSTRUCTOR
ABaseProceduralActor::ABaseProceduralActor()
{
	
	// TURNING OFF TICK
	PrimaryActorTick.bCanEverTick = false;
	
	// CREATING  INSTANCE MESH FOR BASE FLOOR 
	FlorInstanceMesh= CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TileMesh"));
	FlorInstanceMesh->SetStaticMesh(StaticMesh);

	// CREATING INSTANCE MESH FOR  FTILE MESH

	UInstancedStaticMeshComponent*instmesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("FTILEMESH INSTANCE"));
	
	for(FTileMesh &tileMesh : TotalTileMesh)
	{
		tileMesh.InstancedMesh = instmesh ;
		// set other properties of tileMesh
		if(tileMesh.TileMesh)
		tileMesh.InstancedMesh->SetStaticMesh(tileMesh.TileMesh);
	}

	// SETTING THE ALL TILE FLOAT COUNTER TO 0
	AllTiles_Float = 0 ;
	
}


//BEGIN PLAY
void ABaseProceduralActor::BeginPlay()
{
	Super::BeginPlay();
	// SpawningActor
	DebugContainerAcotr = GetWorld()->SpawnActor<ACoreDebugContainer>(FVector::ZeroVector, FRotator::ZeroRotator);
	
	// CALLING TO GET MESH LENGTH 
	CalculateMeshLength();
	//CALLING TO GENERATE TILE
	GenerateTile();
	//STARTING THE MAIN ALGORITHM
	WaveFunctionCollapse();
	//if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("LENGTH OF ALLTileArray : %f "),AllTiles.Num());}
}

// THE MAIN ALGORITHM
void ABaseProceduralActor::WaveFunctionCollapse()
{
	
	// Generate Tile
	bool GenDone;
	
	GenDone =GenerateTile();
	
	if(GenDone)
	{
		// FIRST RANDOM ID FROM STREAM
		int FirstTileID =  UKismetMathLibrary::RandomIntegerFromStream(Map_Length*Map_Width,Stream);
		
		//Pick A Random Tile	//For the first time choose from stream
		RemainingTiles =AllTiles;
		FTile FirstRandomTile = RemainingTiles[30];

		//SET SELECTED FTILEMES
		FirstRandomTile.SelectedTiledMesh =RandomMeshFromAvailableMesh(FirstRandomTile);
		
		// ADDING INSTANCE OF THE SELECTED MESH
		AddInstanceMesh(FirstRandomTile);

		// Remove From Remaining Tile
		
		RemainingTiles.RemoveAt(FirstRandomTile.ID-1);

		//UPDATE THE SURROUNDING TILES AVAILABLEMESH

		UpdateAvailableMesh_Left(FirstRandomTile);
		UpdateAvailableMesh_Right(FirstRandomTile);
		UpdateAvailableMesh_Up(FirstRandomTile);
		UpdateAvailableMesh_Down(FirstRandomTile);

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

			

			
		
		}
	}
}

// CALCULATE LENGTH OF THE  FLOOR MESH 
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
	Actor_Length_Z = (Extent.Z-Center.Z)*2;
}

//THIS FUNCTION GENERATES TILES 
bool ABaseProceduralActor::GenerateTile()
{
	bool GenerationDone= false;
	for (int i = 0 ; i< Map_Length ; i++)
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
			Tile.AllAvailableMeshToChooseFrom=TotalTileMesh;
			AllTiles.Add(Tile);
			
			if(bWantBaseFloor)
			{
				if(FlorInstanceMesh)
				{
					FTransform SpawnTransform ;
					SpawnTransform.SetLocation(Tile.World_Location);
					FlorInstanceMesh->AddInstance(SpawnTransform,true);
				}
				
			}
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
		for ( UStaticMesh* SuitableMesh_Right : AvailableTileMesh_Left.MatchingTiles.RightTileMesh)
		{
			if(SuitableMesh_Right == SelectedTile.SelectedTiledMesh.TileMesh)
			{
				UpdatedAvailableTileMesh.Add(AvailableTileMesh_Left);
				continue;
			}
		}
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
		for ( UStaticMesh* SuitableMesh_Left : AvailableTileMesh_Right.MatchingTiles.LeftTileMesh)
		{
			if(SuitableMesh_Left == SelectedTile.SelectedTiledMesh.TileMesh)
			{
				UpdatedAvailableTileMesh.Add(AvailableTileMesh_Right);
				continue;
			}
		}
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

	for (FTileMesh AvailableTileMesh_UP : UpNeighbour.AllAvailableMeshToChooseFrom )
	{
		for ( UStaticMesh* SuitableMesh_DownTileMesh : AvailableTileMesh_UP.MatchingTiles.DownTileMesh)
		{
			if(SuitableMesh_DownTileMesh == SelectedTile.SelectedTiledMesh.TileMesh)
			{
				UpdatedAvailableTileMesh.Add(AvailableTileMesh_UP);
				continue;
			}
		}
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
			for ( UStaticMesh* SuitableMesh_UpTileMesh : AvailableTileMesh_Down.MatchingTiles.UpTileMesh)
			{
				if(SuitableMesh_UpTileMesh == SelectedTile.SelectedTiledMesh.TileMesh)
				{
					UpdatedAvailableTileMesh.Add(AvailableTileMesh_Down);
					continue;
				}
			}
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
	if(Tile.AllAvailableMeshToChooseFrom.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Mesh found!"));
		return FTileMesh();
	}
	
	int RandomMESH = FMath::RandRange(0,Tile.AllAvailableMeshToChooseFrom.Num()-1 );
	return Tile.AllAvailableMeshToChooseFrom[RandomMESH];
}


// THIS FUNCTION IS  CURRENTLY NOT IN USE ITS MAINLY  TELLS US  AVAILABLE MESH AFTER  CHECKING SURROUNDINGS
void CheckSelectedTileStatusAndAvilableTileMesh  (TArray<FTile>TotalTile , int TileIndex , EcollapseStatus & CollapseStatus , TArray<FTileMesh  >& CurrentlyAvailableTilemesh)
{

	//  In this approach we are selecting the first tile
	// then checking surrounding lv_1 tile if  they are collapsed then we are updating the choises available for the selected tile
	// if they are not colapsed or some of some of them are collapsed the we arer going to update the available mesh to choose from array
	// if none of then are collapsed then we are goiong to 
	
	FTile SelectedTile = TotalTile [TileIndex];
	
	
	TArray<FTileMesh>AvailableTileMesh = SelectedTile.AllAvailableMeshToChooseFrom ;
	CollapseStatus = SelectedTile .CollapseStatus;


	
	FTile LeftNeighbour_1  = TotalTile[TileIndex-10];
	TArray<FTileMesh> AvailMesh_LeftNeighbour_1 = LeftNeighbour_1.AllAvailableMeshToChooseFrom;
		
	FTile RightNeighbour_1 = TotalTile[TileIndex+10];
	TArray<FTileMesh> AvailMesh_RightNeighbour_1 = RightNeighbour_1.AllAvailableMeshToChooseFrom;
		
	FTile UpNeighbour_1  = TotalTile[TileIndex+1];
	TArray<FTileMesh> AvailMesh_UpNeighbour_1 = UpNeighbour_1.AllAvailableMeshToChooseFrom;
		
	FTile DownNeighbour_1= TotalTile[TileIndex-1] ;
	TArray<FTileMesh> AvailMesh_DownNeighbour_1 = DownNeighbour_1.AllAvailableMeshToChooseFrom;



	TArray<FTileMesh> UpdatedAvailableTileMesh_L;
	// check left tile // if  its collapsed then update the  availablemesh to select 

	if(LeftNeighbour_1.CollapseStatus == EcollapseStatus::NotCollapsed)
	{
		UpdatedAvailableTileMesh_L = AvailableTileMesh ; 
	}
	if(LeftNeighbour_1.CollapseStatus == EcollapseStatus::Collapsed)
	{
		for(FTileMesh TileMesh : AvailableTileMesh)
		{
			for (UStaticMesh* AvailableMeshBecauseofLeftTile : LeftNeighbour_1.SelectedTiledMesh.MatchingTiles.RightTileMesh )
			{
				if(TileMesh.TileMesh ==  AvailableMeshBecauseofLeftTile )
				{
					UpdatedAvailableTileMesh_L.Add(TileMesh);
					break;
				}
			}
			
		}
		
	}

	TArray<FTileMesh> UpdatedAvailableTileMesh_R;
	// CHECKING RIGHT TILE 

	if(RightNeighbour_1.CollapseStatus == EcollapseStatus::NotCollapsed)
	{
		UpdatedAvailableTileMesh_R = UpdatedAvailableTileMesh_L ;
	}
	if(RightNeighbour_1.CollapseStatus == EcollapseStatus::Collapsed)
	{
		for(FTileMesh TileMesh : UpdatedAvailableTileMesh_L)
		{
			for (UStaticMesh* AvailableMeshBecauseofLeftTile : RightNeighbour_1.SelectedTiledMesh.MatchingTiles.LeftTileMesh )
			{
				if(TileMesh.TileMesh ==  AvailableMeshBecauseofLeftTile )
				{
					UpdatedAvailableTileMesh_R.Add(TileMesh);
					break;
				}
			}
			
		}
		
	}


	TArray<FTileMesh> UpdatedAvailableTileMesh_U;
	// checking up tile

	if(RightNeighbour_1.CollapseStatus == EcollapseStatus::NotCollapsed)
	{
		UpdatedAvailableTileMesh_U = UpdatedAvailableTileMesh_R ;
	}
	if(RightNeighbour_1.CollapseStatus == EcollapseStatus::Collapsed)
	{
		for(FTileMesh TileMesh : UpdatedAvailableTileMesh_R)
		{
			for (UStaticMesh* AvailableMeshBecauseofLeftTile : RightNeighbour_1.SelectedTiledMesh.MatchingTiles.DownTileMesh )
			{
				if(TileMesh.TileMesh ==  AvailableMeshBecauseofLeftTile )
				{
					UpdatedAvailableTileMesh_U.Add(TileMesh);
					break;
				}
			}
			
		}
		
	}

	
	TArray<FTileMesh> UpdatedAvailableTileMesh_D;
	// checking Down tile
	if(RightNeighbour_1.CollapseStatus == EcollapseStatus::NotCollapsed)
	{
		UpdatedAvailableTileMesh_D = UpdatedAvailableTileMesh_U ;
	}
	if(RightNeighbour_1.CollapseStatus == EcollapseStatus::Collapsed)
	{
		for(FTileMesh TileMesh : UpdatedAvailableTileMesh_U)
		{
			for (UStaticMesh* AvailableMeshBecauseofLeftTile : RightNeighbour_1.SelectedTiledMesh.MatchingTiles.DownTileMesh )
			{
				if(TileMesh.TileMesh ==  AvailableMeshBecauseofLeftTile )
				{
					UpdatedAvailableTileMesh_D.Add(TileMesh);
					break;
				}
			}
			
		}
		
	}

	CurrentlyAvailableTilemesh = UpdatedAvailableTileMesh_D;
	
}



