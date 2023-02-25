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
	FlorInstanceMeshComponent= CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TileMesh"));

	// SETTING THE ALL TILE FLOAT COUNTER TO 0
	AllTiles_Float = 0 ;

	//Setting up Default tile mesh
	DefaultInstanceMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("DEFAULT MESH INSTANCE CONTAINER"));
	DefaultTileMesh.Owner=this;
	DefaultTileMesh.InstancedMesh=DefaultInstanceMeshComponent;
	
	//SETTING UP DEFAULT TILE
	DefaultTile.World_Location=FVector(0.0f,0.0f,100.0f);
	DefaultTile.Position_2D=FMatrixPosition(0,0);
	DefaultTile.SelectedTiledMesh= &DefaultTileMesh;
	
}


//BEGIN PLAY
void ABaseProceduralActor::BeginPlay()
{
	Super::BeginPlay();

	//init Tile Mesh
	InitTileMesh(TotalTileMesh);

	//setting the floor mesh
	FlorInstanceMeshComponent->SetStaticMesh(StaticMesh);

	//FOR DEBUG CONTAINER ACTOR
	DebugContainerAcotr = GetWorld()->SpawnActor<ACoreDebugContainer>(FVector::ZeroVector, FRotator::ZeroRotator);

	//GENERATING TILE
	CalculateMeshLength();
	GenerateTile();
	SetAllTilesREF(AllTilesPTR);
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
	for(FTile * Tile : AllTilesPTR)
	{
		delete Tile ;
	}
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
		UpdateSurroundingMesh(FirstRandomTile,AllTilesPTR);
	
		while (!RemainingTiles.IsEmpty())
		{
			// CHOOSE A TILE DEPENDING ENTROPY OF THE TILE
			int TileID = ReturnMeshIDWithLowEntropy(RemainingTiles);
			FTile* Tile = RemainingTiles[TileID-1];
			AddInstanceMesh(TileID,RemainingTiles);
			UpdateSurroundingMesh(Tile,RemainingTiles);
		}
}

// THIS FUNCTION CREATE THE INSTANCED MESH OBJET FOR ALL THE TILEMESH
void ABaseProceduralActor::InitTileMesh(TArray<FTileMesh>& TotalTileMeshes)
{
	for(FTileMesh &tileMesh : TotalTileMeshes)
	{
		tileMesh.Init(this);
		
	}
}

void ABaseProceduralActor::UpdateCollapsedTileData(int ID ,int ArrayPosition , TArray<FTile*>& TotalTilee ,TArray<FTile*>& RemainingTile, TArray<FTile*>& TotalCollapsedTile)
{
	//Update Collapse Status in the main tile

	//FTile&CollapsedTile = TotalTile[ID-1];
	TotalTilee[ID-1]->CollapseStatus=EcollapseStatus::Collapsed;

	//Remove From Remaining Title
	RemainingTile.RemoveAt(ArrayPosition);

	// Add th the collapsed tile
	TotalCollapsedTile.Add(TotalTilee[ID-1]);
}

int ABaseProceduralActor::ReturnMeshIDWithLowEntropy(TArray<FTile*>& TotalTile)
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

FTile* ABaseProceduralActor::GetTileByID(int ID, TArray<FTile*>& TotalTile)
{
	for (FTile* Tile : TotalTile)
	{
		if(Tile->ID==ID)
			return  Tile ;
	}
	return &DefaultTile;
}

FTile* ABaseProceduralActor::GetTileByPosition2D(FMatrixPosition Pos, TArray<FTile*>& TotalTile)
{
	for (FTile*Tile :TotalTile)
	{
		if(Tile->Position_2D.X == Pos.X && Tile->Position_2D.Y == Pos.Y )
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
			int Yvar=i+1;
			int Xvar=j+1;
			FMatrixPosition POS(Xvar,Yvar);
			FVector World_Location = FVector (i*Actor_Length_X , j*Actor_Length_Y,0.0f);
			FTile* Tile = new FTile (id,POS,World_Location,TotalTileMesh);
			AllTilesPTR.Add(Tile);
			
		}
	}
	GenerationDone=true;
	return GenerationDone;
}

void ABaseProceduralActor::SetTileLength(int Lenght ,int Width)
{
	
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
FTile* ABaseProceduralActor::ChooseRandomTile(TArray<FTile*>& AllTileToChooseFrom)
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
	if(FlorInstanceMeshComponent)
	{
		for(FTile* Tile : TotalTies)
		{
			FTransform Transform ;
			Transform.SetLocation(Tile->World_Location);
			FlorInstanceMeshComponent->AddInstance(Transform);
		}
	}
}

// THIS FUNCTION UPDATE SURROUNDING MAINLY CALL THOSE 4 FUNCTION
void ABaseProceduralActor::UpdateSurroundingMesh(FTile* SelectedTile, TArray<FTile*>&TotalTile)
{
	UpdateAvailableMesh_Left(SelectedTile,TotalTile);
	UpdateAvailableMesh_Right( SelectedTile,TotalTile);
	UpdateAvailableMesh_Up( SelectedTile,TotalTile);
	UpdateAvailableMesh_Down( SelectedTile,TotalTile);
}

