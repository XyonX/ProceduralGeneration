// Fill out your copyright notice in the Description page of Project Settings.


#include "GridComponent.h"



void UGridComponent::Init(TArray<FVector>& InVerticesRef, UProceduralMeshComponent* InProceduralMeshComponent,
	TArray<int32> InTriangles, TArray<FVector> InNormals , int32 InGlobalIndex ,UMaterialInterface* InMaterial)
{
	GlobalIndex=InGlobalIndex;
	ProceduralMesh=InProceduralMeshComponent;
	Triangles=InTriangles;
	Normals=InNormals;
	VerticesRef=InVerticesRef;
	DefaultMaterial=InMaterial;

	GenerateMeshSection();
}

bool UGridComponent::GenerateMeshSection()
{
	if(ProceduralMesh==nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,TEXT("Proc Mesh Not Found"),true);
		return false;
		
	}

	// Create the mesh section
	ProceduralMesh->CreateMeshSection(GlobalIndex, VerticesRef, Triangles, Normals, TArray<FVector2D>(), TArray<FColor>(), TArray<FProcMeshTangent>(), true);

	if(DefaultMaterial)
	{
		// Set the default material for the mesh section
		ProceduralMesh->SetMaterial(GlobalIndex, DefaultMaterial);
	}


	
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,TEXT("Mesh Section Created"),true);
	return true;
}
