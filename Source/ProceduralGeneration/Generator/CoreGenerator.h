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
	~UCoreGenerator();
	

	// Getters
	virtual int GetHeight () {return Map_Height;}
	virtual int GetWidth () {return Map_Width;}
	FString GetDataAssetPath()const;
	inline TArray<UTile*>* GetAllTiles   () {return  TileContainer;}
	inline TArray<UTile*>* GetRemainingTiles   () {return  TileContainer_Remaining;}
	inline TArray<UTile*>* GetCollapsedTiles   () {return  TileContainer_Collapsed;}

	//UI
	void AddUIEntry ();

	//Generation
	virtual bool Run (TArray<UTile*>& in_TileContainer ,TArray<UTileMesh*>& in_TileMeshContainer ) ;
	virtual void Init (TSharedPtr<SGenerationControllerTab> InTab , UStaticMesh*in_UnitMesh, int in_height , int in_width );
	virtual void CalculateMeshDimension(const UStaticMesh*StaticMesh , int& out_LenX ,int&  out_LenY , int&  out_LenZ);
	virtual bool GenerateTile( TArray<UTile*>& in_TileContainer, TArray<UTileMesh*>& in_TileMeshCContainer , int& in_TileCount ,int in_Height ,int in_Width );
	virtual void SetTilesWorldLocation (TArray<UTile*>& in_TileContainer, int Length_X ,int Length_Y );

    //Debug Visualization
	bool bDrawn = false; // Keep track of whether the point has been drawn or not
	int32 PointId = 0; // The debug draw ID of the point
    void DrawPositionIndicator (TArray<UTile*>* in_TileContainer);
	void RemoveIndicator (TArray<UTile*>* in_TileContainer);
	bool OnDebug ();


	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Data")
	UDataAsset* GeneratorDataAsset ;

	TSharedRef<SWidget> HandleMenuContent()  ;
	TSharedRef<ITableRow> HandleCustomDataAssetListRow (UObject* Item, const TSharedRef<STableViewBase>& OwnerTable);

	void ScanDataAssets ();
	TArray<UObject*>CustomDataAssetList;
	void SetControllerTab (TSharedPtr<SGenerationControllerTab> in_ControllerTab){ControllerTab =in_ControllerTab;}


protected:

	TArray<UTile*>* TileContainer;
    TArray<UTile*>* TileContainer_Remaining;
    TArray<UTile*>* TileContainer_Collapsed;

	

	int TileCount ;
	UPROPERTY( EditAnywhere, BlueprintReadWrite,Category="Generation")
	UStaticMesh*UnitMesh;
	
private:

	//Map Dimension

	UPROPERTY(EditAnywhere,Category = "Generation")
	int Map_Height  = 10;
	UPROPERTY(EditAnywhere, Category = "Generation")
	int Map_Width =  10;


	//Mesh Dimension
	int  Actor_Length_X = 1.0f;
	int  Actor_Length_Y = 1.0f;
	int  Actor_Length_Z = 1.0f;

	TSharedPtr<SGenerationControllerTab> ControllerTab ;

	FString SelectedDataAssetPath ;

	bool  bIsFirstGen ;
};
