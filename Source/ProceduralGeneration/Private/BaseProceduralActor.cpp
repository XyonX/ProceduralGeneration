// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProceduralActor.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Containers/Array.h"


void FTile::SetCollapseStatus(EcollapseStatus CollapseStatuss)
{
	CollapseStatus =CollapseStatuss;
}

void FTile::SetSelectedMesh(UStaticMesh* SelectedMeshh)
{
	SelectedMesh = SelectedMeshh ;
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
	GenerateTile();
	
	
	
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

	// this one choose the first tile Randomly
	int FirstTileID =  UKismetMathLibrary::RandomIntegerFromStream(Map_Length*Map_Width,Stream);

	// Choose a Random Mesh From All Mesh List
	int SelectedMeshSeriel;
	UStaticMesh*FirstSelectedMesh ;
	FirstSelectedMesh = RandomMeshFromTotalMesh(TotalTileMesh,SelectedMeshSeriel);

	// Storing the first selected tile in the FirstTile Variable
	FTile FirstTile = AllTiles[FirstTileID];
	AllTiles[FirstTileID].CollapseStatus =EcollapseStatus::Collapsed;
	AllTiles[FirstTileID].SelectedMesh =  FirstSelectedMesh ;


	/* As We have Chosen One mesh from a random section that means we have change the The entropy of surrounding mesh
	 So we have to update that supported mesh list

	one mesh changes particularly surrounded 4 meshes entropy

	for the left tile of selected mesh we are gonna check if the 

	*/

	

	//After Selecting the first mesh it goes for the second part choosing all the suitable part of all the sides
	RandomSuitableMeshFromTotalMesh(TotalTileMesh,SelectedMeshSeriel);

	


	
	// Now As We have the first mesh time to choose a random direction from			// HERE TILE Refering to the Mesh
	

	FSelectedMatchingMesh MatchingMesh = RandomSuitableMeshFromTotalMesh(TotalTileMesh , FirstTileID) ;
	//
	//
	
	

	
	
	
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
			TArray<FTileMesh> AvailMesh_LeftNeighbour = LeftNeighbour_1.AllAvailableMeshToChooseFrom;
		
			RightNeighbour_2 = TotalTile[i+20];
			TArray<FTileMesh> AvailMesh_RightNeighbour = RightNeighbour_1.AllAvailableMeshToChooseFrom;
		
			UpNeighbour_2  = TotalTile[i+2];
			TArray<FTileMesh> AvailMesh_UpNeighbour = UpNeighbour_1.AllAvailableMeshToChooseFrom;
		
			DownNeighbour_2= TotalTile[i-2] ;
			TArray<FTileMesh> AvailMesh_DownNeighbour = DownNeighbour_1.AllAvailableMeshToChooseFrom;
		}
		

		
		for(FTileMesh TileMesh : AvailableTileMesh)
		{
			
			// check  left-1 side tile
			for (	FTileMesh TileMesh1 : LeftNeighbour_1)
			{
				if(TileMesh1.TileMesh == TileMesh.TileMesh )
				{
					for(FTileMesh TileMesh2 : LeftNeighbour_2)
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


		
	
}

void ABaseProceduralActor::UpdateAvailableMesh_Surroundings(TArray<FTile> TotalTile, FTile SelectedTile)
{
	FTileMesh UpdatedTileMesh;
	
	FTile LeftNeighbour_1 ;
	FTile RightNeighbour_1 ;
	FTile UpNeighbour_1 ;
	FTile DownNeighbour_1 ;
	FTile LeftNeighbour_2 ;
	FTile RightNeighbour_2 ;
	FTile UpNeighbour_2 ;
	FTile DownNeighbour_2 ;
	
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
			for (UStaticMesh* AvailableMeshBecauseofLeftTile : LeftNeighbour_1.SelecteTiledMesh.MatchingTiles.RightTileMesh )
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
			for (UStaticMesh* AvailableMeshBecauseofLeftTile : RightNeighbour_1.SelecteTiledMesh.MatchingTiles.LeftTileMesh )
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
			for (UStaticMesh* AvailableMeshBecauseofLeftTile : RightNeighbour_1.SelecteTiledMesh.MatchingTiles.DownTileMesh )
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
			for (UStaticMesh* AvailableMeshBecauseofLeftTile : RightNeighbour_1.SelecteTiledMesh.MatchingTiles.DownTileMesh )
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






