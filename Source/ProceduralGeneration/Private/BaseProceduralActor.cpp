// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseProceduralActor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProceduralGeneration/Public/CoreDebugContainer.h"
#include "Containers/Array.h"
#include "FTile.h"

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

	//init Tile Mesh
	InitTileMesh(TotalTileMesh);

	//setting the floor mesh
	FlorInstanceMesh->SetStaticMesh(StaticMesh);

	//FOR DEBUG CONTAINER ACTOR
	DebugContainerAcotr = GetWorld()->SpawnActor<ACoreDebugContainer>(FVector::ZeroVector, FRotator::ZeroRotator);

	//GENERATING TILE
	CalculateMeshLength();
	GenerateTile();
	GenerateBaseFloor(AllTilesPTR);
	
	if ( !AllTilesPTR.IsEmpty()  && !TotalTileMesh.IsEmpty() )
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT(" BOTH TILE AND TOTAL MESH AVAILABLE WAVE FUNCTION CALLING  "));}

		//STARTING THE MAIN ALGORITHM
		WaveFunctionCollapse();
	}
}

void ABaseProceduralActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	delete AllTilesPTR;
}

// THE MAIN ALGORITHM
void ABaseProceduralActor::WaveFunctionCollapse()
{

		//Adding RemainingTile To All Tile
		RemainingTiles.Reserve(AllTilesPTR.Num());
		for(FTile* Tile : AllTilesPTR)
			{
				RemainingTiles.Add(Tile)  ;
			}
		
	
		// FIRST RANDOM ID FROM STREAM
		Stream.GenerateNewSeed();
		int FirstIndices =  UKismetMathLibrary::RandomIntegerFromStream(RemainingTiles.Num()-1,Stream);
		
		//Pick A Random Tile	//For the first time choose from stream
		FTile* FirstRandomTile = RemainingTiles[FirstIndices];
		
		// ADDING INSTANCE OF THE SELECTED MESH
		AddInstanceMesh(FirstRandomTile->ID,AllTilesPTR);
		//Update  Collapsed Tile Data
		UpdateCollapsedTileData(FirstRandomTile->ID,FirstIndices,AllTilesPTR,RemainingTiles,CollapsedTiles);

		//UPDATE THE SURROUNDING TILES AVAILABLE MESH
		UpdateSurroundingMesh(FirstRandomTile->Position_2D,FirstRandomTile->ID,AllTilesPTR);
	
		/*while (!RemainingTiles.IsEmpty())
		{
			// CHOOSE A TILE DEPENDING ENTROPY OF THE TILE
			int TileID = ReturnMeshIDWithLowEntropy(AllTiles);
			FTile& Tile = AllTiles[TileID-1];
			AddInstanceMesh(TileID,AllTiles);
			UpdateSurroundingMesh(Tile.Position_2D,TileID,AllTiles);
		}*/
}

// THIS FUNCTION CREATE THE INSTANCED MESH OBJET FOR ALL THE TILEMESH
void ABaseProceduralActor::InitTileMesh(TArray<FTileMesh>& TotalTileMeshes)
{
	for(FTileMesh &tileMesh : TotalTileMeshes)
	{
		tileMesh.Init(this);
		
	}
}

void ABaseProceduralActor::UpdateCollapsedTileData(int ID ,int ArrayPosition , TArray<FTile*> TotalTilee ,TArray<FTile*> RemainingTile, TArray<FTile*> TotalCollapsedTile)
{
	//Update Collapse Status in the main tile

	//FTile&CollapsedTile = TotalTile[ID-1];
	TotalTilee[ID-1]->CollapseStatus=EcollapseStatus::Collapsed;

	//Remove From Remaining Title
	RemainingTile.RemoveAt(ArrayPosition);

	// Add th the collapsed tile
	TotalCollapsedTile.Add(TotalTilee[ID-1]);
}

