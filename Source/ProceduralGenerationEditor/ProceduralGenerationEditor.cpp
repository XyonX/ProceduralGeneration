#pragma once
#include "ProceduralGenerationEditor.h"

#include "AssetToolsModule.h"
#include "CustomAssetType/Actions/BaseAssetActions.h"
#include "CustomAssetType/AssetFactory/BaseActorFactory.h"

void FMyEditorModule::StartupModule()
{
	IModuleInterface::StartupModule();

	RegisterAssetAction();


}

void FMyEditorModule::ShutdownModule()
{
	IModuleInterface::ShutdownModule();
	UnRegisterAssetAction();

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
	//IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	//AssetTools.UnregisterAssetTypeActions(CustomAssetActions.ToSharedRef());

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

void FMyEditorModule::RegisterToolkit()
{
	// Register the editor toolkit
	FAssetEditorToolkitModule& AssetEditorModule = FModuleManager::LoadModuleChecked<IAssetEditorToolkitModule>("AssetEditorToolkit");
	AssetEditorModule.RegisterAssetEditorToolkit(MakeShareable(new FMyCustomTextureEditorToolkit()));
	
}

void FMyEditorModule::UnRegisterToolkit()
{
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
