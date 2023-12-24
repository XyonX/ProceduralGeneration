/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "UObject/Object.h"
#include "GridComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALGENERATION_API UGridComponent : public UObject
{
	GENERATED_BODY()

public:
	
	/* Functions */
	void Init (TArray<FVector>& InVerticesRef,UProceduralMeshComponent*InProceduralMeshComponent,TArray<int32>InTriangles,
	TArray<FVector>InNormals,int32 InGlobalIndex, UMaterialInterface*InMaterial );

	bool GenerateMeshSection ();
	void GenerateMeshSection_Internal ();

	/** Data */
	int32 GlobalIndex;
	int32 LocalIndex;
	FVector2D GlobalPos2D;
	FVector2D LocalPos2D;
	FVector WorldLocation;
	FVector Center;
	FVector Extents;
	
	TArray<FVector>VerticesRef;
	TArray<int32>Triangles;
	TArray<FVector>Normals;


	

private:

	UPROPERTY()
	UProceduralMeshComponent*ProceduralMesh;
	UPROPERTY()
	UMaterialInterface*DefaultMaterial;
};
