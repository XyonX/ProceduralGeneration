// Fill out your copyright notice in the Description page of Project Settings.


#include "RuntimeAppearanceEditor.h"
#include "KismetProceduralMeshLibrary.h"


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
	UKismetProceduralMeshLibrary::CopyProceduralMeshFromStaticMeshComponent(InSMC,0,OutPMC,false);
	if(OutPMC ==nullptr)
	{
		return false;
	}
	return true;
	
}

void ARuntimeAppearanceEditor::ExtractMeshSectionStaticMeshComponent()
{
	//It Returns A MeshSection from the PMC
	PMS_FullBody= CharacterProceduralMesh->GetProcMeshSection(0);


	
	UKismetProceduralMeshLibrary::GetSectionFromStaticMesh(CharacterMesh,0,Index,Vertices,Triangles,Normals,UVs,Tangents);

	

	CharacterMesh->GetVertexColorData(VertexColorData);

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
	
	
	CharacterProceduralMesh->GetProcMeshSection(0);
}

