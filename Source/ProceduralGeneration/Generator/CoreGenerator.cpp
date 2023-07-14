

#include "CoreGenerator.h"

#include "Kismet/KismetMathLibrary.h"
#include "ProceduralGeneration/Tiles/Tile.h"


UCoreGenerator::UCoreGenerator()
{

	GridSize=FVector2D(4,4);
	TileSize=FVector2D(1000.f,1000.f);
}

UCoreGenerator::~UCoreGenerator()
{
/*
	for (int32 i = Grid.Num() - 1; i >= 0; i--)
	{
		UTile* Tile = Grid[i];
		Tile->ConditionalBeginDestroy();
		Grid.RemoveAt(i);
	}
	Grid.Empty();*/

}

UGridSection* UCoreGenerator::Run( )
{
	AActor* Owner = GetTypedOuter<AActor>();
	if (Owner == nullptr)
	{
		return nullptr;
	}

	FVector2D TileDimension = ConfigureGrid();
	GenerateGrid( GridSize ,TileDimension,Grid );

	return  DynamicGirdSection;
}

bool UCoreGenerator::Init(FGridData GridData)
{
	GridSize=GridData.GridSize;
	GridType=GridData.GridType;
	TileSize=GridData.TileSize;
	NumOfSection=GridData.NumOfSection;
	HeightMapPath=GridData.HeightMapFilePath;
	Origin=GridData.CustomOrigin;

	Center=Origin+FVector(GridSize.X/2,GridSize.Y/2,0);

	QuadDensity_Lod0 = GridData.QuadDensity_Lod0;
	VertexDensity_Lod0 = UKismetMathLibrary::Sqrt(QuadDensity_Lod0);

	NumVertsX_Lod0 = static_cast<int32>((GridSize.X / 100) * VertexDensity_Lod0);
	NumVertsY_Lod0 = static_cast<int32>((GridSize.Y / 100) * VertexDensity_Lod0);

	QuadDensity_Lod1 = GridData.QuadDensity_Lod1;
	VertexDensity_Lod1 = UKismetMathLibrary::Sqrt(QuadDensity_Lod1);

	NumVertsX_Lod1 = static_cast<int32>((GridSize.X / 100) * VertexDensity_Lod1);
	NumVertsY_Lod1 = static_cast<int32>((GridSize.Y / 100) * VertexDensity_Lod1);

	return true;
}

FVector2D UCoreGenerator::ConfigureGrid()
{
	return TileSize;
}

bool UCoreGenerator::GenerateGrid(FVector2D InGridSize, FVector2D InTileSize, TArray<UGridSection*>& OutGrid)
{
	int index=0;
	for (int Y = 0 ; Y<  NumVertsY_Lod0 ; Y++)
	{
		for (int X = 0 ; X<NumVertsX_Lod0 ; X++)
		{
			float Height = HeightMap[(Y*NumVertsX_Lod0)+X];
			FVector Location = FVector((X+Center.X),(Y+Center.Y),(Height+Center.Z));
			Vertices.Add(Location);
		}
	}
	return true;
}

TArray<UGridSection*>* UCoreGenerator::ConfigureGridSection()
{
	int SectionSize_X =GridSize.X/NumOfSection.X;
	int SectionSize_Y =GridSize.Y/NumOfSection.Y;
	int32 Index =0;
	for (int32 SecY =0 ;SecY<NumOfSection.Y ; SecY++)
	{
		for(int32 SecX =0 ;SecX<NumOfSection.X ; SecX++)
		{
			Index++;
			UGridSection*Section =NewObject<UGridSection>(Owner);
			Section->Index=Index;
			FVector WorldLocation=FVector(SecY,SecX*SectionSize_X,0);
			Section->WorldLocation =WorldLocation;
			Section->Center =WorldLocation+FVector(SectionSize_X/2,SectionSize_Y/2,0);

			TArray<FVector>Verts;
			int SecStartY =SecY*(NumVertsY_Lod0/NumOfSection.Y);
			int SecEndY =(SecY+1)*(NumVertsY_Lod0/NumOfSection.Y);
			for (int  SecY*VertsY =0 ; VertsY < SecEndY ; VertsY++)
			{
				int SecStartX =SecX*(NumVertsX_Lod0/NumOfSection.X);
				int SecEndX =(SecX+1)*(NumVertsX_Lod0/NumOfSection.X);
				for(int VertsX=0 ; VertsX< SectionSize_X ; VertsX++)
				{
					Verts
				}
			}
			Grid.Add(Section);
		}
	}
}

void UCoreGenerator::Receiver_OnCharacterMovement(FVector CharacterLocation)
{

	
	
}
