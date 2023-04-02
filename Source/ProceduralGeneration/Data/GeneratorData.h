#pragma once

#include "CoreMinimal.h"
#include "GeneratorData.generated.h"

UCLASS(BlueprintType)
class PROCEDURALGENERATION_API UGeneratorData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Generation")
	TArray<FVector> Vertices;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Generation")
	TArray<int32> Indices;
};