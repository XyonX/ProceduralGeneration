// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ProceduralGeneration/Tiles/Tile.h"
#include "CoreGenerator.generated.h"

//class USpawnable;
//class UTile;


// The Base class of All tile  generation algorithm 
UCLASS(Blueprintable)
class PROCEDURALGENERATION_API UCoreGenerator : public UObject , public TSharedFromThis<UCoreGenerator>
{
	GENERATED_BODY()
public:
	UCoreGenerator();
	~UCoreGenerator();

	
	//Generation

	//The Main Function to Generate the grid
	virtual TArray<UTile*>* Run () ;
	
	virtual FVector2D ConfigureTileSize();
	
	virtual bool GenerateTile(FVector2D InGridSize ,FVector2D InTileSize , TArray<UTile*>&OutGrid);

public:
	
	bool bIsStaticGrid;

	/** Getter and Setters */

	UFUNCTION(BlueprintCallable)
	FVector2D GetGridSize ( ){ return  GridSize;};
	UFUNCTION(BlueprintCallable)
	FVector2D GetTileSize(){return  TileSize;};

	UFUNCTION(BlueprintCallable)
	void SetGridSize (FVector2D InSize ){ GridSize=InSize;};
	UFUNCTION(BlueprintCallable)
	void SetTileSize(FVector2D InSize){TileSize=InSize;};

	
	TArray<UTile*>* GetGrid   () {return  &Grid;}
	
private:
	
	UPROPERTY()
	TArray<UTile*> Grid;
	

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Generator",meta=(AllowPrivateAccess="true"))
	FVector2D GridSize;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Generator",meta=(AllowPrivateAccess="true"))
	FVector2D TileSize;
	
	
};
