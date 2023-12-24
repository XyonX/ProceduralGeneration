/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "UObject/Object.h"
#include "GridSection.generated.h"

class UGridComponent;

UCLASS()
class PROCEDURALGENERATION_API UGridSection : public UObject
{
	GENERATED_BODY()

public:

	/* Functions */
	void Init (AActor* InOwner,int32 InIndex, TArray<FVector>& InVerticesRef, FVector2D InSectionSize, FVector2D InComponentSize, FVector2D InQuadDensity
		, UProceduralMeshComponent*InPMC,FVector2D InNumVertex_lod0, UMaterialInterface*InMaterial);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Index;
	FVector Center;
	FBox Bounds;
	FVector2D SectionSize;
	FVector2D ComponentSize;
	FVector WorldLocation;
	FVector2D NumOfComponents;
	FVector2D NumVertexLod0;
	FVector2D QuadDensity_Lod0;
	FVector2D Pos2D;
	
	TArray<FVector>VerticesRef;

	
	UPROPERTY()
	TMap<FVector2D , UGridComponent*> SectionComponents;
	UPROPERTY()
	UProceduralMeshComponent*ProceduralMeshComponent;
	UPROPERTY()
	AActor*Owner ;
	UPROPERTY()
	UMaterialInterface*DefaultMaterial;
};
