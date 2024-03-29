﻿/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/

#include "ProceduralEditorToolkit.h"

#include "CoreUI/DockTab/CollapsibleBoxTab.h"
#include  "Toolkits/AssetEditorToolkit.h"
#include "Framework/Docking/TabManager.h"
#include "ProceduralGeneration/Data/ProceduralGenerationData.h"


FProceduralEditorToolkit::FProceduralEditorToolkit()
{
	
}

FProceduralEditorToolkit::~FProceduralEditorToolkit()
{
	
}

void FProceduralEditorToolkit::Initialize(UProceduralGenerationData* InProceduralAsset, const EToolkitMode::Type Mode,
	const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	EditorTab =SNew(SCollapsibleBoxTab);

	// Register the procedural editor tab with the toolkit host
	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("ProceduralGenerationEditor_Layout_v1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			
			->Split
			(
				FTabManager::NewStack()
				->AddTab(GetTabName(), ETabState::OpenedTab)
				->SetHideTabWell(true)
			)
		);

	TArray<UObject*> ObjectsToEdit;
	ObjectsToEdit.Add(InProceduralAsset);

	FAssetEditorToolkit::InitAssetEditor(
		Mode,
		InitToolkitHost,
		GetToolkitFName(),
		Layout,
		true /*bCreateDefaultStandaloneMenu*/,
		true /*bCreateDefaultToolbar*/,
		InProceduralAsset /*ObjectToEdit*/
		
	);
	
}

void FProceduralEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	// Register the spawner for our tab widget
	const auto SpawnTab = [this](const FSpawnTabArgs& Args) -> TSharedRef<SDockTab>
	{
		return SNew(SDockTab)
			.TabRole(ETabRole::NomadTab)
			.Label(FText::FromString("My Tab"))
			.ContentPadding(5.0f)
			[
				EditorTab.ToSharedRef()
			];
	};
	
	
	// Register the tab spawner
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
}

FName FProceduralEditorToolkit::GetToolkitFName() const
{
	return EditorName;
}

FText FProceduralEditorToolkit::GetBaseToolkitName() const
{
	return FText::FromString("ProceduralEditor");
}

FLinearColor FProceduralEditorToolkit::GetWorldCentricTabColorScale() const
{
	return FLinearColor::Yellow;
}

void FProceduralEditorToolkit::SaveAsset_Execute()
{
	FAssetEditorToolkit::SaveAsset_Execute();
}

FName FProceduralEditorToolkit::GetTabName() const
{
	return EditorTab->TabName;
}

void FProceduralEditorToolkit::CreateProceduralEditorTab(const TSharedPtr<SDockTab>& Tab)
{
	Tab->SetContent(EditorTab.ToSharedRef());
	
}

void FProceduralEditorToolkit::SaveAssetAs_Execute()
{
	FAssetEditorToolkit::SaveAssetAs_Execute();
}
