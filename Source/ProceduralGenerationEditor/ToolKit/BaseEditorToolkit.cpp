// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEditorToolkit.h"

#include <dbghelp.h>

#include "AssetTypeCategories.h"
#include "BlueprintEditor.h"
#include "EditorStyleSet.h"
#include "WorkspaceMenuStructure.h"
#include "WorkspaceMenuStructureModule.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "ProceduralGenerationEditor/Layout/BaseActorEditorLayout.h"

#define LOCTEXT_NAMESPACE "Editor Window"

void FBaseEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
	
	// Register the blueprint editor tab spawner
	InTabManager->RegisterTabSpawner("Kismet2", FOnSpawnTab::CreateSP(this, &FBaseEditorToolkit::SpawnBlueprintEditorTab))
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Modes"))
		.SetDisplayName(FText::FromString("Blueprint Editor"))
		.SetGroup(WorkspaceMenu::GetMenuStructure().GetLevelEditorCategory();

	// Register the details tab spawner
	InTabManager->RegisterTabSpawner("Details", FOnSpawnTab::CreateSP(this, &FMyCustomEditorToolkit::SpawnDetailsTab))
		.SetDisplayName(FText::FromString("Details"))
		.SetGroup(WorkspaceMenu::GetMenuStructure().GetLevelEditorCategory())
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));

	
}

void FBaseEditorToolkit::Init(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	//create the layout
	static const TSharedRef<FTabManager::FLayout> EditorLayout =FBaseActorEditorLayout::EditorLayout();
	
	// Initialize the toolkit
	InitAssetEditor(
	Mode,
	InitToolkitHost,
	FName("Procedural Editor"),
	EditorLayout,
	true,
	true,
	TArray<UObject*>(),
	false,      
	false
	
);

	// Activate the initial layout
	const bool bNewlyCreated = (GetEditingObjects().Num() == 1 && GetEditingObjects()[0] == GetEditingObject());
	if (bNewlyCreated)
	{
		// If this is a newly created asset, activate the properties tab
		TSharedPtr<FTabManager> TabManager = GetToolkitHost()->GetTabManager();
		TabManager->TryInvokeTab(FName("BlueprintEditor"));
		TabManager->TryInvokeTab(FName("Details"));

	}

}
	


void FBaseEditorToolkit::OpenEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	RegisterTabSpawners(FGlobalTabmanager::Get());
}


TSharedRef<SDockTab> FBaseEditorToolkit::SpawnBlueprintEditorTab(const FSpawnTabArgs& Args)
{
	/*//FBlueprintEditorModule::CreateBlueprintEditor(this)
	// Get the Kismet2 tab widget from the engine
	TSharedPtr<SDockTab> Kismet2Tab = FGlobalTabmanager::Get()->FindExistingLiveTab(FName("Kismet2"));
    
	if (Kismet2Tab.IsValid())
	{
		// If the tab exists, return it
		return Kismet2Tab.ToSharedRef();
	}
	// Get the blueprint graph editor module
	FBlueprintEditorModule& BlueprintEditorModule = FModuleManager::GetModuleChecked<FBlueprintEditorModule>("Kismet");

	// Create an instance of the blueprint graph editor
	//UBlueprint* Blueprint = ...; // Get the blueprint you want to edit
	TSharedRef<IBlueprintEditor> BlueprintEditor = BlueprintEditorModule.CreateBlueprintEditor(
		EToolkitMode::Standalone, TSharedPtr<IToolkitHost>(), EAssetTypeCategories::Blueprint, false);

	// Return the blueprint graph editor as a dock tab
	return BlueprintEditor->GetGraphEditorTab();*/
	// Get the blueprint object that you want to edit
	UBlueprint* BlueprintObj = ...;

	// Create an instance of the blueprint editor
	TSharedPtr<SGraphEditor> GraphEditor = FKismetEditorUtilities::CreateBlueprintEditorInstance(BlueprintObj, GetTabId(), SpawnTabArgs.GetOwnerTab().ToSharedRef());

	// Create a new tab with the graph editor as content
	TSharedRef<SDockTab> NewTab = SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		.Label(FText::FromString(TEXT("My Tab")))
		.ContentPadding(2.0f)
		[
			GraphEditor.ToSharedRef()
		];

	return NewTab;

}

#undef LOCTEXT_NAMESPACE
