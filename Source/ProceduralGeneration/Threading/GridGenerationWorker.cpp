/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/


#include "GridGenerationWorker.h"

#include "ProceduralGeneration/Terrain/GridSection.h"

UGridGenerationWorker::UGridGenerationWorker()
{
}

bool UGridGenerationWorker::Init()
{
	return FRunnable::Init();
}

uint32 UGridGenerationWorker::Run()
{
	GenerateMeshSections();
	return 0;
}

void UGridGenerationWorker::Stop()
{
	FRunnable::Stop();
}

void UGridGenerationWorker::Exit()
{
	FRunnable::Exit();
}

void UGridGenerationWorker::SetParameters(UCoreGenerator* InGenerator)
{
	Generator=InGenerator;
}

void UGridGenerationWorker::GenerateMeshSections()
{
	if(Generator==nullptr)
	{
		return;
	}
	FVector2D NumOfSection=Generator->GetNumOfSections();
	FVector2D SectionSize = Generator->GetSectionSize();
	FVector2D QuadDensity_Lod0 = Generator->GetQuadDensity();
	int32 SectionIndex =0;
	AActor* Owner = Generator->GetOwner();
	for (int32 SecY =0 ;SecY<NumOfSection.Y ; SecY++)
	{
		for(int32 SecX =0 ;SecX<NumOfSection.X ; SecX++)
		{
			SectionIndex++;
			UGridSection*Section =NewObject<UGridSection>(Owner);
			Section->Index=SectionIndex;

			FVector2D Pos2D = FVector2D(SecX,SecY);
			FVector WorldLocation = FVector (SecX*SectionSize.X,SecY*SectionSize.Y,0);
			Section->Pos2D =Pos2D;
			Section->WorldLocation =WorldLocation;
			Section->Center =WorldLocation+FVector(SectionSize.X/2,SectionSize.Y/2,0);

			int SecStartY =(SecY*(SectionSize.Y/100)*QuadDensity_Lod0.Y);
			int  SecEndY =((SecY+1)*(SectionSize.Y/100)*QuadDensity_Lod0.Y);
			int  SecStartX =(SecX*(SectionSize.X/100)*QuadDensity_Lod0.X);
			int SecEndX =((SecX+1)*(SectionSize.X/100)*QuadDensity_Lod0.X);

			Section->Init(Owner,SectionIndex,Generator->GetVertices(),SectionSize,Generator->GetComponentSize(),QuadDensity_Lod0,Generator->GetPMC(),Generator->GetNumVertsLod0(),Generator->GetDefaultMaterial());
			Generator->AddSectionToGrid(Section);
		}
	}
}
