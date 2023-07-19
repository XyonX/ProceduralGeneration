// Fill out your copyright notice in the Description page of Project Settings.


#include "GridSection.h"
#include "GridComponent.h"


void UGridSection::Init(AActor* InOwner,int32 InIndex, TArray<FVector>& InVerticesRef, FVector2D InSectionSize, FVector2D InComponentSize, FVector2D InQuadDensity,
	TArray<int32>InSectionIndices , UProceduralMeshComponent*InPMC , FVector2D InNumOfComponents , UMaterialInterface*InMaterial)
{
	SectionSize=InSectionSize;
	ComponentSize=InComponentSize;
	QuadDensity_Lod0=InQuadDensity;
	//SectionVertices=InSectionVertices;
	VerticesRef=InVerticesRef;
	SectionIndices=InSectionIndices;
	NumOfComponents = InSectionSize/InComponentSize;
	ProceduralMeshComponent=InPMC;
	Index=InIndex;
	Owner=InOwner;
	DefaultMaterial=InMaterial;
	
	Bounds.Min=FVector ( Center.X-SectionSize.X/2 , Center.Y-SectionSize.Y/2,Center.Z);
	Bounds.Max=FVector ( Center.X+SectionSize.X/2 , Center.Y+SectionSize.Y/2,Center.Z);

	int NumVertexPerSection_X = ((SectionSize.X/100) *QuadDensity_Lod0.X)+1;
	int NumVertexPerSection_Y = ((SectionSize.Y/100) *QuadDensity_Lod0.Y)+1;
	int NumVertexPerComponent_X = ((ComponentSize.X/100) *QuadDensity_Lod0.X)+1;
	int NumVertexPerComponent_Y = ((ComponentSize.Y/100) *QuadDensity_Lod0.Y)+1;
	int  Componentindex =0;
	for (int YthComp =0 ; YthComp < NumOfComponents.Y ; YthComp++)
	{
		for (int XthComp =0 ; XthComp < NumOfComponents.X ; XthComp++)
		{

			Componentindex++;
			UGridComponent*GridComp = NewObject<UGridComponent>(Owner);
			FVector CompLoc = FVector(XthComp*ComponentSize.X,YthComp*ComponentSize.Y,0);
			GridComp->LocalIndex=Componentindex;
			GridComp->WorldLocation=CompLoc;

			int GlobPos_X = (Pos2D.X*NumOfComponents.X)+XthComp;
			int GlobPos_Y = (Pos2D.Y*NumOfComponents.Y)+YthComp;
			
			GridComp->GlobalPos2D=FVector2D(GlobPos_X,GlobPos_Y);
			GridComp->LocalPos2D= FVector2D(XthComp,YthComp);
			
			GridComp->GlobalIndex= (GlobPos_Y*NumOfComponents.X)+GlobPos_X;
			

			DrawDebugString(GetWorld(),WorldLocation,FString::Printf(TEXT("%f ,%f"),CompLoc.X,CompLoc.Y));

			int CompStartY =(YthComp*(ComponentSize.Y/100)*QuadDensity_Lod0.Y);
			int  CompEndY =((YthComp+1)*(ComponentSize.Y/100)*QuadDensity_Lod0.Y);
			int  CompStartX =(XthComp*(ComponentSize.X/100)*QuadDensity_Lod0.X);
			int CompEndX =((XthComp+1)*(ComponentSize.X/100)*QuadDensity_Lod0.X);
			

			//TArray<TArrayView<const FVector>>VerticesArray;
			TArray<int32>Triangles;
			TArray<FVector>Normals;
			
			for (int InComponentY =CompStartY ; InComponentY <=CompEndY;InComponentY++ )
			{
				for (int InComponentX =CompStartX ; InComponentX <=CompEndX;InComponentX++ )
				{
					
					FVector Normal = FVector (0.0f,0.0f,1.0f);
					
					//VerticesArray.Add(VectorRef);
					Normals.Add(Normal);

					//Calculate Triangle
					

					if( InComponentY<CompEndY-1 && InComponentX <CompEndX-1)
					{
						int Ind = (InComponentY*NumVertexPerSection_X)+InComponentX;
						
						int32 A =SectionIndices[Ind] ;
						int32 B = SectionIndices[((InComponentY+1)*NumVertexPerSection_X)+InComponentX];
						int32 C =SectionIndices[B+1];
						int32 D =SectionIndices[A+1];

						Triangles.Add(A);
						Triangles.Add(B);
						Triangles.Add(C);

						Triangles.Add(C);
						Triangles.Add(D);
						Triangles.Add(A);
					}
				}
			}
			GridComp->Init(VerticesRef,ProceduralMeshComponent,Triangles,Normals,Componentindex*Index,DefaultMaterial);
			SectionComponents.Add(FVector2D(YthComp,XthComp),GridComp);
		}
	}
}