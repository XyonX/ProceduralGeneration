// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "GameFramework/Actor.h"
#include "RuntimeAppearanceEditor.generated.h"


/** Class to Modify Character Mesh Appearance at Runtime */
UCLASS()
class PROCEDURALGENERATION_API ARuntimeAppearanceEditor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARuntimeAppearanceEditor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UStaticMesh*CharacterMesh;
	UPROPERTY()
	UStaticMeshComponent* CharacterMeshComponent;
	UPROPERTY()
	UProceduralMeshComponent*PMC;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void ExtractMeshData ();

private:

	int32 Index;
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FProcMeshTangent> Tangents;

	FProcMeshSection*PMS_FullBody;
};
