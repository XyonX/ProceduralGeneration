/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MaterialContainer.generated.h"


UCLASS()
class PROCEDURALGENERATION_API UMaterialContainer : public UObject
{
	GENERATED_BODY()
public:
	UMaterialContainer();

	//static UMaterialInterface* GridMaterialInterface;
	static  UMaterialInstanceDynamic* MI_Grid  ;
	static UMaterial* M_Grid ;

	//Grid Functions

	void Setup_Material_Grid (UMaterial*in_Material);


	//Generic functions
	static void SetBaseColor ( FLinearColor BaseColor , UMaterialInstanceDynamic* in_Material ) ;
	static void SetRoughness ( float Roughness , UMaterialInstanceDynamic* in_Material ) ;

	
	

	//variables

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyMaterial")
	UTexture2D* BaseColor_01;


	void GenerateGrid();


	//Grid Parameters
	
	// The size of each square
	float SquareSize = 50.0;

	// The number of squares in each dimension
	int GridSize = 10;

	// The color of each square
	FLinearColor SquareColor = FLinearColor::Green;

	// The color to use for squares that are turned off
	FLinearColor OffColor = FLinearColor::Black;


};
