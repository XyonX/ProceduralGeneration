#pragma once
#include "ProceduralGenerationEditor.h"

#include "AssetToolsModule.h"
#include "CoreUI/DockTab/GenerationControllerTab.h"
#include "ProceduralGeneration/CustomAssetType/Actions/BaseAssetActions.h"
#include "Toolkits/AssetEditorToolkit.h"


void FMyEditorModule::StartupModule()
{
	IModuleInterface::StartupModule();

	SGenerationControllerTab::RegisterTabSpawner();

	RegisterAssetAction();


}

void FMyEditorModule::ShutdownModule()
{
	IModuleInterface::ShutdownModule();
	UnRegisterAssetAction();

	// Get a list of all open asset editor toolkits
	//TArray<UObject*> OpenToolkits = FAssetEditorToolkit::GetMod
	
	//FGlobalTabmanager::Get()->UnregisterTabSpawner()

	// Get a reference to the asset editor module
	//FAssetEditorModule& AssetEditorModule = FModuleManager::GetModuleChecked<FAssetEditorModule>("AssetEditor");

}

void FMyEditorModule::RegisterAssetAction()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	CustomAssetActions = MakeShareable(new FBaseActorActions);

	AssetTools.RegisterAssetTypeActions(CustomAssetActions.ToSharedRef());

	// Add custom asset category
	EAssetTypeCategories::Type CustomAssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("Procedural Actor")), FText::FromString("Procedural Actor"));
}

void FMyEditorModule::UnRegisterAssetAction()
{

	FAssetToolsModule* AssetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools");
	if (AssetToolsModule != nullptr)
	{
		IAssetTools& AssetTools = AssetToolsModule->Get();
		AssetTools.UnregisterAssetTypeActions(CustomAssetActions.ToSharedRef());
	}

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


void FMyEditorModule::RegisterMenuExtensions()
{
	MenuExtensibilityManager = MakeShareable(new FExtensibilityManager);
	ToolBarExtensibilityManager = MakeShareable(new FExtensibilityManager);
}

void FMyEditorModule::UnregisterMenuExtensions()
{
	MenuExtensibilityManager.Reset();
	ToolBarExtensibilityManager.Reset();
}
