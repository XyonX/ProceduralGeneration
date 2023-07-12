

#include "CoreGenerator.h"
#include "ProceduralGeneration/Tiles/Tile.h"


UCoreGenerator::UCoreGenerator()
{

	TileSize=FVector2D(4,4);
}

UCoreGenerator::~UCoreGenerator()
{
	for (int32 i = Grid.Num() - 1; i >= 0; i--)
	{
		UTile* Tile = Grid[i];
		Tile->ConditionalBeginDestroy();
		Grid.RemoveAt(i);
	}
	Grid.Empty();

}

TArray<UTile*>* UCoreGenerator::Run( )
{

	FVector2D TileDimension = ConfigureTileSize();

	GenerateTile( GridSize ,TileDimension,Grid );

	return  &Grid;
}

FVector2D UCoreGenerator::ConfigureTileSize()
{
	return TileSize;
}

bool UCoreGenerator::GenerateTile(FVector2D InGridSize ,FVector2D InTileSize , TArray<UTile*>&OutGrid)
{
	int id=0;
	for (int Y = 0 ; Y<  InGridSize.Y ; Y++)
	{
		for (int X = 0 ; X< InGridSize.X ; X++)
		{
			
			id++;
			FVector2D POS(X,Y);
			
			// create a new instance of UTile with NewObject
			UTile* Tile = NewObject<UTile>();
			
			//Tile->Init(id, POS,UnscaledLoc, in_SpawnableContainer);


			OutGrid.Add(Tile);
			
		}
	}
	return true;
}