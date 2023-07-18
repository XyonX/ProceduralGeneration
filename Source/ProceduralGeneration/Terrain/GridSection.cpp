// Fill out your copyright notice in the Description page of Project Settings.


#include "GridSection.h"
#include "GridComponent.h"


void UGridSection::Init(AActor* Owner, FVector2D InSectionSize, FVector2D InComponentSize, FVector2D InQuadDensity,
	TArray<TArrayView<const FVector>> InSectionVertices)
{
	SectionSize=InSectionSize;
	ComponentSize=InComponentSize;
	QuadDensity_Lod0=InQuadDensity;
	SectionVertices=InSectionVertices;
	NumOfComponents = InSectionSize/InComponentSize;
	
	Bounds.Min=FVector ( Center.X-SectionSize.X/2 , Center.Y-SectionSize.Y/2,Center.Z);
	Bounds.Max=FVector ( Center.X+SectionSize.X/2 , Center.Y+SectionSize.Y/2,Center.Z);

	int NumVertexPerSection_X = ((SectionSize.X/100) *QuadDensity_Lod0.X)+1;
	for (int YthComp =0 ; YthComp < NumOfComponents.Y ; YthComp++)
	{
		for (int XthComp =0 ; XthComp < NumOfComponents.X ; XthComp++)
		{

			UGridComponent*GridComp = NewObject<UGridComponent>(Owner);
			FVector CompLoc = FVector(XthComp*ComponentSize.X,YthComp*ComponentSize.Y,0);
			GridComp->WorldLocation=CompLoc;

			DrawDebugString(GetWorld(),WorldLocation,FString::Printf(TEXT("%f ,%f"),CompLoc.X,CompLoc.Y));

			int CompStartY =(YthComp*(ComponentSize.Y/100)*QuadDensity_Lod0.Y);
			int  CompEndY =((YthComp+1)*(ComponentSize.Y/100)*QuadDensity_Lod0.Y);
			int  CompStartX =(XthComp*(ComponentSize.X/100)*QuadDensity_Lod0.X);
			int CompEndX =((XthComp+1)*(ComponentSize.X/100)*QuadDensity_Lod0.X);
			

			TArray<TArrayView<const FVector>>ComponentArray;
			for (int InComponentY =CompStartY ; InComponentY <=CompEndY;InComponentY++ )
			{
				for (int InComponentX =CompStartX ; InComponentX <=CompEndX;InComponentX++ )
				{
					//take the vector ref from the main vertices array and put it to the section array container
					int Ind = (InComponentY*NumVertexPerSection_X)+InComponentX;
					TArrayView<const FVector> VectorRef= SectionVertices[Ind];
					ComponentArray.Add(VectorRef);
				}
			}
			GridComp->ComponentVertices = ComponentArray;
			SectionComponents.Add(FVector2D(YthComp,XthComp),GridComp);
		}
	}
}