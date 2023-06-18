// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TileData.generated.h"

struct FProcMeshSection;
/**
 * 
 */
UCLASS(Blueprintable)
class PROCEDURALGENERATION_API UTileData : public UObject
{
	GENERATED_BODY()
public:
	UTileData();
	UTileData(FVector2D in_Loc2D, FVector in_LocWorld, int in_Index,TArray<FVector>* in_Vertices, FVector in_GridSize,FVector in_TileSize);

	
	void Init ( TArray<FVector>* in_Vertices );
	void Const (FVector2D in_Loc2D, FVector in_LocWorld, int in_Index ,FVector in_GridSize , FVector in_TileSize);
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int Index ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector2D Loc2D ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector LocationWorld ;
	TArray<FVector>* Vertices ;
	FVector GridSize;
	FVector TileSize;
	FBox BoundingBox;
	FVector Normal ;
	FVector CenterPoint;
	FProcMeshSection* MeshSections;
	

	FVector CalculateNorMal (TArray<FVector>&in_Verts);
	FVector CalculateCenterPoint (TArray<FVector>&in_Verts);
	FBox CalculateBoundingBox ();
	TArray<FVector>  GetVertices (int in_Index);
	
};