int ABaseProceduralActor::ReturnMeshIDWithLowEntropy(TArray<FTile*> TotalTile)
{
	int LowestNumberOfTile =999;
	int id=0;
	for(FTile* Tile : TotalTile )
	{
		if(Tile->AllAvailableMeshToChooseFrom.Num()<LowestNumberOfTile )
		{

			LowestNumberOfTile=Tile->AllAvailableMeshToChooseFrom.Num();
			id =Tile->ID;
		}
	}
	return id;
}

FTile* ABaseProceduralActor::GetTileByID(int ID, TArray<FTile*> TotalTile)
{
	for (FTile* Tile : TotalTile)
	{
		if(Tile->ID==ID)
			return  Tile ;
	}
	return &DefaultTile;
}

FTile* ABaseProceduralActor::GetTileByPosition2D(FMatrixPosition Pos, TArray<FTile*> TotalTile)
{
	for (FTile*Tile :TotalTile)
	{
		if(Tile->Position_2D.Height == Pos.Height && Tile->Position_2D.Height == Pos.Width )
		{
			return Tile;
		}
	}
	if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("  ERROR IN TILE FOUND RETURN DEFAULT TILE  "));}
	return &DefaultTile;
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
	if(TotalTileMesh.IsEmpty())
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Total Tile Not set properly Tile Generation Aborted!!!  "));}
	}
	bool GenerationDone= false;
	int id=0;
	for (int i = 0 ; i< Map_Height ; i++)
	{
		for (int j = 0 ; j< Map_Width ; j++)
		{
			
			
			
			
			id++;
			AllTiles_Float ++ ;
			int PosHeight=i+1;
			int PosWidth=j+1;
			FMatrixPosition POS(PosHeight,PosWidth);
			FVector World_Location = FVector (i*Actor_Length_X , j*Actor_Length_Y,0.0f);
			FTile* Tile = new FTile (id,POS,World_Location,TotalTileMesh);
			AllTilesPTR.Add(Tile);
			
		}
	}
	GenerationDone=true;
	return GenerationDone;
}

void ABaseProceduralActor::SetAllTilesREF(TArray<FTile*>& alltile)
{
	if (alltile.IsEmpty())
	{
		UE_LOG(LogTemp,Warning,TEXT("AllTiles ARRAY IS EMPTY REF SET UNSUCCESSFULL"));
		return;
	}
	for (FTile* tile : alltile)
	{
		//FTile& TileRef = *tile; // create a reference to the FTile object pointed to by TilePtr
		FTile& TileRef = *tile; 
		AllTilesREF.Add(TileRef);
		//AllTilesREF.Add(std::ref(*TilePtr));
	}
}

/*
bool ABaseProceduralActor::GenerateTile_V2()
{
	bool GenerationDone= false;
	int id=0;
	FTileContainer*CurrentTileContainer ;
	for (int i = 0 ; i< Map_Height ; i++)
	{
		for (int j = 0 ; j< Map_Width ; j++)
		{
			
			std::unique_ptr<FTile> tile(new FTile);
			id++;
			tile->ID = id ;
			AllTiles_Float ++ ;
			tile->Position_2D.Height=i+1;
			tile->Position_2D.Width=j+1;
			tile->World_Location = FVector (i*Actor_Length_X , j*Actor_Length_Y,0.0f);

			FTileContainer* TileContainer = new FTileContainer;
			TileContainer->Tile=std::move(tile);
			CurrentTileContainer=TileContainer;
			FTileContainer*NextTileCotainer =new FTileContainer;
			CurrentTileContainer->NextTileContainer =NextTileCotainer;
			CurrentTileContainer=NextTileCotainer;

			if(AllTiles_HEAD==nullptr)
			{
				AllTiles_HEAD=new FTileContainer;
				AllTiles_HEAD->Tile=std::move(tile);
				AllTiles_HEAD->NextTileContainer=CurrentTileContainer;
			}
		}
	}
	GenerationDone=true;
	return GenerationDone;
	
}*/

// THIS FUNCTION CHOOSE RANDOM TILE FROM GIVEN ARRAY
FTile* ABaseProceduralActor::ChooseRandomTile(TArray<FTile*> AllTileToChooseFrom)
{
	
	int RandomTile = FMath::RandRange(0,AllTileToChooseFrom.Num() );
	return AllTilesPTR[RandomTile];
}



