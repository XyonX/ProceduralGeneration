// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEditorToolkit.h"
#include "BlueprintEditor.h"
#include "EditorStyleSet.h"
#include "WorkspaceMenuStructure.h"
#include "WorkspaceMenuStructureModule.h"
#include "CoreUI/BlueprintGraph/EventGraph/CustomEVGraph.h"
#include "CoreUI/DockTab/DetailsPanelTab.h"
#include "CoreUI/Layout/BaseActorEditorLayout.h"
#include "Kismet2/KismetEditorUtilities.h"

#define LOCTEXT_NAMESPACE "Editor Window"

void FBaseEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
	/*
	// Register the blueprint editor tab spawner
	InTabManager->RegisterTabSpawner("Kismet2", FOnSpawnTab::CreateSP(this, &FBaseEditorToolkit::SpawnBlueprintEditorTab))
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Modes"))
		.SetDisplayName(FText::FromString("Blueprint Editor"))
		.SetGroup(WorkspaceMenu::GetMenuStructure().GetLevelEditorCategory());*/
	
	// Register the details tab spawner
	InTabManager->RegisterTabSpawner("Details", FOnSpawnTab::CreateSP(this, &FBaseEditorToolkit::SpawnDetailsPanel))
		.SetDisplayName(FText::FromString("Details"))
		.SetGroup(WorkspaceMenu::GetMenuStructure().GetLevelEditorCategory())
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));
	
}

// FBaseEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager)
//{
/*	// Unregister the tab spawner for the Blueprint Editor
	//TabManager->UnregisterTabSpawner("Kismet2");

	// Unregister the tab spawner for the Details panel
	InTabManager->UnregisterTabSpawner("Details");

	// Call the base class implementation to unregister any additional tab spawners
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);*/
//}

FBaseEditorToolkit::FBaseEditorToolkit()
{
}
FBaseEditorToolkit::~FBaseEditorToolkit()
{
	//UnregisterTabSpawners(FGlobalTabmanager::Get());
}

void FBaseEditorToolkit::Init(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, const TArray<UObject*>& InObjects)
{

	// Register the tab spawners for the editor
	RegisterTabSpawners(FGlobalTabmanager::Get());
	
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
	InObjects,
	false,      
	false
	
	);

}



TSharedRef<SDockTab> FBaseEditorToolkit::SpawnBlueprintEditorTab(const FSpawnTabArgs& Args)
{
	// Create a new instance of our custom editor widget
	TSharedRef<SCustomEVGraph> CustomEditorWidget = SNew(SCustomEVGraph);

	// Wrap the widget in a dock tab and return it
	return SNew(SDockTab)
		.TabRole(ETabRole::MajorTab)
		.ContentPadding(0)
		.Label(LOCTEXT("MyCustomEditorTabTitle", "My Custom Editor"))
		[
			CustomEditorWidget
		];

}

TSharedRef<SDockTab> FBaseEditorToolkit::SpawnDetailsPanel(const FSpawnTabArgs& Args)
{
	// Create a new instance of our custom editor widget
	TSharedRef<SDetailsPanelTab> CustomEditorWidget = SNew(SDetailsPanelTab);

	// Wrap the widget in a dock tab and return it
	return SNew(SDockTab)
		.TabRole(ETabRole::MajorTab)
		.ContentPadding(0)
		.Label(LOCTEXT("MyCustomEditorTabTitle", "My Custom Editor"))
		[
			CustomEditorWidget
		];
}

#undef LOCTEXT_NAMESPACE
