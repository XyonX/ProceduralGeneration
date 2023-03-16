// Fill out your copyright notice in the Description page of Project Settings
#pragma once

#include "CoreMinimal.h"
#include "ToolKits/AssetEditorToolkit.h"

class FProceduralEditorToolkit : public FAssetEditorToolkit
{
public:
	// Constructor
	FProceduralEditorToolkit();

	// Destructor
	virtual ~FProceduralEditorToolkit();

	// Initialize the editor toolkit
	virtual void Initialize(UObject* InAsset, const EToolkitMode::Type InMode, const TSharedPtr<class IToolkitHost>& InToolkitHost) ;
	

	// Extend the toolbar with additional functionality
	virtual void ExtendToolbar();

	// Create the main tab layout of the editor toolkit
	//virtual void CreateToolkitTabs(TSharedPtr<class FTabManager> TabManager) ;

	// Get the name of the editor toolkit
	virtual FName GetToolkitFName() const override;

	// Get the label of the editor toolkit
	virtual FText GetBaseToolkitName() const override;

	// Get the object being edited by this editor toolkit
	virtual UObject* GetEditingObject()    ;

	// Save the asset being edited by this editor toolkit
	virtual void SaveAsset_Execute() override;

	FName DefaultName ;
	FText DefaultText ;
};
