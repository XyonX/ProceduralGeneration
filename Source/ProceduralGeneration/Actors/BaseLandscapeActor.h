// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "GameFramework/Actor.h"
#include "BaseLandscapeActor.generated.h"

UCLASS()
class PROCEDURALGENERATION_API ABaseLandscapeActor : public AActor
{
	GENERATED_BODY()

public:
	ABaseLandscapeActor();

protected:
	
	virtual void BeginPlay() override;
	
public:

	bool ImportHeightMap (const FString& FilePath, int32 ImageSize, TArray<float>& OutHeightMap);

	FVector CalculateVertexNormal(const TArray<float>& inHeightMap, int32 inNumVertsX, int32 inNumVertsY, int32 VertexX, int32 VertexY);
	
	bool GenerateLandscape ();
	

protected:
	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="LandScapeActor")
	int32 NumVertsX;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="LandScapeActor")
	int32 NumVertsY;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="LandScapeActor")
	float MapHeight;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="LandScapeActor")
	float MapWidth;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="LandScapeActor")
	float CellSizeX;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="LandScapeActor")
	float CellSizeY;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="LandScapeActor")
	float HeightMultiplier;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="LandScapeActor")
	UMaterialInterface*LandscapeMaterial;

	FString FilePath;


private:

	TArray<FVector> Vertices;
	TArray<FVector> Normals;
	TArray<int32> Triangles;
	
	TArray<float> HeightMap;


	USceneComponent* RootSceneComponent;
	UProceduralMeshComponent*PMC;

	
};
