#pragma once
#include "ProceduralGenerationEditor.h"
#include "AssetRegistry/IAssetRegistry.h"
#ifndef CUSTOM_ASSET_ACTIONS_H
#define CUSTOM_ASSET_ACTIONS_H

#include "CustomAssetType/Actions/CustomAssetActions.h"

#endif // CUSTOM_ASSET_ACTIONS_H


#include "AssetToolsModule.h"
#include "CollectionManagerModule.h"
#include "CollectionManagerTypes.h" 
#include "EditorStyleSet.h"
#include "IAssetTools.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "CustomAssetType/AssetFactory/TestAssetFactory.h"
//#include "Interfaces/IPluginManager.h"


#define LOCTEXT_NAMESPACE "FTestAssetEditorModule"

void FMyEditorModule::StartupModule()
{
    RegisterAssetTools();
    RegisterMenuExtensions();
    RegisterSettings();
    
}

void FMyEditorModule::ShutdownModule()
{
    UnregisterAssetTools();
    UnregisterMenuExtensions();
    UnregisterSettings();
}

bool FMyEditorModule::SupportsDynamicReloading()
{
    return IModuleInterface::SupportsDynamicReloading();
}

TSharedPtr<FExtensibilityManager> FMyEditorModule::GetMenuExtensibilityManager()
{
    return MenuExtensibilityManager;
}

TSharedPtr<FExtensibilityManager> FMyEditorModule::GetToolBarExtensibilityManager()
{
    return ToolBarExtensibilityManager;
}

void FMyEditorModule::RegisterAssetTools()
{
    IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

   RegisterAssetTypeAction(AssetTools, MakeShareable(new FMyCustomAssetActions));
}

void FMyEditorModule::UnregisterAssetTools()
{
    FAssetToolsModule* AssetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools");

    if (AssetToolsModule != nullptr)
    {
        IAssetTools& AssetTools = AssetToolsModule->Get();

        for (auto Action : RegisteredAssetTypeActions)
        {
            AssetTools.UnregisterAssetTypeActions(Action);
        }
    }
}

void FMyEditorModule::RegisterAssetTypeAction(IAssetTools& AssetTools, const TSharedRef<IAssetTypeActions>& Action)
{
    AssetTools.RegisterAssetTypeActions(Action);
    
    RegisteredAssetTypeActions.Add(Action);
    ConfigureDirectory(AssetTools);
}

void FMyEditorModule::RegisterAssetFaccory()
{
    // Register the asset factory with the asset tools module
    //UTestAssetFactory* TestAssetFactory = NewObject<UTestAssetFactory>();
    //AssetTools.RegisterAssetTypeActions(MakeShareable(new FAssetTypeActions_TestAsset(TestAssetFactory)));
}

void FMyEditorModule::RegisterSettings()
{
    ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

    if (SettingsModule != nullptr)
    {
       // ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Editor", "Plugins", "TextAsset",
            //LOCTEXT("TextAssetSettingsName", "Text Asset"),
            //LOCTEXT("TextAssetSettingsDescription", "Configure the Text Asset plug-in."),
           // GetMutableDefault<UTextAssetEditorSettings>()
       // );
    }
}
void FMyEditorModule::UnregisterSettings()
{
    ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

    if (SettingsModule != nullptr)
    {
        SettingsModule->UnregisterSettings("Editor", "Plugins", "TextAsset");
    }
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

void FMyEditorModule::ConfigureDirectory(const IAssetTools& AssetTools)
{
 /*   // Get the plugin's base directory
    FString BaseDir = IPluginManager::Get().FindPlugin("ProceduralGeneration")->GetBaseDir();

    // Add an auto-import directory
    FString AutoImportDir = FPaths::Combine(BaseDir, TEXT("Content"));

    //LOAD thew Module and register
    IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();
    AssetRegistry.Get()->Get()->AddPath(AutoImportDir);*/

}
