#pragma once
#include "ProceduralGenerationEditor.h"

#include "AssetToolsModule.h"
#include "CustomAssetType/Actions/BaseAssetActions.h"
#include "CustomAssetType/AssetFactory/BaseActorFactory.h"

void FMyEditorModule::StartupModule()
{
	IModuleInterface::StartupModule();

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	CustomAssetActions = MakeShareable(new FBaseActorActions);

	AssetTools.RegisterAssetTypeActions(CustomAssetActions.ToSharedRef());

	// Add custom asset category
	EAssetTypeCategories::Type CustomAssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("Procedural Actor")), FText::FromString("Procedural Actor"));

	/*// Register custom asset factory
	EAssetTypeCategories::Type MyAssetCategoryBit = CustomAssetCategoryBit;
	TSharedPtr<UBaseActorFactory> CustomAssetFactory = MakeShareable(new UBaseActorFactory);
	AssetTools.RegisterAssetTypeActions(CustomAssetActions.ToSharedRef());
	AssetTools.RegisterAssetTypeActions(MakeShareable(new FAssetTypeActions_ClassLoader<UCustomAsset>(
		MyAssetCategoryBit,
		FColor::Blue,
		FText::FromString("Custom Asset"),
		FText::FromString("Custom Asset")
	)));
	AssetTools.RegisterAssetTypeActions(MakeShareable(new FAssetTypeActions_ClassLoader<UCustomAssetFactory>(
		MyAssetCategoryBit,
		FColor::Blue,
		FText::FromString("Custom Asset Factory"),
		FText::FromString("Custom Asset Factory")
	)));*/

	

}

void FMyEditorModule::ShutdownModule()
{
	IModuleInterface::ShutdownModule();

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	AssetTools.UnregisterAssetTypeActions(CustomAssetActions.ToSharedRef());

/*	FAssetToolsModule* AssetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools");

	if (AssetToolsModule != nullptr)
	{
		IAssetTools& AssetTools = AssetToolsModule->Get();

		for (auto Action : RegisteredAssetTypeActions)
		{
			AssetTools.UnregisterAssetTypeActions(Action);
		}
	}*/
}
