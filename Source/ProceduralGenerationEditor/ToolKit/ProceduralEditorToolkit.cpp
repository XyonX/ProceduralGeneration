// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralEditorToolkit.h"
#include  "Toolkits/AssetEditorToolkit.h"

FProceduralEditorToolkit::FProceduralEditorToolkit()
{
/*	EditorTab =SNew(SProceduralEditorTab);

	// Add the tab to the tab manager
	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("MyLayout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->Split
			(
				FTabManager::NewStack()
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
				->SetHideTabWell(true)
			)
			->Split
			(
				FTabManager::NewStack()
				->AddTab(EditorTab->GetTabId(), ETabState::OpenedTab)
			)
		);
	// Register the tab spawners
	FAssetEditorToolkit::InitAssetEditor(
		EToolkitMode::Standalone,
		nullptr,
		FName(TEXT("MyEditor")),
		Layout,
		true,
		true
	);*/
}

FProceduralEditorToolkit::~FProceduralEditorToolkit()
{
	
}

void FProceduralEditorToolkit::Initialize(UProceduralGenerationData* InProceduralAsset, const EToolkitMode::Type Mode,
	const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	EditorTab =SNew(SProceduralEditorTab);

	// Register the procedural editor tab with the toolkit host
	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("ProceduralGenerationEditor_Layout_v1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)->Split
			(
				FTabManager::NewStack()->AddTab(GetTabName(), ETabState::OpenedTab)->SetHideTabWell(true)
			)
		);
/*
	FAssetEditorToolkit::InitAssetEditor(
		Mode,
		InitToolkitHost,
		GetToolkitFName(),
		Layout,
		true /*bCreateDefaultStandaloneMenu*/,
		//true /*bCreateDefaultToolbar*/,
		//InProceduralAsset /*ObjectToEdit*/
	//);
	
}

void FProceduralEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager)
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
	
	FAssetEditorToolkit::RegisterTabSpawners(EditorTab->GetTabIdentifier(), SpawnTab);
}

void FProceduralEditorToolkit::CreateProceduralEditorTab(const TSharedPtr<SDockTab>& Tab)
{
	Tab->SetContent(EditorTab.ToSharedRef());
	
}