// UPDATE LEFT SIDE OF THE SELECTED MESH
void ABaseProceduralActor::UpdateAvailableMesh_Left(FTile* SelectedTile,TArray<FTile*>&TotalTile)
{
	
	FMatrixPosition Position2D = SelectedTile->Position_2D;
	if(Position2D.Y-1 <=0 )
	{
		return;
	}
	FMatrixPosition Pos (Position2D.X,Position2D.Y-1);
	FTile* LeftNeighbour  = GetTileByPosition2D(Pos,AllTilesPTR);
	TArray<FTileMesh*> UpdatedAvailableTileMesh;

	if( LeftNeighbour->CollapseStatus==EcollapseStatus::Collapsed)
	{
		return;
	}
	

	for (FTileMesh* AvailableTileMesh_Left : LeftNeighbour->AllAvailableMeshToChooseFrom )
	{
		if(AvailableTileMesh_Left->ComaptileMeshTag_Right.HasTag(SelectedTile->SelectedTiledMesh->MeshTag))
		{
			UpdatedAvailableTileMesh.Add(AvailableTileMesh_Left);
		}
			
	}
	SelectedTile->AllAvailableMeshToChooseFrom =UpdatedAvailableTileMesh;
	
}

// UPDATE RIGHT SIDE OF THE SELECTED MESH
void ABaseProceduralActor::UpdateAvailableMesh_Right(FTile* SelectedTile,TArray<FTile*>&TotalTile)
{
	FMatrixPosition Position2D = SelectedTile->Position_2D;
	if(Position2D.Y+1 > AllTiles_Float  )
	{
		return;
	}
	FMatrixPosition Pos(Position2D.X,Position2D.Y+1);
	FTile* RightNeighbour =GetTileByPosition2D(Pos,AllTilesPTR);
	
	TArray<FTileMesh*> UpdatedAvailableTileMesh;
	
	if(RightNeighbour->CollapseStatus==EcollapseStatus::Collapsed)
	{
		return;
	}

	for (FTileMesh* AvailableTileMesh_Right : RightNeighbour->AllAvailableMeshToChooseFrom )
	{
			if(AvailableTileMesh_Right->ComaptileMeshTag_Left.HasTag(SelectedTile->SelectedTiledMesh->MeshTag))
			UpdatedAvailableTileMesh.Add(AvailableTileMesh_Right);
	}
	SelectedTile->AllAvailableMeshToChooseFrom =UpdatedAvailableTileMesh;
}

// UPDATE UP SIDE OF SELECTED MESH
void ABaseProceduralActor::UpdateAvailableMesh_Up(FTile* SelectedTile,TArray<FTile*>&TotalTile)
{
	FMatrixPosition Position2D =SelectedTile->Position_2D;
	if(Position2D.X+1 > AllTiles_Float )
	{
		return;
	}
	FMatrixPosition Pos(Position2D.X+1,Position2D.Y);
	FTile* UpNeighbour  = GetTileByPosition2D(Pos,AllTilesPTR);
	TArray<FTileMesh*> UpdatedAvailableTileMesh;
	
	if(UpNeighbour->CollapseStatus==EcollapseStatus::Collapsed)
	{
		return;
	}
	for (FTileMesh* AvailableTileMesh_Up : UpNeighbour->AllAvailableMeshToChooseFrom )
	{
		if(AvailableTileMesh_Up->ComaptileMeshTag_Down.HasTag(SelectedTile->SelectedTiledMesh->MeshTag))
			UpdatedAvailableTileMesh.Add(AvailableTileMesh_Up);
	}
	SelectedTile->AllAvailableMeshToChooseFrom =UpdatedAvailableTileMesh;
}

// UPDATE DOWN SIDE OF SELECTED MESH 
void ABaseProceduralActor::UpdateAvailableMesh_Down(FTile* SelectedTile,TArray<FTile*>&TotalTile)
{
	{
		FMatrixPosition Position2D = SelectedTile->Position_2D;
		if(Position2D.X-1 <= 0 )
		{
			return;
		}
		FMatrixPosition Pos(Position2D.X-1,Position2D.Y);
		FTile* DownNeighbour  = GetTileByPosition2D(Pos,AllTilesPTR);
		TArray<FTileMesh*> UpdatedAvailableTileMesh;
	
		if(DownNeighbour->CollapseStatus==EcollapseStatus::Collapsed)
		{
			return;
		}
		for (FTileMesh* AvailableTileMesh_Down : DownNeighbour->AllAvailableMeshToChooseFrom )
		{
			if(AvailableTileMesh_Down->ComaptileMeshTag_Up.HasTag(SelectedTile->SelectedTiledMesh->MeshTag))
				UpdatedAvailableTileMesh.Add(AvailableTileMesh_Down);
		}
		SelectedTile->AllAvailableMeshToChooseFrom =UpdatedAvailableTileMesh;
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

void ABaseProceduralActor::AddInstanceMesh(int ID, TArray<FTile*>& TotalTile)
{
	FTile*SelectedTile = TotalTile[ID-1];
	
	SelectedTile->SelectedTiledMesh = RandomMeshFromAvailableMesh(SelectedTile);
	if(SelectedTile->SelectedTiledMesh->TileMesh ==nullptr  )
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Instance Add Failedd Selected Tile Didint have any Selected  Mesh "));}
		return;
	}
	SelectedTile->SelectedTiledMesh->OwnerTileList.Add(SelectedTile);
	if(SelectedTile->SelectedTiledMesh->TileMesh != nullptr)
	{
		FTransform SpawnTransform ;
		SpawnTransform.SetLocation(TotalTile[ID-1]->World_Location);
		SelectedTile->SelectedTiledMesh->InstancedMesh->AddInstance(SpawnTransform);
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green,  TEXT(" INSTANCE ADING DONE "));}
	}
}






