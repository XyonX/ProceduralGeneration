// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GridSection.generated.h"

class UGridComponent;

UCLASS()
class PROCEDURALGENERATION_API UGridSection : public UObject
{
	GENERATED_BODY()

public:

	/* Functions */
	void Init (AActor* Owner, FVector2D InSectionSize, FVector2D InComponentSize, FVector2D InQuadDensity,
	TArray<TArrayView<const FVector>> InSectionVertices);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Index;
	FVector Center;
	FBox Bounds;
	FVector2D SectionSize;
	FVector2D ComponentSize;
	FVector WorldLocation;
	FVector2D NumOfComponents;
	FVector2D QuadDensity_Lod0;
	
	FVector2D Pos2D;

	TArray<TArrayView<const FVector>> SectionVertices;
	UPROPERTY()
	TMap<FVector2D , UGridComponent*> SectionComponents;
};
