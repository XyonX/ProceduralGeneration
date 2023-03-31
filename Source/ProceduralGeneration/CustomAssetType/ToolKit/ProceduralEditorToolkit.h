// Fill out your copyright notice in the Description page of Project Settings
#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

class UProceduralGenerationData;
class SCollapsibleBoxTab;


class PROCEDURALGENERATION_API FProceduralEditorToolkit : public FAssetEditorToolkit
{
	
public:
	
	// Constructor
	FProceduralEditorToolkit();
	// Destructor
	virtual ~FProceduralEditorToolkit();

	
	// Initialize the asset editor
	void Initialize(UProceduralGenerationData* InProceduralAsset, const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost);
	
	//OVERRIDES
	//Register Tab Spawner
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	// Get the default layout for the editor toolkit
	virtual FName GetToolkitFName() const override;
	//get base toolkit name
	virtual FText GetBaseToolkitName() const override;
	// Get the default layout for the editor toolkit
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	//ADDITIONAL OVERRIDES
	virtual void SaveAsset_Execute() override;
	virtual void SaveAssetAs_Execute() override;
	
	
	//CLASS GETTER
	// Get the tab identifier for the procedural editor tab
	FName GetTabName() const;
	
private:
	// Pointer to the procedural asset being edited
	UProceduralGenerationData* ProceduralAsset;
	TSharedPtr<SCollapsibleBoxTab>EditorTab ;
	// Create the procedural editor tab
	void CreateProceduralEditorTab(const TSharedPtr<class SDockTab>& Tab);
	FName EditorName =  FName("ProceduralEditor");
	
};