void ABaseProceduralActor::GenerateBaseFloor( TArray<FTile*>&TotalTies)
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
		for(FTile* Tile : TotalTies)
		{
			FTransform Transform ;
			Transform.SetLocation(Tile->World_Location);
			FlorInstanceMesh->AddInstance(Transform);
		}
	}
}

// THIS FUNCTION UPDATE SURROUNDING MAINLY CALL THOSE 4 FUNCTION
void ABaseProceduralActor::UpdateSurroundingMesh(FMatrixPosition Position2D ,int SelectedTileID, TArray<FTile*>TotalTile)
{
	UpdateAvailableMesh_Left(Position2D,SelectedTileID ,TotalTile);
	UpdateAvailableMesh_Right(Position2D,SelectedTileID,TotalTile);
	UpdateAvailableMesh_Up(Position2D,SelectedTileID,TotalTile);
	UpdateAvailableMesh_Down(Position2D,SelectedTileID ,TotalTile);
}

// UPDATE LEFT SIDE OF THE SELECTED MESH
void ABaseProceduralActor::UpdateAvailableMesh_Left(FMatrixPosition Position2D ,int SelectedTileID, TArray<FTile*>TotalTile)
{
	
	
	if(Position2D.Width-1 <=0 )
	{
		return;
	}
	FMatrixPosition Pos (Position2D.Height,Position2D.Width-1);
	FTile* LeftNeighbour  = GetTileByPosition2D(Pos,AllTilesPTR);
	TArray<FTileMesh*> UpdatedAvailableTileMesh;
	TArray<FTileMesh*> AvailableMesh = LeftNeighbour->AllAvailableMeshToChooseFrom ;

	if( LeftNeighbour->CollapseStatus==EcollapseStatus::Collapsed)
	{
		return;
	}
	

	for (FTileMesh* AvailableTileMesh_Left : AvailableMesh )
	{
		if(AvailableTileMesh_Left->ComaptileMeshTag_Right.HasTag(GetTileByID(SelectedTileID,TotalTile)->SelectedTiledMesh->MeshTag))
			UpdatedAvailableTileMesh.Add(AvailableTileMesh_Left);
	}
	GetTileByID(SelectedTileID,TotalTile)->AllAvailableMeshToChooseFrom =UpdatedAvailableTileMesh;
	
}

// UPDATE RIGHT SIDE OF THE SELECTED MESH
void ABaseProceduralActor::UpdateAvailableMesh_Right(FMatrixPosition Position2D ,int SelectedTileID, TArray<FTile*>TotalTile)
{
	if(Position2D.Width+1 > AllTiles_Float  )
	{
		return;
	}
	FMatrixPosition Pos(Position2D.Height,Position2D.Width+1);
	FTile* RightNeighbour =GetTileByPosition2D(Pos,AllTilesPTR);
	
	TArray<FTileMesh*> UpdatedAvailableTileMesh;
	TArray<FTileMesh*> AvailableMesh = RightNeighbour->AllAvailableMeshToChooseFrom ;
	if(RightNeighbour->CollapseStatus==EcollapseStatus::Collapsed)
	{
		return;
	}

	for (FTileMesh* AvailableTileMesh_Right : AvailableMesh )
	{
			if(AvailableTileMesh_Right->ComaptileMeshTag_Left.HasTag(GetTileByID(SelectedTileID,TotalTile)->SelectedTiledMesh->MeshTag))
			UpdatedAvailableTileMesh.Add(AvailableTileMesh_Right);
	}
	GetTileByID(SelectedTileID,TotalTile)->AllAvailableMeshToChooseFrom =UpdatedAvailableTileMesh;
}

