// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CorePlugin/Helpers/DelegateHelper.h"
#include "GameFramework/Actor.h"
#include "BaseGridActor.generated.h"

class ATopDownPlayerController;
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

	UFUNCTION()
	void Receiver_OnMouseMove (FVector HitLoc);

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


	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="ProcMesh",meta=(AllowPrivateAccess=True))
	FVector GridSize;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="ProcMesh",meta=(AllowPrivateAccess=True))
	FVector CellSize;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ProcMesh")
	FVector GridCenter ;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ProcMesh")
	FVector MaterialOpacity;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ProcMesh")
	FVector MaterialEmission;
	ATopDownPlayerController*TopDownController;

	UTileData*CursorHitTile;

	FOnMouseMovementDelegate MouseMovementDelegate;

	void TileHoverEffect();
	void PrintDotProduct (ATopDownPlayerController*TDController);

	

private:

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="ProcMesh",meta=(AllowPrivateAccess=True))
	UProceduralMeshComponent* GridMesh;
	//TArray<UProceduralMeshComponent*>AllTiles ;
	TArray<FVector>Vertices;
	TArray<int32>VertexIndex;
	TArray<int32>Triangles;
	TArray<FVector>Normals;
	TArray<FVector2D>UVs;
	TArray<TArray<FVector>>AllCollisionShape;
	TMap<FVector2D ,FVector> MainContainer ;
	TMap<FVector2D , UTileData*>TileMap ;
	TMap<FVector2D , UMaterialInstanceDynamic*>MaterialContainer ;
	TArray<FVector*> GetVerticesByTilePos (FVector2D TilePos);

public:
	// Generate the grid mesh
	bool GenerateGridMesh();
	void DrawPositionIndicator();
};