// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ProceduralGeneration/Tiles/Tile.h"
#include "CoreUI/DockTab/GenerationControllerTab.h"
#include "CoreGenerator.generated.h"

//class USpawnable;
//class UTile;


// The Base class of All tile  generation algorithm 
UCLASS()
class PROCEDURALGENERATION_API UCoreGenerator : public UObject //, public TSharedFromThis<UCoreGenerator>
{
	GENERATED_BODY()
public:
	UCoreGenerator();
	~UCoreGenerator();
	

	// Getters
	virtual int GetHeight () {return Map_Height;}
	virtual int GetWidth () {return Map_Width;}
	FString GetDataAssetPath()const;
	inline TArray<UTile*>* GetAllTiles   () {return  &TileContainer;}
	
	//Generation
	virtual TArray<UTile*>* Run ( ) ;
	virtual void Init ( TMap<int32,USpawnable*>*in_SpawnableContainer ,UStaticMesh*InUnitMesh,int InMapHeight , int InMapWidth);
	virtual bool CalculateMeshDimension(const UStaticMesh*StaticMesh , float& out_LenX ,float&  out_LenY , float&  out_LenZ);
	virtual bool GenerateTile( TArray<UTile*>& in_TileContainer, TMap<int32,USpawnable*>* in_SpawnableContainer , int& in_TileCount ,int in_Height ,int in_Width );
	virtual void SetTilesWorldLocation (TArray<UTile*>& in_TileContainer, int Length_X ,int Length_Y );

    //Debug Visualization
	bool bDrawn = false; // Keep track of whether the point has been drawn or not
	int32 PointId = 0; // The debug draw ID of the point
    void DrawPositionIndicator (TArray<UTile*>* in_TileContainer);
	void RemoveIndicator (TArray<UTile*>* in_TileContainer);
	bool OnDebug ();


	//Blueprint Exposed Data
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Data")
	UDataAsset* GeneratorDataAsset ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Data")
	UStaticMesh*UnitMesh;

	

	//TSharedRef<SWidget> HandleMenuContent()  ;
	//TSharedRef<ITableRow> HandleCustomDataAssetListRow (UObject* Item, const TSharedRef<STableViewBase>& OwnerTable);

	//void ScanDataAssets ();
	//TArray<UObject*>CustomDataAssetList;
	void SetControllerTab (TSharedPtr<SGenerationControllerTab> in_ControllerTab){ControllerTab =in_ControllerTab;}


protected:

	UPROPERTY()
	TArray<UTile*> TileContainer;
	TMap<int32,USpawnable*>*SpawnableContainer;
	TArray<FVector2D>TileWorldLocationContainer;

	

	int TileCount ;

	float  Actor_Length_X ;
	float  Actor_Length_Y ;
	float  Actor_Length_Z ;
	
private:

	//Map Dimension

	UPROPERTY(EditAnywhere,Category = "Generation")
	int Map_Height  = 4;
	UPROPERTY(EditAnywhere, Category = "Generation")
	int Map_Width =  4;
	

	TSharedPtr<SGenerationControllerTab> ControllerTab ;

	FString SelectedDataAssetPath ;

	bool  bIsFirstGen ;
};
