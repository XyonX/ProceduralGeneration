// Fill out your copyright notice in the Description page of Project Settings.


#include "GridComponent.h"
#include "Materials/MaterialInstanceDynamic.h"



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
		
		UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(DefaultMaterial, this);
		// Set the desired color for the tile
		FLinearColor ColorParameter = FLinearColor::MakeRandomColor();
		//ColorParameter.A =0.1;
		DynMaterial->SetVectorParameterValue("Base_Color", ColorParameter);
		FVector OPCT =FVector(1.0f,1.0f,1.0f);
		FVector EMSV =FVector(0.0f,0.f,0.0f);
		DynMaterial->SetVectorParameterValue("Opacity", OPCT);
		DynMaterial->SetVectorParameterValue("Emissive_Color", EMSV);

		ProceduralMesh->SetMaterial(GlobalIndex, DynMaterial);
	}


	
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,TEXT("Mesh Section Created"),true);
	return true;
}
