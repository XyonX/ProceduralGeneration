// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ProceduralGeneration/Tiles/Tile.h"
#include "CoreUI/DockTab/GenerationControllerTab.h"
#include "CoreGenerator.generated.h"

// The Base class of All tile  generation algorithm 
UCLASS()
class PROCEDURALGENERATION_API UCoreGenerator : public UObject , public TSharedFromThis<UCoreGenerator>
{
	GENERATED_BODY()
public:
	UCoreGenerator();

	virtual void Init (TSharedPtr<SGenerationControllerTab> InTab);
	virtual TArray<UTile*> Run ();
	inline TArray<UTile*> GetAllTiles   () {return  AllTiles;}
	inline TArray<UTile*> GetRemainingTiles   () {return  RemainingTiles;}
	inline TArray<UTile*> GetCollapsedTiles   () {return  CollapsedTiles;}



	// Getters
	virtual int GetHeight () {return Map_Height;}
	virtual int GetWidth () {return Map_Width;}
	FString GetDataAssetPath()const;

	//UI
	void AddUIEntry ();

	

	


	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Data")
	UDataAsset* GeneratorDataAsset ;

	TSharedRef<SWidget> HandleMenuContent()  ;
	TSharedRef<ITableRow> HandleCustomDataAssetListRow (UObject* Item, const TSharedRef<STableViewBase>& OwnerTable);

	void ScanDataAssets ();
	TArray<UObject*>CustomDataAssetList;
private:

	//Map Dimension

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

	FString SelectedDataAssetPath ;

	bool  bIsFirstGen ;
};
