/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/


#include "CoreSpawner.h"
#include "ProceduralGeneration/Tiles/Tile.h"
#include "CorePlugin/Spawnables/Spawnable.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameplayTagContainer.h"

UCoreSpawner::UCoreSpawner()
{
}

/*
UCoreSpawner::UCoreSpawner(TArray<UTile*>*InTotalTiles, TMap<int32,USpawnable*>*InTotalSpawnables , int InMap_Height , int InMap_Width)
{
	TotalTiles=InTotalTiles;
	TotalSpawnables=InTotalSpawnables;
	Map_Height=InMap_Height;
	Map_Width=InMap_Width;
	
	
}*/

bool UCoreSpawner::Init(TArray<UTile*>*InTotalTiles, TMap<int32,USpawnable*>*InTotalSpawnables,UTile*InDefaultTile,USpawnable*InDefaultSpawnable,int InMap_Height , int InMap_Width)
{
	SetTotalTiles(InTotalTiles);
	SetTotalSpawnables(InTotalSpawnables);
	Map_Height=InMap_Height;
	Map_Width=InMap_Width;
	return true;
	
}

void UCoreSpawner::SetTotalTiles(TArray<UTile*>* InTotalTiles)
{
	if(TotalTiles==nullptr)
	{
		TotalTiles=InTotalTiles;
	}
}

