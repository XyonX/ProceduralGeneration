// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "GameFramework/Actor.h"
#include "RuntimeAppearanceEditor.generated.h"



/** Color Code for Character Parts 

	Head: FColor::Red or (255, 0, 0)
	Torso: FColor::Green or (0, 255, 0)
	Arms: FColor::Blue or (0, 0, 255)
	Legs: FColor::Yellow or (255, 255, 0)
	Hands: FColor::Cyan or (0, 255, 255)
	Feet: FColor::Magenta or (255, 0, 255)


*/


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
		UStaticMeshComponent* CharacterStaticMesh;
	UPROPERTY()
	UProceduralMeshComponent* CharacterProceduralMesh;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//Extract The Mesh Data
	bool ConvertStaticMeshToProceduralMesh (UStaticMeshComponent*InSMC, UProceduralMeshComponent* OutPMC );
	void ExtractMeshSectionStaticMeshComponent ();

protected:

	FColor Head = FColor::Red ;
	FColor Torso = FColor::Green;
	FColor Arms = FColor::Blue ;
	FColor Legs = FColor::Yellow ;
	FColor Hands =  FColor::Cyan;
    FColor Feet =  FColor::Magenta;


	TArray<FVector3f> Vertices_Head;
	TArray<FVector3f> Vertices_Torso;
	TArray<FVector3f> Vertices_Arms;
	TArray<FVector3f> Vertices_Legs;
	TArray<FVector3f> Vertices_Hands;
	TArray<FVector3f> Vertices_Feet;
	
	

private:

	int32 Index;
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FProcMeshTangent> Tangents;

	TMap<FVector3f ,FColor>VertexColorData;

	FProcMeshSection*PMS_FullBody;
};
