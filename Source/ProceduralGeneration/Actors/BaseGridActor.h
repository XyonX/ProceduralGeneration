// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGridActor.generated.h"

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

private:

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="ProcMesh",meta=(AllowPrivateAccess=True))
	UProceduralMeshComponent* GridMesh;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="ProcMesh",meta=(AllowPrivateAccess=True))
	int32 NumRows;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="ProcMesh",meta=(AllowPrivateAccess=True))
	int32 NumColumns;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="ProcMesh",meta=(AllowPrivateAccess=True))
	float CellSize;

	TArray<FVector>Vertices;
	TArray<int32>Triangles;
	TArray<FVector>Normals;
	TArray<FVector2D>UVs;

public:
	// Generate the grid mesh
	bool GenerateGridMesh();
	
};
