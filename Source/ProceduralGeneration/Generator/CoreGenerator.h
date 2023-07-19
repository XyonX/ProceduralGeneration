// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CorePlugin/Data/GridData.h"
#include "CoreGenerator.generated.h"


class UGridSection;

class UProceduralMeshComponent;
// The Base class of All tile  generation algorithm 
UCLASS(Blueprintable)
class PROCEDURALGENERATION_API UCoreGenerator : public UObject , public TSharedFromThis<UCoreGenerator>
{
	GENERATED_BODY()
public:
	UCoreGenerator();

	
	//Generation

	//The Main Function to Generate the grid
	
	virtual UGridSection* Run () ;


	virtual bool Init (FGridData GridData);

	UFUNCTION(BlueprintCallable)
	virtual void ConfigureGrid();
	UFUNCTION(BlueprintCallable)
	virtual bool GenerateGrid(FVector2D InGridSize , TArray<UGridSection*>&OutGrid);
	virtual TArray<UGridSection*>* ConfigureGridSections ();


public:
	

	/** Getter  */

	UFUNCTION(BlueprintCallable)
	FVector2D GetGridSize ( ){ return  GridSize;};
	UFUNCTION(BlueprintCallable)
	FVector2D GetNumOfSections(){return NumOfSection;};

	
	TArray<UGridSection*>* GetGrid   () {return  &Grid;}

	void Receiver_OnCharacterMovement (FVector CharacterLocation);
	
protected:


	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Generator")
	FGridData Defaults;
	
	/** Grid Size */	/**--------------*/

	//The scaler size representation of the grid in Meter 
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Generator")
	FVector2D GridSize;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Generator")
	FVector2D SectionSize;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Generator")
	FVector2D ComponentSize;

	/** Grid Counts */	/**--------------*/
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Generator")
	FVector2D NumOfSection;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Generator")
	FVector2D NumOfComponentsPerSection;

	/** Data */
	FVector Center;
	FVector Origin;
	FString HeightMapPath;
	FVector Extents;
	

	/** Input Data */
	/**Density of the landscape in close proximity */
	/** in  100 Unreal Unit or 1M (RealWorld Unit)  */
	UPROPERTY()
	FVector2D QuadDensity_Lod0;
	//Density of the landscape Sections far from the player 
	UPROPERTY()
	FVector2D QuadDensity_Lod1;
	
	
	/** Lod 0 */
	FVector2D NumVerts_Lod0;
	/** Lod 1 */
	FVector2D NumVerts_Lod1;

	
	UPROPERTY()
	TArray<float> HeightMap;
	TArray<FVector>Vertices;
	TArray<int32>VertexIndex;
	TArray<int32>Triangles;
	TArray<FVector>Normals;
	TArray<FVector2D>UVs;
	
	/** Reference */
	UPROPERTY()
	
	TArray<UGridSection*> Grid;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Generator")
	UGridSection*DynamicGirdSection;

	UPROPERTY()
	UProceduralMeshComponent*ProceduralMesh;

	UPROPERTY()
	UMaterialInterface*DefaultMaterial;

	UPROPERTY()
	AActor*Owner;
	


	
	
};
