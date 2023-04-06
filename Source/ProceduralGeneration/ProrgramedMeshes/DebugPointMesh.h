// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent/Public/ProceduralMeshComponent.h"
#include "DebugPointMesh.generated.h"


UCLASS()
class PROCEDURALGENERATION_API ADebugPointMesh : public AActor
{
	GENERATED_BODY()
public:
	ADebugPointMesh();
	~ADebugPointMesh();

	void CreateMesh ();

	UPROPERTY()
	UProceduralMeshComponent* ProceduralMeshComponent ;
};
