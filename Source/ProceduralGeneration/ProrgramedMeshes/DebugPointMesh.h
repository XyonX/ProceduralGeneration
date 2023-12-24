/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/

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
