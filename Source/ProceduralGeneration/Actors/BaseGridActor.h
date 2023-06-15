// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGridActor.generated.h"

class UTileData;
class UProceduralMeshComponent;
UCLASS(BlueprintType)
class PROCEDURALGENERATION_API ABaseGridActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseGridActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Mat")
	UMaterialInterface* MaterialTemplate;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Test")
	UStaticMesh*TestCube ;

	
	TArray<UTileData*>Tiles;
	void OnMouseMove(const FVector2D& MousePosition);
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector CursorWorldPosition ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector CursorWorldDirection ;

	

private:

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="ProcMesh",meta=(AllowPrivateAccess=True))
	UProceduralMeshComponent* GridMesh;
	TArray<UProceduralMeshComponent*>AllTiles ;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="ProcMesh",meta=(AllowPrivateAccess=True))
	int32 Length_X;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="ProcMesh",meta=(AllowPrivateAccess=True))
	int32 Length_Y;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="ProcMesh",meta=(AllowPrivateAccess=True))
	float CellSize;

	TArray<FVector>Vertices;
	TArray<int32>Index;
	TArray<int32>Triangles;
	TArray<FVector>Normals;
	TArray<FVector2D>UVs;
	TMap<FVector2D ,FVector> MainContainer ;
	TArray<FVector*> GetVerticesByTilePos (FVector2D TilePos);

public:
	// Generate the grid mesh
	bool GenerateGridMesh();
	void DrawPositionIndicator();
};
