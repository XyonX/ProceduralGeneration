// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GridComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALGENERATION_API UGridComponent : public UObject
{
	GENERATED_BODY()

public:
	
	/* Functions */
	void Init ();

	/** Data */
	FBox Bounds;
	int32 GlobalIndex;
	int32 LocalIndex;
	FVector WorldLocation;
	FVector Center;
	FVector Extents;
	TArray<TArrayView<const FVector>> ComponentVertices;
};