void UCoreSpawner::SetTotalSpawnables(TMap<int32, USpawnable*>* InTotalSpawnables)
{
	if(TotalSpawnables==nullptr)
	{
		TotalSpawnables= InTotalSpawnables;
	}
}
/*
USpawnable* UCoreSpawner::RandomSpawnableFromAvailableSpawnable(UTile* InTile)
{
	//if(Tile.AllAvailableMeshToChooseFrom.Num() == 0)
	if(InTile->AllocatedSpawnables.IsEmpty())
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("   Available mesh list is empty For this tile unable to select any random Mesh "));}
		return DefaultSpawnable;
	}
	
	int RandomMESH = FMath::RandRange(0,InTile->AllocatedSpawnables.Num()-1 );
	USpawnable* SelectedSpawnable = InTile->AllocatedSpawnables[RandomMESH];
	return SelectedSpawnable;
}

void UCoreSpawner::AddInstanceMesh(UTile* InSelectedTile)
{
	InSelectedTile->SelectedSpawnable = RandomSpawnableFromAvailableSpawnable(InSelectedTile);
	if(InSelectedTile->SelectedSpawnable->GetMesh() ==nullptr  )
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Instance Add Failedd Selected Tile Didint have any Selected  Mesh "));}
		return;
	}
		FTransform SpawnTransform ;
		SpawnTransform.SetLocation(InSelectedTile->World_Location);
		InSelectedTile->SelectedSpawnable->AddInstance(SpawnTransform);
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green,  TEXT(" INSTANCE ADING DONE "));}
}

void UCoreSpawner::UpdateCollapsedTileData(UTile* inTile, TArray<UTile*>* inRemainingTiles,
	TArray<UTile*>* inTotalCollapsedTile)
{

	
	inTile->SetCollapseStatus(EcollapseStatus::Collapsed);
	inRemainingTiles->Remove(inTile);
	inTotalCollapsedTile->Add(inTile);
}

void UCoreSpawner::UpdateSurroundingMesh(UTile* SelectedTile, TArray<UTile*>* InTotalTile)
{
	FVector2D Position2D = SelectedTile->Position_2D;
	//Left
	if(Position2D.Y-1 >=1 )
	{
		FVector2D Pos (Position2D.X,Position2D.Y-1);
		UTile* LeftNeighbour  = GetTileByPosition2D(Pos,InTotalTile);
		UpdateAvailableMesh_Left(SelectedTile,LeftNeighbour);
	}


	//Right
	if(Position2D.Y+1 <=Map_Width )
	{
		
		FVector2D Pos (Position2D.X,Position2D.Y+1);
		UTile* RightNeighbour  = GetTileByPosition2D(Pos,InTotalTile);
		UpdateAvailableMesh_Right(SelectedTile,RightNeighbour);
	}
	//Up
	if(Position2D.X+1 <=Map_Height )
	{
		
		FVector2D Pos (Position2D.X+1,Position2D.Y);
		UTile* UpNeighbour  = GetTileByPosition2D(Pos,InTotalTile);
		UpdateAvailableMesh_Up(SelectedTile,UpNeighbour);
	}
	//Down
	if(Position2D.X-1 >=1 )
	{
		
		FVector2D Pos (Position2D.X-1,Position2D.Y);
		UTile* DownNeighbour  = GetTileByPosition2D(Pos,InTotalTile);
		UpdateAvailableMesh_Down(SelectedTile,DownNeighbour);
	}
	/*
		//Left UP
	if(Position2D.Y-1 >=1 &&  Position2D.X+1 <=Map_Height)
	{
		FVector2D Pos (Position2D.X+1,Position2D.Y-1);
		UTile* LeftUpNeighbour  = GetTileByPosition2D(Pos,InTotalTile);
		UpdateAvailableMesh_LeftUp(SelectedTile,LeftUpNeighbour);
	}
	//Left Down
	if(Position2D.Y-1 >=1  && Position2D.X-1 >=1)
	{
		FVector2D Pos (Position2D.X-1,Position2D.Y-1);
		UTile* LeftDownNeighbour  = GetTileByPosition2D(Pos,InTotalTile);
		UpdateAvailableMesh_LeftDown(SelectedTile,LeftDownNeighbour);
	}*/
	/*//Right Up
	if(Position2D.Y+1 <=Map_Width  &&  Position2D.X+1 <=Map_Height)
	{
		
		FVector2D Pos (Position2D.X+1,Position2D.Y+1);
		UTile* RightUpNeighbour  = GetTileByPosition2D(Pos,InTotalTile);
		UpdateAvailableMesh_RightUp(SelectedTile,RightUpNeighbour);
	}
	//Right Down
	if(Position2D.Y+1 <=Map_Width  && Position2D.X-1 >=1 )
	{
		
		FVector2D Pos (Position2D.X-1,Position2D.Y+1);
		UTile* RightDownNeighbour  = GetTileByPosition2D(Pos,InTotalTile);
		UpdateAvailableMesh_RightDown(SelectedTile,RightDownNeighbour);
	}**

}*/
/*
void UCoreSpawner::UpdateAvailableMesh_Left(UTile* SelectedTile, UTile* LeftNeighbour)
{
	TArray<USpawnable*> UpdatedAvailableTileMesh;

	if( LeftNeighbour->CollapseStatus==EcollapseStatus::Collapsed)
	{
		return;
	}
	TArray<USpawnable*> AllSpawnablesLeft = LeftNeighbour->AllocatedSpawnables;
	
	for (USpawnable* LeftSpawnable : AllSpawnablesLeft )
	{
		if (LeftSpawnable == nullptr) {
			continue;
		}

		if (LeftSpawnable->CompatibleMeshTag_Right.HasTag(SelectedTile->SelectedSpawnable->SpawnableTag)) {
			UpdatedAvailableTileMesh.Add(LeftSpawnable);
		}
			
	}
	LeftNeighbour->AllocatedSpawnables =UpdatedAvailableTileMesh;
}

void UCoreSpawner::UpdateAvailableMesh_LeftUp(UTile* SelectedTile, UTile* LeftUpNeighbour)
{
	TArray<USpawnable*> UpdatedAvailableTileMesh;

	if( LeftUpNeighbour->CollapseStatus==EcollapseStatus::Collapsed)
	{
		return;
	}
	TArray<USpawnable*> AllSpawnablesLeftUp = LeftUpNeighbour->AllocatedSpawnables;
	UpdatedAvailableTileMesh.Add(DefaultSpawnable);

	/*
	for (USpawnable* LeftSpawnable : AllSpawnablesLeftUp )
	{
		if (LeftSpawnable == nullptr) {
			continue;
		}

		if (LeftSpawnable->CompatibleMeshTag_Right.HasTag(SelectedTile->SelectedSpawnable->SpawnableTag)) {
			UpdatedAvailableTileMesh.Add(LeftSpawnable);
		}
			
	}**
	LeftUpNeighbour->AllocatedSpawnables =UpdatedAvailableTileMesh;
}

void UCoreSpawner::UpdateAvailableMesh_LeftDown(UTile* SelectedTile, UTile* LeftDownNeighbour)
{
	TArray<USpawnable*> UpdatedAvailableTileMesh;

	if( LeftDownNeighbour->CollapseStatus==EcollapseStatus::Collapsed)
	{
		return;
	}
	TArray<USpawnable*> AllSpawnablesLeftDown = LeftDownNeighbour->AllocatedSpawnables;
	UpdatedAvailableTileMesh.Add(DefaultSpawnable);

	/*
	for (USpawnable* LeftSpawnable : AllSpawnablesLeftUp )
	{
		if (LeftSpawnable == nullptr) {
			continue;
		}

		if (LeftSpawnable->CompatibleMeshTag_Right.HasTag(SelectedTile->SelectedSpawnable->SpawnableTag)) {
			UpdatedAvailableTileMesh.Add(LeftSpawnable);
		}
			
	}**
	LeftDownNeighbour->AllocatedSpawnables =UpdatedAvailableTileMesh;
}

void UCoreSpawner::UpdateAvailableMesh_Right(UTile* SelectedTile, UTile* RightNeighbour)
{
	TArray<USpawnable*> UpdatedAvailableTileMesh;

	if( RightNeighbour->CollapseStatus==EcollapseStatus::Collapsed)
	{
		return;
	}
	TArray<USpawnable*> AllSpawnablesRight = RightNeighbour->AllocatedSpawnables;
	
	for (USpawnable* RightSpawnable : AllSpawnablesRight )
	{
		if (RightSpawnable == nullptr) {
			continue;
		}

		if (RightSpawnable->CompatibleMeshTag_Left.HasTag(SelectedTile->SelectedSpawnable->SpawnableTag)) {
			UpdatedAvailableTileMesh.Add(RightSpawnable);
		}
			
	}
	RightNeighbour->AllocatedSpawnables =UpdatedAvailableTileMesh;
}

void UCoreSpawner::UpdateAvailableMesh_RightUp(UTile* SelectedTile, UTile* RightUpNeighbour)
{
	TArray<USpawnable*> UpdatedAvailableTileMesh;

	if( RightUpNeighbour->CollapseStatus==EcollapseStatus::Collapsed)
	{
		return;
	}
	TArray<USpawnable*> AllSpawnablesRightUp = RightUpNeighbour->AllocatedSpawnables;
	UpdatedAvailableTileMesh.Add(DefaultSpawnable);

	/*
	for (USpawnable* LeftSpawnable : AllSpawnablesLeftUp )
	{
		if (LeftSpawnable == nullptr) {
			continue;
		}

		if (LeftSpawnable->CompatibleMeshTag_Right.HasTag(SelectedTile->SelectedSpawnable->SpawnableTag)) {
			UpdatedAvailableTileMesh.Add(LeftSpawnable);
		}
			
	}**
	RightUpNeighbour->AllocatedSpawnables =UpdatedAvailableTileMesh;
}

void UCoreSpawner::UpdateAvailableMesh_RightDown(UTile* SelectedTile, UTile* RightDownNeighbour)
{
	TArray<USpawnable*> UpdatedAvailableTileMesh;

	if( RightDownNeighbour->CollapseStatus==EcollapseStatus::Collapsed)
	{
		return;
	}
	TArray<USpawnable*> AllSpawnablesRightDown = RightDownNeighbour->AllocatedSpawnables;
	UpdatedAvailableTileMesh.Add(DefaultSpawnable);

	/*
	for (USpawnable* LeftSpawnable : AllSpawnablesLeftUp )
	{
		if (LeftSpawnable == nullptr) {
			continue;
		}

		if (LeftSpawnable->CompatibleMeshTag_Right.HasTag(SelectedTile->SelectedSpawnable->SpawnableTag)) {
			UpdatedAvailableTileMesh.Add(LeftSpawnable);
		}
			
	}**
	RightDownNeighbour->AllocatedSpawnables =UpdatedAvailableTileMesh;
}

void UCoreSpawner::UpdateAvailableMesh_Up(UTile* SelectedTile, UTile* UpNeighbour)
{
	TArray<USpawnable*> UpdatedAvailableTileMesh;

	if( UpNeighbour->CollapseStatus==EcollapseStatus::Collapsed)
	{
		return;
	}
	TArray<USpawnable*> AllSpawnablesUp = UpNeighbour->AllocatedSpawnables;
	
	for (USpawnable* UpSpawnable : AllSpawnablesUp )
	{
		if (UpSpawnable == nullptr) {
			continue;
		}

		if (UpSpawnable->CompatibleMeshTag_Down.HasTag(SelectedTile->SelectedSpawnable->SpawnableTag)) {
			UpdatedAvailableTileMesh.Add(UpSpawnable);
		}
			
	}
	UpNeighbour->AllocatedSpawnables =UpdatedAvailableTileMesh;
}

void UCoreSpawner::UpdateAvailableMesh_Down(UTile* SelectedTile, UTile* DownNeighbour)
{
	TArray<USpawnable*> UpdatedAvailableTileMesh;

	if( DownNeighbour->CollapseStatus==EcollapseStatus::Collapsed)
	{
		return;
	}
	TArray<USpawnable*> AllSpawnablesUp = DownNeighbour->AllocatedSpawnables;
	
	for (USpawnable* DownSpawnable : AllSpawnablesUp )
	{
		if (DownSpawnable == nullptr) {
			continue;
		}

		if (DownSpawnable->CompatibleMeshTag_Up.HasTag(SelectedTile->SelectedSpawnable->SpawnableTag)) {
			UpdatedAvailableTileMesh.Add(DownSpawnable);
		}
			
	}
	DownNeighbour->AllocatedSpawnables =UpdatedAvailableTileMesh;
}


UTile* UCoreSpawner::ReturnTileWithLowestEntropy(TArray<UTile*>* inTotalTiles)
{
	UTile*LowestEntropyTile =DefaultTile;
	bool bfirst = true ;
	bIsGenSaturated =true;
	for(int i = inTotalTiles->Num()-1 ; i >= 0 ; i-- )
	{
		UTile* tile = (*inTotalTiles)[i];
		if(tile->CollapseStatus ==EcollapseStatus::Collapsed)
		{
			continue;
		}
		if( tile->AllocatedSpawnables.Num() <=0 )
		{
			tile->bIsSaturated  =true;
			RemainingTiles.Remove(tile);
			SaturatedTiles.Add(tile);
			continue;
		}
		
		if(bfirst)
		{
			LowestEntropyTile = tile;
			bfirst=false;
			bIsGenSaturated =false;
			continue;
		}
		if(tile->AllocatedSpawnables.Num()< LowestEntropyTile->AllocatedSpawnables.Num())
		{
			LowestEntropyTile = tile;
			bIsGenSaturated=false;
		}
	}
	
	return LowestEntropyTile;
}

UTile* UCoreSpawner::GetTileByID(int ID, TArray<UTile*>* inTotalTiles)
{
	for (UTile* Tile : *inTotalTiles)
	{
		if(Tile->ID==ID)
			return  Tile ;
	}
	//return &DefaultTile;
	return nullptr;
}

UTile* UCoreSpawner::GetTileByPosition2D(FVector2D Pos, TArray<UTile*>* inTotalTiles)
{
	int32 index = ((Pos.Y - 1) * Map_Height) + (Pos.X - 1);
	return (*inTotalTiles) [index];
}

void UCoreSpawner::WaveFunctionCollapse()
{
	//Adding RemainingTile To All Tile
	RemainingTiles.Reserve(TotalTiles->Num());
	for(UTile* Tile : *TotalTiles)
		
	{
		RemainingTiles.Add(Tile)  ;
	}

	// FIRST RANDOM ID FROM STREAM
	Stream.GenerateNewSeed();
	int FirstIndices =  UKismetMathLibrary::RandomIntegerFromStream(RemainingTiles.Num()-1,Stream);
	
	//Pick A Random Tile	//For the first time choose from stream
	UTile* FirstRandomTile = RemainingTiles[FirstIndices];

	// ADDING INSTANCE OF THE SELECTED MESH
	AddInstanceMesh(FirstRandomTile);

	//Update  Collapsed Tile Data
	UpdateCollapsedTileData(FirstRandomTile,&RemainingTiles,&CollapsedTiles);

	UpdateSurroundingMesh(FirstRandomTile,&RemainingTiles);

	while (!RemainingTiles.IsEmpty())
	{
		// CHOOSE A TILE DEPENDING ENTROPY OF THE TILE
		UTile* Tile = ReturnTileWithLowestEntropy(&RemainingTiles);
		if(bIsGenSaturated)
			break;
		AddInstanceMesh(Tile);
		UpdateCollapsedTileData(Tile,&RemainingTiles,&CollapsedTiles);
		UpdateSurroundingMesh(Tile,&RemainingTiles);
	}
	/*
	for (UTile*tile :SaturatedTiles)
	{
		tile->SelectedTiledMesh=DefaultTileMesh;
		tile->CollapseStatus =EcollapseStatus::Collapsed;
		FTransform Transform;
		Transform.SetLocation(tile->World_Location);
		tile->SelectedTiledMesh =DefaultTileMesh;
		DefaultTileMesh->InstancedMesh->AddInstance(Transform);
		
	}**
	
}



bool UCoreSpawner::Run()
{
	if (!TotalTiles->IsEmpty() && !TotalSpawnables->IsEmpty())
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT(" BOTH TILE AND TOTAL MESH AVAILABLE WAVE FUNCTION CALLING  "));
		}

		// STARTING THE MAIN ALGORITHM
		WaveFunctionCollapse();
		return true;
	}
	else
	{
		// error occurred, display an error message
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Could not generate tile or total mesh Aborting."));
		}
		return false;
	}
}*/
