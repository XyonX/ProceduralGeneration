// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProceduralGeneration.h"



#define LOCTEXT_NAMESPACE "FProceduralGenerationModule"

void FProceduralGenerationModule::StartupModule()
{
/*
	const EAssetTypeCategories::Type MyCustomAssetCategory = EAssetTypeCategories::Misc;

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	FAssetCategoryTreeItem MyCategory;
	FAssetTypeCategoryTree CustomAssetCategoryTree;
	CustomAssetCategoryTree.SetTypeAssetCategories(MyCustomAssetCategory);
	AssetTools.RegisterAdvancedAssetCategory(MyAssetCategory, FText::FromString("My Custom Assets"));

	AssetTools.RegisterAssetTypeActions(MakeShared<FMyCustomAssetActions>(MyAssetCategory));


	const FName MyCustomAssetCategoryName = FName(TEXT("MyCustomAssets"));

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	// Register the custom asset category
	AssetTools.RegisterAdvancedAssetCategory(MyCustomAssetCategoryName, FText::FromString("My Custom Assets"));

	// Add the custom asset category to the content browser
	TSharedPtr<FAssetTypeActions_MyCustomAsset> MyCustomAssetTypeActions = MakeShared<FAssetTypeActions_MyCustomAsset>();
	TSharedPtr<FCollectionManagerModule> CollectionManager = FModuleManager::LoadModuleChecked<FCollectionManagerModule>("CollectionManager");
	CollectionManager->Get().AddCollection(FCollectionNameType("MyCustomAssets"), FCollectionDescription(), FAssetRegistryModule::Get().Get().GetCollectionPath(FName("OtherAssets")));
	AssetTools.GetAssetTypeActionsRegistry().RegisterAssetTypeActions(MyCustomAssetTypeActions.ToSharedRef(), MyCustomAssetCategoryName, FAssetTypeActions::CreateGetActionsMenuDelegate(FOnGetAssetActionsMenu::CreateSP(MyCustomAssetTypeActions.Get(), &FAssetTypeActions_MyCustomAsset::GetActionsMenu)));

*/

}

void FProceduralGenerationModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FProceduralGenerationModule, ProceduralGeneration)