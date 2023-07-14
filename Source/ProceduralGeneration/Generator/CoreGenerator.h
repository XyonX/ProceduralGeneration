// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CorePlugin/Data/GridData.h"
#include "UObject/Object.h"
#include "CoreGenerator.generated.h"


class UProceduralMeshComponent;
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
	
	virtual UGridSection* Run () ;


	virtual bool Init (FGridData GridData);

	UFUNCTION(BlueprintCallable)
	virtual FVector2D ConfigureGrid();
	UFUNCTION(BlueprintCallable)
	virtual bool GenerateGrid(FVector2D InGridSize ,FVector2D InTileSize , TArray<UGridSection*>&OutGrid);
	UFUNCTION(BlueprintCallable)
	virtual TArray<UGridSection*>* ConfigureGridSection ();


public:
	

	/** Getter  */

	UFUNCTION(BlueprintCallable)
	FVector2D GetGridSize ( ){ return  GridSize;};
	UFUNCTION(BlueprintCallable)
	FVector2D GetTileSize(){return  TileSize;};
	UFUNCTION(BlueprintCallable)
	FVector2D GetNumOfSections(){return NumOfSection;};

	
	TArray<UGridSection*>* GetGrid   () {return  &Grid;}

	void Receiver_OnCharacterMovement (FVector CharacterLocation);
	
protected:
	

	
	/** Data */
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Generator")
	FVector2D GridSize;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Generator")
	FVector2D TileSize;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Generator")
	FVector2D NumOfSection;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Generator",meta=(AllowPrivateAccess="true"))
	EGridType GridType;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Generator")
	FVector Origin;

	FString HeightMapPath;
	FVector Center;
	FVector2D Extents;

	int32 NumVertsX_Lod0;
	int32 NumVertsY_Lod0;

	int32 NumVertsX_Lod1;
	int32 NumVertsY_Lod1;

	UPROPERTY()
	TArray<float> HeightMap;
	
	TArray<FVector>Vertices;
	TArray<int32>VertexIndex;
	TArray<int32>Triangles;
	TArray<FVector>Normals;
	TArray<FVector2D>UVs;

	/**Density of the landscape in close proximity */
	/** in  100 Unreal Unit or 1M (RealWorld Unit)  */
	UPROPERTY()
	int32 QuadDensity_Lod0;
	//Density of the landscape Sections far from the player 
	UPROPERTY()
	int32 QuadDensity_Lod1;

	/**Density of the landscape in close proximity */
	/** 1 UnitDensity = 100 Unreal Unit = 1M (RealWorld Unit)  */
	UPROPERTY()
	int32 VertexDensity_Lod0;
	//Density of the landscape Sections far from the player 
	UPROPERTY()
	int32 VertexDensity_Lod1;

	



	/** Reference */
	UPROPERTY()
	
	TArray<UGridSection*> Grid;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Generator")
	UGridSection*DynamicGirdSection;

	UPROPERTY()
	UProceduralMeshComponent*ProceduralMesh;

	UPROPERTY()
	AActor*Owner;
	


	
	
};
