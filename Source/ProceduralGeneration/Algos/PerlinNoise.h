#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PerlinNoise.generated.h"


// The Base class of All tile  generation algorithm 
UCLASS(Blueprintable)
class PROCEDURALGENERATION_API UPerlinNoise : public UObject
{

	GENERATED_BODY()

	
public:
	
	UPerlinNoise();
	float Interpolate (float A , float B ,float T);
	void Init(FVector2D InGridSize);
	void Run ();

private:
	FVector2D GridSize;
	TArray<float>PerlinData;
};


