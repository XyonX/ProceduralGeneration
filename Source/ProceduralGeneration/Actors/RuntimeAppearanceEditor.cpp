/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/


#include "RuntimeAppearanceEditor.h"
#include "KismetProceduralMeshLibrary.h"
//#include "Rendering/SkeletalMeshRenderData.h"
//#include "Rendering/SkinWeightVertexBuffer.h"


// Sets default values
ARuntimeAppearanceEditor::ARuntimeAppearanceEditor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARuntimeAppearanceEditor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARuntimeAppearanceEditor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ARuntimeAppearanceEditor::ConvertStaticMeshToProceduralMesh(UStaticMeshComponent* InSMC, UProceduralMeshComponent* OutPMC)
{
	/*
	UKismetProceduralMeshLibrary::CopyProceduralMeshFromStaticMeshComponent(InSMC,0,OutPMC,false);
	if(OutPMC ==nullptr)
	{
		return false;
	}*/
	return true;
	
}

void ARuntimeAppearanceEditor::ExtractMeshSectionStaticMeshComponent()
{
	/*
	//It Returns A MeshSection from the PMC
	PMS_FullBody= CharacterProceduralMesh->GetProcMeshSection(0);
	
	UKismetProceduralMeshLibrary::GetSectionFromStaticMesh(CharacterMesh,0,Index,Vertices,Triangles,Normals,UVs,Tangents);

	//CharacterMesh->GetVertexColorData(VertexColorData);
	//FStaticMeshLODResources& LODResource= CharacterMesh->GetRenderData()->LODResources;

	FSkeletalMeshRenderData*RenderData= CharacterSkeletalMesh->GetSkeletalMeshRenderData();
	FSkeletalMeshLODRenderData& SkeletalMeshRenderData =  RenderData->LODRenderData[0];

	if(SkeletalMeshRenderData.SkinWeightVertexBuffer.GetNumVertices() >0)
	{
		TArray<FSkinWeightInfo> SkinWeights;
		SkeletalMeshRenderData.SkinWeightVertexBuffer.GetSkinWeights(SkinWeights);

		for (int32 VertexIndex = 0; VertexIndex < SkinWeights.Num(); ++VertexIndex)
		{
			const FSkinWeightInfo& SkinWeight = SkinWeights[VertexIndex];

			// Process the bone influences as needed
			for (int32 InfluenceIndex = 0; InfluenceIndex < MAX_TOTAL_INFLUENCES ; ++InfluenceIndex)
			{
				uint32 BoneIndex = SkinWeight.InfluenceBones[InfluenceIndex];
				float Weight = SkinWeight.InfluenceWeights[InfluenceIndex];

				// Do something with the bone index and weight
			}
			
		}

	}*/
/*
	for(auto& Pair : VertexColorData)
	{
		switch (Pair.Value)
		{
		case Head :
			{
				Vertices_Head.Add(Pair.Key);
				break;
			}
		case Torso:
			{
				Vertices_Torso.Add(Pair.Key);
				break;
			}
		case Arms:
			{
				Vertices_Arms.Add(Pair.Key);
				break;
			}
		case Legs:
			{
				Vertices_Legs.Add(Pair.Key);
				break;
			}
		case Hands:
			{
				Vertices_Hands.Add(Pair.Key);
				break;
			}
		case Feet:
			{
				Vertices_Feet.Add(Pair.Key);
				break;
			}
			default:
				
				continue;
			
	}

		
	CharacterProceduralMesh->GetProcMeshSection(0);*/
}

