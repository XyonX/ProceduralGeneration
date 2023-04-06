// Fill out your copyright notice in the Description page of Project Settings.


#include "MaterialContainer.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/Material.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstance.h"

UMaterialInterface* UMaterialContainer::GridMaterialInterface = nullptr;
UMaterialInstanceDynamic* UMaterialContainer::GridDynamic = nullptr;

UMaterialContainer::UMaterialContainer()
{
	GridDynamic = UMaterialInstanceDynamic::Create(GridMaterialInterface, this);

	// Set any desired parameters on the dynamic material instance
	GridDynamic->SetVectorParameterValue(TEXT("MyColor"), FLinearColor::Red);
	GridMaterialInterface =  NewObject<UMaterial>(GetTransientPackage(), NAME_None, RF_Transient);
	
}

void UMaterialContainer::SetBaseColor(FLinearColor BaseColor, UMaterialInstanceDynamic* in_Material)
{
	in_Material->SetVectorParameterValue("BaseColor", BaseColor);
}

void UMaterialContainer::SetBaseColor(FLinearColor BaseColor, UMaterial* in_Material)
{
	// Create a texture object and set it as the diffuse texture
	UTexture* DiffuseTexture = LoadObject<UTexture>(NULL, TEXT("/Game/Textures/MyTexture.MyTexture"), NULL, LOAD_None, NULL);
	in_Material->SetTextureParameterValueEditorOnly(TEXT("DiffuseTexture"), DiffuseTexture);
}

void UMaterialContainer::GenerateGrid()
{
	
}
