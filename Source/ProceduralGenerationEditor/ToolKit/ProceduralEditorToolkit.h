// Fill out your copyright notice in the Description page of Project Settings
#pragma once

#include "CoreMinimal.h"
#include "ProceduralGenerationEditor/DockTab/ProceduralEditorTab.h"
#include "Toolkits/AssetEditorToolkit.h"

class UProceduralGenerationData;

class FProceduralEditorToolkit : public FAssetEditorToolkit
{
public:
	// Constructor
	FProceduralEditorToolkit();

	// Destructor
	virtual ~FProceduralEditorToolkit();

	// Initialize the asset editor
	void Initialize(UProceduralGenerationData* InProceduralAsset, const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost);

	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;

	// Get the name of the editor toolkit
	FString GetToolkitName() const override;

	// Get the default layout for the editor toolkit
	FName GetToolkitFName() const override;

	// Get the tab identifier for the procedural editor tab
	FName GetTabName() const;
	


	//ADDITIONAL OVERRIDES
	virtual void SaveAsset_Execute() override;
	virtual void SaveAssetAs_Execute() override;
	
	

	
	
private:
	// Pointer to the procedural asset being edited
	UProceduralGenerationData* ProceduralAsset;
	TSharedPtr<SProceduralEditorTab>EditorTab ;
	// Create the procedural editor tab
	void CreateProceduralEditorTab(const TSharedPtr<class SDockTab>& Tab);
	
};
