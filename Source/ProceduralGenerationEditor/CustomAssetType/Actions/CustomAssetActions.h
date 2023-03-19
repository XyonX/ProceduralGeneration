#pragma once

#include "AssetTypeActions_Base.h"
#include  "ProceduralGenerationEditor/CustomAssetType/Class/TestAsset.h"
//#define LOCTEXT_NAMESPACE "AssetTypeActions"
class FMyCustomAssetActions : public FAssetTypeActions_Base
{
	
public:

	
	virtual FText GetName() const override; 
	virtual FColor GetTypeColor() const override { return FColor::Blue; }
	virtual UClass* GetSupportedClass() const override { return ATestAsset::StaticClass(); }
	virtual bool HasActions(const TArray<UObject*>& InObjects) const override { return true; }
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects,TSharedPtr<class IToolkitHost> EditWithinLevelEditor) override {}
	virtual bool CanFilter() override { return true; }
	virtual uint32 GetCategories() override { return EAssetTypeCategories::Misc; }
	
	
	//virtual void GetActions(const TArray<UObject*>& InObjects, FToolMenuSection& Section) override;
};