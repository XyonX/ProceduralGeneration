// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreGenerator.h"
#include "ProceduralMeshComponent.h"
#include "ProceduralMeshGenerator.generated.h"

//Generator Base On PMC
UCLASS()
class PROCEDURALGENERATION_API UProceduralMeshGenerator : public UCoreGenerator
{
	GENERATED_BODY()

public:

	virtual TArray<UTile*>* Run() override;


	UFUNCTION(BlueprintCallable)
	virtual bool GenerateTile_HeightMap(FVector2D InGridSize ,FVector2D InTileSize , TArray<UTile*>&OutGrid);

	virtual  bool GenerateGridMesh ();

protected:

	TArray<float> HeightMap;

	UPROPERTY()
	UProceduralMeshComponent*ProceduralMesh;

	TArray<FVector>Vertices;
	TArray<int32>VertexIndex;
	TArray<int32>Triangles;
	TArray<FVector>Normals;
	TArray<FVector2D>UVs;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Generator",meta=(AllowPrivateAccess="true"))
	EGridType GridType;
	
};
