// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialInstance.h"
#include "BaseMeshActor.generated.h"

UCLASS()
class PROCEDURALGENERATION_API ABaseMeshActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseMeshActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MeshActor")
	UStaticMeshComponent*MeshCompoonent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MeshActor")
	UStaticMesh*Mesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MeshActor")
	UMaterialInstanceDynamic*Material;

public:
	
	void SetMesh(UStaticMesh*inMesh) {Mesh=inMesh;}
	UStaticMesh* GetMesh () {return  Mesh;};

	void Init (UStaticMesh*inMesh,UMaterialInstanceDynamic*inMaterial);
};
