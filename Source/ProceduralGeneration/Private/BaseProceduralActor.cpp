// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProceduralActor.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Containers/Array.h"


void FTile::SetCollapseStatus(EcollapseStatus CollapseStatuss)
{
	CollapseStatus =CollapseStatuss;
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
	AllTiles_float = 0 ;
	
}

// Called when the game starts or when spawned
void ABaseProceduralActor::BeginPlay()
{
	Super::BeginPlay();
	InstancedMesh->SetStaticMesh(StaticMesh);
	CalculateMeshLength();
	//GenerateTile();

	
	

	
	
	
	
}

// Called every frame
void ABaseProceduralActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ABaseProceduralActor::GenerateTile()
{
	
	for (int i = 0 ; i< Map_Length ; i++)
	{
		for (int j = 0 ; j< Map_Width ; j++)
		{
			
			int id;
			id=(i*10)+j+1;
			FTile Tile ;
			Tile.ID = id ;
			AllTiles_float +=id ;
			Tile.Position_2D.Width=j+1;
			Tile.Position_2D.Length=i+1;
			if(bWantCustomTileSize)
			{
				Tile.World_Location = FVector (i*Actor_Length , j*Actor_Length,0.0f);
			}
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
	GenerateTile_NEW(AllTiles);

	// this one choose the first tile Randomly
	int FirstTileID =  UKismetMathLibrary::RandomIntegerFromStream(Map_Length*Map_Width,Stream);

	//Pick A Random Tile	//For the first time choose from stream

	FTile FirstRandomTileRandomTile = AllTiles[FirstTileID];

	//TODO MAKE A FUNCTION TO SPAWN ACTOR AND CREATE A NEW INSTANCED MESH FOR ALL THE FTILE MESH

	// Remove From Remaining Tile

	AllTiles.Remove(FirstRandomTileRandomTile);

	//UPDATE THE SURROUNDING TILES AVAILABLEMESH

	UpdateAvailableMesh_Left(FirstRandomTileRandomTile);
	UpdateAvailableMesh_Right(FirstRandomTileRandomTile);
	UpdateAvailableMesh_Up(FirstRandomTileRandomTile);
	UpdateAvailableMesh_Down(FirstRandomTileRandomTile);

	while (RemainingTiles.Num()<=0)
	{
		FTile SelectedTile = ReturnMeshWithLowEntropy(RemainingTiles);
		//TODO SAWN MESH
		//
		// Remove From Remaioning Tile
		RemainingTiles.Remove(SelectedTile);

		// Update Surroundings
		UpdateAvailableMesh_Left(SelectedTile);
		UpdateAvailableMesh_Right(SelectedTile);
		UpdateAvailableMesh_Up(SelectedTile);
		UpdateAvailableMesh_Down(SelectedTile);
		
	}
	
	

	
	
	
}

FMatchingTileArray ABaseProceduralActor::FindSuitablePieces(FTileMesh TileMesh)
{
	return  TileMesh.MatchingTiles;
}

UStaticMesh* ABaseProceduralActor::RandomMeshFromTotalMesh(TArray<FTileMesh> TotalMesh ,  int &  SerielNoRef)
{
	int Ran = FMath::RandRange(0,TotalMesh.Num() );
	SerielNoRef = Ran;
	return TotalMesh[Ran].TileMesh;
	
}

FSelectedMatchingMesh ABaseProceduralActor::RandomSuitableMeshFromTotalMesh(TArray<FTileMesh> TotalMesh, int SerielNo)
{
	{
		FSelectedMatchingMesh SelectedMatchingTile ;
		FTileMesh Tilemesh = TotalMesh[SerielNo];
		FMatchingTileArray TilesArray = Tilemesh.MatchingTiles;

		// Random Suitable left Mesh
		int RanLeftTile = FMath::RandRange(0,Tilemesh.MatchingTiles.LeftTileMesh.Num() );
	
		SelectedMatchingTile.LeftTileMesh = Tilemesh.MatchingTiles.LeftTileMesh[RanLeftTile];


		//Random Suitable Right Mesh
		int RanRightTile = FMath::RandRange(0,Tilemesh.MatchingTiles.RightTileMesh.Num() );
	
		SelectedMatchingTile.LeftTileMesh = Tilemesh.MatchingTiles.LeftTileMesh[RanRightTile];

		//Random Suitable Top Mesh
		int RanUpTile = FMath::RandRange(0,Tilemesh.MatchingTiles.UpTileMesh.Num() );
	
		SelectedMatchingTile.LeftTileMesh = Tilemesh.MatchingTiles.LeftTileMesh[RanUpTile];

		//Random Suitable Top Mesh
		int RanDownTile = FMath::RandRange(0,Tilemesh.MatchingTiles.UpTileMesh.Num() );
	
		SelectedMatchingTile.LeftTileMesh = Tilemesh.MatchingTiles.LeftTileMesh[RanDownTile];

		return SelectedMatchingTile ; 


	
	
	}
}

bool ABaseProceduralActor::CheckCollapseStatus(int ID)
{
	EcollapseStatus CollapseStatus = AllTiles[ID].CollapseStatus;

	if(CollapseStatus == EcollapseStatus::Collapsed)
	{
		return true;
	}
	else
		return  false;
		
}

void ABaseProceduralActor::UpdateAvailableMesh(TArray<FTile> TotalTile)
{
	FTile SelectedTile;
	
	FTile LeftNeighbour_1 ;
	FTile RightNeighbour_1 ;
	FTile UpNeighbour_1 ;
	FTile DownNeighbour_1 ;
	FTile LeftNeighbour_2 ;
	FTile RightNeighbour_2 ;
	FTile UpNeighbour_2 ;
	FTile DownNeighbour_2 ;

	/*
	for (int i = 1 ; 1<= AllTiles_float ; i++ )
	{
		
		FTileMesh UpdatedAvailableMesh;
		SelectedTile = TotalTile[i];
		TArray<FTileMesh> AvailMesh_Selected = SelectedTile.AllAvailableMeshToChooseFrom;
		LeftNeighbourTile  = TotalTile[i-10];
		TArray<FTileMesh> AvailMesh_LeftNeighbour = LeftNeighbourTile.AllAvailableMeshToChooseFrom;
		RightNeighbourTile = TotalTile[i+10];
		TArray<FTileMesh> AvailMesh_RightNeighbour = RightNeighbourTile.AllAvailableMeshToChooseFrom;
		UpNeighbourTile  = TotalTile[i+1];
		TArray<FTileMesh> AvailMesh_UpNeighbour = UpNeighbourTile.AllAvailableMeshToChooseFrom;
		DownNeighbourTile = TotalTile[i+1] ;
		TArray<FTileMesh> AvailMesh_DownNeighbour = DownNeighbourTile.AllAvailableMeshToChooseFrom;

		//find commonmesh
		for (FTileMesh TileMesh  : AvailMesh_Selected)
		{
			 UStaticMesh*Mesh =  TileMesh.TileMesh ;

			//Checking The left esh of the selected mesh 
			
			for (FTileMesh TileMesh : AvailMesh_LeftNeighbour)
			{
				UStaticMesh*RightMEshOfLeftTile =TileMesh.MatchingTiles.RightTileMesh ;

				if(RightMEshOfLeftTile ==Mesh)
				{
					SelectedTile.MatchingTiles.
				}
				
			}
			
			
			
		}*/
		
	// we are going through every tile and updating it
	// here we are starting  from 1
	/*
	for (int i = 1 ; 1<= AllTiles_float ; i++ )
	{

		SelectedTile = TotalTile[i];
		TArray<FTileMesh> UpdatedAvailableMesh;
		TArray<FTileMesh>AvailableTileMesh = SelectedTile.AllAvailableMeshToChooseFrom ;

		// one left tiles
		
		if(!( i-10 <0 && i+10 > AllTiles_float))
		{
			LeftNeighbour_1  = TotalTile[i-10];
			TArray<FTileMesh> AvailMesh_LeftNeighbour_1 = LeftNeighbour_1.AllAvailableMeshToChooseFrom;
		
			RightNeighbour_1 = TotalTile[i+10];
			TArray<FTileMesh> AvailMesh_RightNeighbour_1 = RightNeighbour_1.AllAvailableMeshToChooseFrom;
		
			UpNeighbour_1  = TotalTile[i+1];
			TArray<FTileMesh> AvailMesh_UpNeighbour_1 = UpNeighbour_1.AllAvailableMeshToChooseFrom;
		
			DownNeighbour_1= TotalTile[i-1] ;
			TArray<FTileMesh> AvailMesh_DownNeighbour_1 = DownNeighbour_1.AllAvailableMeshToChooseFrom;
		}
		

		//two left tiles
		if(!( i-20 <0 && i+20 > AllTiles_float))
		{
			LeftNeighbour_2  = TotalTile[i-20];
			TArray<FTileMesh> AvailMesh_LeftNeighbour_2 = LeftNeighbour_1.AllAvailableMeshToChooseFrom;
		
			RightNeighbour_2 = TotalTile[i+20];
			TArray<FTileMesh> AvailMesh_RightNeighbour_2 = RightNeighbour_1.AllAvailableMeshToChooseFrom;
		
			UpNeighbour_2  = TotalTile[i+2];
			TArray<FTileMesh> AvailMesh_UpNeighbour_2 = UpNeighbour_1.AllAvailableMeshToChooseFrom;
		
			DownNeighbour_2= TotalTile[i-2] ;
			TArray<FTileMesh> AvailMesh_DownNeighbour_2 = DownNeighbour_1.AllAvailableMeshToChooseFrom;
		}
		

		
		for(FTileMesh TileMesh : AvailableTileMesh)
		{
			
			// check  left-1 side tile
			for (	FTileMesh TileMesh1 : LeftNeighbour_1)
			{
				if(TileMesh1.TileMesh == TileMesh.TileMesh )
				{
					for(FTileMesh TileMesh2 : LeftNeighbour_2.AllAvailableMeshToChooseFrom)
					{
						FMatchingTileArray MatchingTileArray = TileMesh2.MatchingTiles;

						for(UStaticMesh* RightMesh : MatchingTileArray.RightTileMesh)
						{
							if(TileMesh.TileMesh == RightMesh)
							{
								UpdatedAvailableMesh.Add(TileMesh);
								TotalTile[i].AllAvailableMeshToChooseFrom = UpdatedAvailableMesh ;
								
							}
								
						}
							
					}
				}

				
				
			}
			
		}
		
	
		
		
		
		
		
	}
*/

		
	
}



void ABaseProceduralActor::ChooseRandomRoute()
{
	
}

bool ABaseProceduralActor::DoesNeedMeshUpdated(TArray<FTile>AllTile, FTile SelectedTile)
{
	int TileSeriel = SelectedTile.ID;
	if(! (TileSeriel-10 <0 && TileSeriel+10 >AllTiles_float ))
	{
		FTile LeftTile =  AllTile[TileSeriel-10];
		FTile RightTile =  AllTile[TileSeriel+10];
		FTile UpTile = AllTile[TileSeriel+1];
		FTile DownTile = AllTile[TileSeriel-1];
	}
	
	return true;
	
}

void ABaseProceduralActor::GenerateTile_NEW(TArray<FTile> & GeneratedTile)
{
	for (int i = 0 ; i< Map_Length ; i++)
	{
		for (int j = 0 ; j< Map_Width ; j++)
		{
			
			int id;
			id=(i*10)+j+1;
			FTile Tile ;
			Tile.ID = id ;
			AllTiles_float +=id ;
			Tile.Position_2D.Width=j+1;
			Tile.Position_2D.Length=i+1;
			if(bWantCustomTileSize)
			{
				Tile.World_Location = FVector (i*Actor_Length , j*Actor_Length,0.0f);
			}
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
	GeneratedTile =AllTiles;
	
}

FTile ABaseProceduralActor::ChooseRandomTile(TArray<FTile> AllTileToChooseFrom)
{
	// Random Suitable left Mesh
	int RandomTile = FMath::RandRange(0,AllTiles.Num() );
	return AllTiles[RandomTile];
}

void ABaseProceduralActor::UpdateAvailableMesh_Left(FTile SelectedTile)
{
	FTile LeftNeighbour  = AllTiles[SelectedTile.ID-10];
	TArray<FTileMesh> UpdatedAvailableTileMesh;
	TArray<FTileMesh> AvailableMesh = LeftNeighbour.AllAvailableMeshToChooseFrom ;
	
	if(SelectedTile.ID-10 <=0  ||  LeftNeighbour.CollapseStatus==EcollapseStatus::Collapsed)
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