// UPDATE UP SIDE OF SELECTED MESH
void ABaseProceduralActor::UpdateAvailableMesh_Up(FMatrixPosition Position2D ,int SelectedTileID, TArray<FTile*>TotalTile)
{
	if(Position2D.Height+1 > AllTiles_Float )
	{
		return;
	}
	FMatrixPosition Pos(Position2D.Height+1,Position2D.Width);
	FTile* UpNeighbour  = GetTileByPosition2D(Pos,AllTilesPTR);
	TArray<FTileMesh*> UpdatedAvailableTileMesh;
	TArray<FTileMesh*> AvailableMesh = UpNeighbour->AllAvailableMeshToChooseFrom ;
	if(UpNeighbour->CollapseStatus==EcollapseStatus::Collapsed)
	{
		return;
	}
	for (FTileMesh* AvailableTileMesh_Up : AvailableMesh )
	{
		if(AvailableTileMesh_Up->ComaptileMeshTag_Down.HasTag(GetTileByID(SelectedTileID,TotalTile)->SelectedTiledMesh->MeshTag))
			UpdatedAvailableTileMesh.Add(AvailableTileMesh_Up);
	}
	GetTileByID(SelectedTileID,TotalTile)->AllAvailableMeshToChooseFrom =UpdatedAvailableTileMesh;
}

// UPDATE DOWN SIDE OF SELECTED MESH 
void ABaseProceduralActor::UpdateAvailableMesh_Down(FMatrixPosition Position2D ,int SelectedTileID, TArray<FTile*>TotalTile)
{
	{
		if(Position2D.Height-1 <= 0 )
		{
			return;
		}
		FMatrixPosition Pos(Position2D.Height-1,Position2D.Width);
		FTile* DownNeighbour  = GetTileByPosition2D(Pos,AllTilesPTR);
		TArray<FTileMesh*> UpdatedAvailableTileMesh;
		TArray<FTileMesh*> AvailableMesh = DownNeighbour->AllAvailableMeshToChooseFrom ;
	
		if(DownNeighbour->CollapseStatus==EcollapseStatus::Collapsed)
		{
			return;
		}
		for (FTileMesh* AvailableTileMesh_Down : AvailableMesh )
		{
			if(AvailableTileMesh_Down->ComaptileMeshTag_Up.HasTag(GetTileByID(SelectedTileID,TotalTile)->SelectedTiledMesh->MeshTag))
				UpdatedAvailableTileMesh.Add(AvailableTileMesh_Down);
		}
		GetTileByID(SelectedTileID,TotalTile)->AllAvailableMeshToChooseFrom =UpdatedAvailableTileMesh;
	}
}


// CHOOSE AN RAND0M ARRAY FROM GIVEN ARRAY OF FTILEMESH BASED ON ENTROPY
FTileMesh* ABaseProceduralActor::RandomMeshFromAvailableMesh(FTile* Tile)
{
	static FTileMesh& DefaultMesh=DefaultTileMesh ;
	//if(Tile.AllAvailableMeshToChooseFrom.Num() == 0)
	if(Tile->AllAvailableMeshToChooseFrom.IsEmpty())
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("   Available mesh list is empty For this tile unable to select any random Mesh "));}
		return &DefaultMesh;
	}
	
	int RandomMESH = FMath::RandRange(0,Tile->AllAvailableMeshToChooseFrom.Num()-1 );
	FTileMesh*SelectedTileMesh = Tile->AllAvailableMeshToChooseFrom[RandomMESH];
	return SelectedTileMesh;
}

void ABaseProceduralActor::AddInstanceMesh(int ID, TArray<FTile*> TotalTile)
{
	FTile*SelectedTile = TotalTile[ID-1];
	
	SelectedTile->SelectedTiledMesh = RandomMeshFromAvailableMesh(SelectedTile);
	if(SelectedTile->SelectedTiledMesh->TileMesh ==nullptr  )
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Instance Add Failedd Selected Tile Didint have any Selected  Mesh "));}
		return;
	}
	if(SelectedTile->SelectedTiledMesh->TileMesh != nullptr)
	{
		FTransform SpawnTransform ;
		SpawnTransform.SetLocation(TotalTile[ID-1]->World_Location);
		SelectedTile->SelectedTiledMesh->InstancedMesh->AddInstance(SpawnTransform);
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green,  TEXT(" INSTANCE ADING DONE "));}
	}
}






