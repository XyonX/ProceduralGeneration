// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "TileMesh.generated.h"



class UTile ;
class UTileMeshData;

USTRUCT(BlueprintType)
struct FTileMeshData : public FTableRowBase
{
	GENERATED_BODY()

	// VARIABLES
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TileMesh")
	UStaticMesh*TileMesh;
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
};

UCLASS()
class PROCEDURALGENERATION_API UTileMesh : public UObject
{
	GENERATED_BODY()

public:

	UTileMesh();
	~UTileMesh();

	void Init(AActor* owneractor , FTileMeshData * FTileMeshData );

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileMesh")
		UStaticMesh* TileMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileMesh")
		TArray<UTile*>OwnerTileList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileMesh")
		FGameplayTag MeshTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileMesh")
		FGameplayTagContainer CompatibleMeshTag_Left;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileMesh")
		FGameplayTagContainer CompatibleMeshTag_Right;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileMesh")
		FGameplayTagContainer CompatibleMeshTag_Up;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileMesh")
		FGameplayTagContainer CompatibleMeshTag_Down;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileMesh")
		UInstancedStaticMeshComponent* InstancedMesh;

};
