/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/


#include "GridSection.h"
#include "GridComponent.h"


void UGridSection::Init(AActor* InOwner,int32 InIndex, TArray<FVector>& InVerticesRef, FVector2D InSectionSize, FVector2D InComponentSize, FVector2D InQuadDensity
	, UProceduralMeshComponent*InPMC  ,FVector2D InNumVertex_lod0, UMaterialInterface*InMaterial)
{
	SectionSize=InSectionSize;
	ComponentSize=InComponentSize;
	QuadDensity_Lod0=InQuadDensity;
	VerticesRef=InVerticesRef;
	NumOfComponents = InSectionSize/InComponentSize;
	ProceduralMeshComponent=InPMC;
	Index=InIndex;
	Owner=InOwner;
	DefaultMaterial=InMaterial;
	NumVertexLod0=InNumVertex_lod0;
	
	Bounds.Min=FVector ( Center.X-SectionSize.X/2 , Center.Y-SectionSize.Y/2,Center.Z);
	Bounds.Max=FVector ( Center.X+SectionSize.X/2 , Center.Y+SectionSize.Y/2,Center.Z);

	FVector2D NumVertexPerSection = ((SectionSize/100) *QuadDensity_Lod0)+1;
	FVector2D NumVertexPerComponent = ((ComponentSize/100) *QuadDensity_Lod0)+1;
	int  Componentindex =0;
	FVector2D SectionOffset = Pos2D*(NumVertexPerSection-1);
	
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
			FVector2D CompLocalPos = FVector2D(XthComp,YthComp);
			GridComp->LocalPos2D= CompLocalPos;
			
			GridComp->GlobalIndex= (GlobPos_Y*NumOfComponents.X)+GlobPos_X;
			

			//DrawDebugString(GetWorld(),WorldLocation,FString::Printf(TEXT("%f ,%f"),CompLoc.X,CompLoc.Y));

			
			FVector2D ComponentOffset =(NumVertexPerComponent-1)*CompLocalPos;
			

			int CompStartY =(YthComp*(ComponentSize.Y/100)*QuadDensity_Lod0.Y);
			int  CompEndY =((YthComp+1)*(ComponentSize.Y/100)*QuadDensity_Lod0.Y);
			int  CompStartX =(XthComp*(ComponentSize.X/100)*QuadDensity_Lod0.X);
			int CompEndX =((XthComp+1)*(ComponentSize.X/100)*QuadDensity_Lod0.X);
			
			
			TArray<int32>Triangles;
			TArray<FVector>Normals;

			int32 VertexGlobalIndex;
			for (int InComponentY =CompStartY ; InComponentY <=CompEndY;InComponentY++ )
			{
				for (int InComponentX =CompStartX ; InComponentX <=CompEndX;InComponentX++ )
				{
					

					if( InComponentY<CompEndY && InComponentX <CompEndX)
					{


						FVector2D VerPos_Component = FVector2D(InComponentX,InComponentY);
						FVector2D TotalOffset = SectionOffset;
						FVector2D  VertexGlobalPos2D =VerPos_Component+TotalOffset;
						
						
						VertexGlobalIndex = (VertexGlobalPos2D.Y*NumVertexLod0.X)+VertexGlobalPos2D.X;

						int32 A =(VertexGlobalPos2D.Y*NumVertexLod0.X)+VertexGlobalPos2D.X ;
						int32 B =((VertexGlobalPos2D.Y+1)*NumVertexLod0.X)+VertexGlobalPos2D.X;
						int32 C =B+1;
						int32 D =A+1;
						
						Triangles.Add(A);
						Triangles.Add(B);
						Triangles.Add(C);

						Triangles.Add(C);
						Triangles.Add(D);
						Triangles.Add(A);


						FVector Normal = FVector (0.0f,0.0f,1.0f);
						Normals.Add(Normal);
					}
				}
			}
			GridComp->Init(VerticesRef,ProceduralMeshComponent,Triangles,Normals,VertexGlobalIndex,DefaultMaterial);
			SectionComponents.Add(FVector2D(YthComp,XthComp),GridComp);
		}
	}
}