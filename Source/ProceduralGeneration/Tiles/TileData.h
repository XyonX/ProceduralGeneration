// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TileData.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALGENERATION_API UTileData : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int ID ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector2D Pos ;
};
