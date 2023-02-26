// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayTagContainer.h"
#include "FTileMesh.generated.h"

class UTile ;

// Must call Init Function From 
USTRUCT(BlueprintType)
struct FTileMesh
{
	GENERATED_BODY()
	void Init(AActor* owneractor);

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	UStaticMesh*TileMesh;
	//UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	//TArray<TSharedPtr<UTile>>OwnerTileList;
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
