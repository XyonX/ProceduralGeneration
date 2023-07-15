#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VoronoiDiagram.generated.h"


// The Base class of All tile  generation algorithm 
UCLASS(Blueprintable)
class PROCEDURALGENERATION_API UVoronoiDiagram : public UObject
{

	GENERATED_BODY()

	
public:
	
	void Init(TArray<FVector> InVertices, TArray<FVector>InSeeds);

	void Run ();

private:

	TArray<FVector>Seeds;
	TArray<FVector>Vertices;

	TMap<FVector,TArray<FVector>>VoronoiData;
};


