// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayTagContainer.h"
#include "FTile.h"
#include "FTileMesh.generated.h"


// Must call Init Function From 
USTRUCT(BlueprintType)
struct FTileMesh
{
	GENERATED_BODY()
	void Init(AActor* owneractor);

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	UStaticMesh*TileMesh;
	TArray<FTile*>OwnerTileList;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	FGameplayTag MeshTag ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	FGameplayTagContainer ComaptileMeshTag_Left ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	FGameplayTagContainer ComaptileMeshTag_Right ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	FGameplayTagContainer ComaptileMeshTag_Up ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	FGameplayTagContainer ComaptileMeshTag_Down ;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	AActor*Owner;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	UInstancedStaticMeshComponent*InstancedMesh;
	
};



UCLASS()
class PROCEDURALGENERATION_API UFTileMesh : public UObject
{
	GENERATED_BODY()
};
