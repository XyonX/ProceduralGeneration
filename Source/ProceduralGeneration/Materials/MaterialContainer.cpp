/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/


#include "MaterialContainer.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/Material.h"
#include "Materials/MaterialExpressionMultiply.h"
#include "Materials/MaterialExpressionScalarParameter.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstance.h"

//UMaterialInterface* UMaterialContainer::GridMaterialInterface = nullptr;
UMaterial* UMaterialContainer::M_Grid = nullptr;
UMaterialInstanceDynamic* UMaterialContainer::MI_Grid = nullptr;

UMaterialContainer::UMaterialContainer()
{
	//M_Grid = NewObject<UMaterial>(GetTransientPackage() , FName(TEXT("MasterGrid")), RF_Transient);
	//MI_Grid = UMaterialInstanceDynamic::Create(MI_Grid, this);
	M_Grid =CreateDefaultSubobject<UMaterial>( FName(TEXT("MasterGrid")));
	//MI_Grid = UMaterialInstanceDynamic::Create(MI_Grid, this);
	
}

void UMaterialContainer::Setup_Material_Grid(UMaterial* in_Material)
{
	UMaterialExpressionScalarParameter* RoughnessMultiplier = NewObject<UMaterialExpressionScalarParameter>(in_Material);
	
	UMaterialExpressionMultiply* Multiply = NewObject<UMaterialExpressionMultiply>(in_Material);
	Multiply->A.Connect(0,RoughnessMultiplier);
	//Multiply->B.Connect(ScalarParameter, 0);
	//in_Material->Expressions.Add(Multiply);

	//in_Material->Roughness.Connect(Multiply, 0);
}

void UMaterialContainer::SetBaseColor(FLinearColor BaseColor, UMaterialInstanceDynamic* in_Material)
{
	in_Material->SetVectorParameterValue("BaseColor", BaseColor);
}

void UMaterialContainer::SetRoughness(float Roughness, UMaterialInstanceDynamic* in_Material)
{
	
}

/*
void UMaterialContainer::SetBaseColor(FLinearColor BaseColor, UMaterial* in_Material)
{
	// Create a texture object and set it as the diffuse texture
	//UTexture* DiffuseTexture = LoadObject<UTexture>(NULL, TEXT("/Game/Textures/MyTexture.MyTexture"), NULL, LOAD_None, NULL);
	//in_Material->SetTextureParameterValueEditorOnly(TEXT("DiffuseTexture"), DiffuseTexture);
}*/

void UMaterialContainer::GenerateGrid()
{
	
}
