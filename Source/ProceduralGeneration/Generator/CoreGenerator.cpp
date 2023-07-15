

#include "CoreGenerator.h"

#include "Kismet/KismetMathLibrary.h"
#include "ProceduralGeneration/Tiles/Tile.h"


UCoreGenerator::UCoreGenerator()
{

	GridSize=FVector2D(4,4);
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
	Owner = GetTypedOuter<AActor>();
	if (Owner == nullptr)
	{
		return nullptr;
	}

	ConfigureGrid();
	GenerateGrid( GridSize ,Grid );

	return  DynamicGirdSection;
}

bool UCoreGenerator::Init(FGridData GridData)
{
	HeightMapPath=GridData.HeightMapFilePath;
    Origin=GridData.CustomOrigin;
	Center=Origin+FVector(GridSize.X/2,GridSize.Y/2,0);
	QuadDensity_Lod0 = GridData.QuadDensity_Lod0;
	
	if(GridData.GridSize.X == GridData.GridSize.Y)
	{
		GridSize=GridData.GridSize;
	}
	else if (GridData.GridSize.X < GridData.GridSize.Y)
	{
		GridSize=FVector2D( GridData.GridSize.Y ,GridData.GridSize.Y) ;
	}
	else
	{
		GridSize=FVector2D( GridData.GridSize.X ,GridData.GridSize.X) ;
	}



/*

	VertexDensity_Lod0 = UKismetMathLibrary::Sqrt(QuadDensity_Lod0);

	NumVertsX_Lod0 = static_cast<int32>((GridSize.X / 100) * VertexDensity_Lod0);
	NumVertsY_Lod0 = static_cast<int32>((GridSize.Y / 100) * VertexDensity_Lod0);

	QuadDensity_Lod1 = GridData.QuadDensity_Lod1;
	VertexDensity_Lod1 = UKismetMathLibrary::Sqrt(QuadDensity_Lod1);

	NumVertsX_Lod1 = static_cast<int32>((GridSize.X / 100) * VertexDensity_Lod1);
	NumVertsY_Lod1 = static_cast<int32>((GridSize.Y / 100) * VertexDensity_Lod1);*/

	return true;
}

FVector2D UCoreGenerator::ConfigureGrid()
{
	SectionSize=FVector2D(100'00,10'000);
	if(GridSize.X < SectionSize.X && GridSize.Y < SectionSize.Y )
	{
		GridSize =SectionSize;
	}
	NumOfSection = GridSize/SectionSize;
	ComponentSize =FVector2D(25'00,25'00);
	NumOfComponentsPerSection =SectionSize/ComponentSize;
	
	NumVerts_Lod0 =GridSize*QuadDensity_Lod0;
	NumQuadsPerSection_Lod0 = SectionSize*QuadDensity_Lod0;

	NumVerts_Lod0 =GridSize*QuadDensity_Lod1;
	NumQuadsPerSection_Lod0 = SectionSize*QuadDensity_Lod1;


	
	return NumOfSection;
}

bool UCoreGenerator::GenerateGrid(FVector2D InGridSize, TArray<UGridSection*>& OutGrid)
{
	int index=0;
	for (int Y = 0 ; Y<  NumVerts_Lod0.Y ; Y++)
	{
		for (int X = 0 ; X<NumVerts_Lod0.X ; X++)
		{
			float Height = HeightMap[(Y*NumVerts_Lod0.X)+X];
			FVector Location = FVector((X+Center.X),(Y+Center.Y),(Height+Center.Z));
			Vertices.Add(Location);
		}
	}
	return true;
}

TArray<UGridSection*>* UCoreGenerator::ConfigureGridSections()
{
	int NumOfVertsPerSection_X =NumVerts_Lod0.X /NumOfSection.X;
	int NumOfVertsPerSection_Y =NumVerts_Lod0.Y /NumOfSection.Y;
	int32 Index =0;
	for (int32 SecY =0 ;SecY<NumOfSection.Y ; SecY++)
	{
		for(int32 SecX =0 ;SecX<NumOfSection.X ; SecX++)
		{
			Index++;
			UGridSection*Section =NewObject<UGridSection>(Owner);
			Section->Index=Index;
			FVector WorldLocation=FVector(SecY*NumOfVertsPerSection_Y,SecX*NumOfVertsPerSection_X,0);
			Section->WorldLocation =WorldLocation;
			Section->Center =WorldLocation+FVector(NumOfVertsPerSection_X/2,NumOfVertsPerSection_Y/2,0);
			
			int SecStartY =SecY*NumOfVertsPerSection_Y;
			int SecEndY =(SecY+1)*NumOfVertsPerSection_Y;
			int SecStartX =SecX*NumOfVertsPerSection_X;
			int SecEndX =(SecX+1)*NumOfVertsPerSection_X;

			

			 TArray<TArrayView<const FVector>>ArrayReference;
			for (int  InSecY =SecStartY ; InSecY < SecEndY ; InSecY++)
			{
				for(int InSecX=SecStartX ; InSecX<SecEndX  ; InSecX++)
				{
					//take the vector ref from the main vertices array and put it to the section array container
					const FVector& Vector = Vertices[(InSecY*NumVerts_Lod0.X)+InSecX];
					TArrayView<const FVector> VectorReference(&Vector, 1);
					ArrayReference.Add(VectorReference);
					
				}
			}
			Section->Init(Owner,NumQuadsPerComponent_Lod0,NumOfComponentsPerSection,ArrayReference);
			Grid.Add(Section);
		}
	}
	
	return &Grid;
}

void UCoreGenerator::Receiver_OnCharacterMovement(FVector CharacterLocation)
{

	
	
}
