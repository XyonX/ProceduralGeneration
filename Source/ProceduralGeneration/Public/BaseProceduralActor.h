// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProceduralActor.generated.h"

USTRUCT(BlueprintType)
struct FMatrixPosition
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Position")
	int Length ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Position")
	int Width ;
};

USTRUCT(BlueprintType)
struct FTile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	int ID ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	FMatrixPosition Position_2D ; 
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	FVector World_Location ;
	
	
};
USTRUCT(BlueprintType)
struct FTileMesh
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	UStaticMesh*TileMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	TArray<UStaticMesh*>LeftTileMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	TArray<UStaticMesh*>RightTileMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	TArray<UStaticMesh*>UpTileMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	TArray<UStaticMesh*>DownTileMesh;
	
	
};

UCLASS()
class PROCEDURALGENERATION_API ABaseProceduralActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseProceduralActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	//Variables

	// these are number like 100x100 procedural tile
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	int Map_Length ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	int Map_Width ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	float Actor_Length ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	float Actor_Length_X ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	float Actor_Length_Y ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	UInstancedStaticMeshComponent*InstancedMesh ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	UStaticMesh*StaticMesh ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	bool bwantToSpawnTiles;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	TArray<FTile> AllTiles;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	bool bWantCustomTileSize;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	TArray<FTileMesh>TotalTileMesh;
	
	
	
	//Functions

	UFUNCTION(BlueprintCallable)
	void GenerateTile( );
	void CalculateMeshLength();
};
