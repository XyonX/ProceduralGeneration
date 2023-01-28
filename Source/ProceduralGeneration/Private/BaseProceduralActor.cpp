// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProceduralActor.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Containers/Array.h"


void FTile::SetCollapseStatus(EcollapseStatus CollapseStatuss)
{
	CollapseStatus =CollapseStatuss;
}



void FTileMesh::SetTileMesh(UStaticMesh* InTileMesh)
{
	TileMesh = InTileMesh;
	InstancedMesh->SetStaticMesh(TileMesh);
}

FMatchingTileArray FTileMesh::GetMatchingTiles()
{
	return MatchingTiles;
}

// Sets default values
ABaseProceduralActor::ABaseProceduralActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InstancedMesh= CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TileMesh"));
/*	Mesh_Right= CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Right Mesh"));
	Mesh_Up= CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Up Mesh"));
	Mesh_Down= CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Down Mesh"));
	Mesh_LeftUp= CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Left UP Mesh"));
	Mesh_RightUp= CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Right UP Mesh"));
	Mesh_LeftDown= CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Left Down Mesh"));
	Mesh_RightDown= CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Right Down Mesh"));
	Mesh_Middle= CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Middle Mesh"));*/

	// for the FTileMeshStruct
	InstancedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedMesh"));
	for(FTileMesh &tileMesh : TotalTileMesh)
	{
		tileMesh.InstancedMesh = InstancedMesh ;
		// set other properties of tileMesh
		if(tileMesh.TileMesh)
		tileMesh.InstancedMesh->SetStaticMesh(tileMesh.TileMesh);
	}
	
	AllTiles_float = 0 ;
	
}

// Called when the game starts or when spawned
void ABaseProceduralActor::BeginPlay()
{
	Super::BeginPlay();
	InstancedMesh->SetStaticMesh(StaticMesh);
	CalculateMeshLength();
	WaveFunctionCollapse();
	//GenerateTile();

}

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
			AllTiles_float ++ ;
			Tile.Position_2D.Width=j+1;
			Tile.Position_2D.Length=i+1;
			Tile.World_Location = FVector (i*Actor_Length_X , j*Actor_Length_Y,0.0f);
			Tile.AllAvailableMeshToChooseFrom=TotalTileMesh;
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
	GenerationDone=true;
	return GenerationDone;
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

void ABaseProceduralActor::WaveFunctionCollapse()
{
	
	// Generate Tile
	bool GenDone;
	GenDone =GenerateTile();
	if(GenDone)
	{
		// this one choose the first tile Randomly
		int FirstTileID =  UKismetMathLibrary::RandomIntegerFromStream(Map_Length*Map_Width,Stream);

		//Pick A Random Tile	//For the first time choose from stream

		FTile FirstRandomTile = AllTiles[25];

		//TODO MAKE A FUNCTION TO SPAWN ACTOR AND CREATE A NEW INSTANCED MESH FOR ALL THE FTILE MESH

		// Remove From Remaining Tile
		RemainingTiles =AllTiles;
		RemainingTiles.RemoveAt(FirstRandomTile.ID-1);

		//UPDATE THE SURROUNDING TILES AVAILABLEMESH

		UpdateAvailableMesh_Left(FirstRandomTile);
		UpdateAvailableMesh_Right(FirstRandomTile);
		UpdateAvailableMesh_Up(FirstRandomTile);
		UpdateAvailableMesh_Down(FirstRandomTile);

		while (RemainingTiles.Num()>0)
		{
			FTile SelectedTile = ReturnMeshWithLowEntropy(RemainingTiles);
			//TODO SAWN MESH
			//
			// Remove From Remaioning Tile

			RemainingTiles.RemoveAt(SelectedTile.ID-1);

			// Update Surroundings
			UpdateAvailableMesh_Left(SelectedTile);
			UpdateAvailableMesh_Right(SelectedTile);
			UpdateAvailableMesh_Up(SelectedTile);
			UpdateAvailableMesh_Down(SelectedTile);
		
		}
	}
}

void ABaseProceduralActor::GenerateTile_NEW(TArray<FTile> & GeneratedTile)
{
	AllTiles_float=0;
	for (int i = 0 ; i< Map_Length ; i++)
	{
		for (int j = 0 ; j< Map_Width ; j++)
		{
			
			int id;
			id=(i*10)+j+1;
			FTile Tile ;
			Tile.ID = id ;
			AllTiles_float ++ ;
			Tile.Position_2D.Width=j+1;
			Tile.Position_2D.Length=i+1;
			if(bWantCustomTileSize)
			{
				Tile.World_Location = FVector (i*Actor_Length , j*Actor_Length,0.0f);
			}
			Tile.World_Location = FVector (i*Actor_Length_X , j*Actor_Length_Y,0.0f);
			Tile.AllAvailableMeshToChooseFrom=TotalTileMesh;
			GeneratedTile.Add(Tile);
			
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

FTile ABaseProceduralActor::ChooseRandomTile(TArray<FTile> AllTileToChooseFrom)
{
	// Random Suitable left Mesh
	int RandomTile = FMath::RandRange(0,AllTiles.Num() );
	return AllTiles[RandomTile];
}

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
void ABaseProceduralActor::UpdateAvailableMesh_Right(FTile SelectedTile)
{
	FTile RightNeighbour  = AllTiles[SelectedTile.ID+10];
	TArray<FTileMesh> UpdatedAvailableTileMesh;
	TArray<FTileMesh> AvailableMesh = RightNeighbour.AllAvailableMeshToChooseFrom ;
	if(SelectedTile.ID+10 > AllTiles_float  ||  RightNeighbour.CollapseStatus==EcollapseStatus::Collapsed)
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

void ABaseProceduralActor::UpdateAvailableMesh_Up(FTile SelectedTile)
{
	FTile UpNeighbour  = AllTiles[SelectedTile.ID+1];
	TArray<FTileMesh> UpdatedAvailableTileMesh;
	TArray<FTileMesh> AvailableMesh = UpNeighbour.AllAvailableMeshToChooseFrom ;
	
	if(SelectedTile.ID+1 > AllTiles_float  ||  UpNeighbour.CollapseStatus==EcollapseStatus::Collapsed)
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

FTileMesh ABaseProceduralActor::RandomMeshFromAvailableMesh(TArray<FTileMesh>AvailableMeshArray)
{
	int RandomMESH = FMath::RandRange(0,AvailableMeshArray.Num() );
	return AvailableMeshArray[RandomMESH];
}

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





