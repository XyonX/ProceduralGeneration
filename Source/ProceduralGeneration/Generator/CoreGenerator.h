// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreUI/DockTab/GenerationControllerTab.h"
#include "UObject/Object.h"
#include "CoreGenerator.generated.h"

class UTile;


UCLASS()
class PROCEDURALGENERATION_API UCoreGenerator : public UObject
{
	GENERATED_BODY()
public:
	UCoreGenerator();


	virtual TArray<UTile*> Run ();

	FORCEINLINE  TArray<UTile*> GetAllTiles   () {return  AllTiles;}
	FORCEINLINE  TArray<UTile*> GetRemainingTiles   () {return  RemainingTiles;}
	FORCEINLINE  TArray<UTile*> GetCollapsedTiles   () {return  CollapsedTiles;}

	FORCEINLINE int GetHeight () {return Map_Height;}
	FORCEINLINE int GetWidth () {return Map_Width;}

	void AddUIEntry ();


	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Data")
	UDataAsset* GeneratorDataAsset ;


private:

	//Map Dimention

	UPROPERTY(EditAnywhere,Category = "Generation")
	int Map_Height;
	UPROPERTY(EditAnywhere, Category = "Generation")
	int Map_Width;

	// Tile Data
	UPROPERTY(EditAnywhere, Category = "Tile")
	TArray<UTile*> AllTiles;
	UPROPERTY(EditAnywhere, Category = "Tile")
	TArray<UTile*> RemainingTiles;
	UPROPERTY(EditAnywhere,  Category = "Tile")
	TArray<UTile*> CollapsedTiles;

	TSharedPtr<SGenerationControllerTab> ControllerTab ;

	

	bool  bIsFirstGen ;
};
