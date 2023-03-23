// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEditorToolkit.h"

#include "ProceduralGenerationEditor/Layout/BaseActorEditorLayout.h"

#define LOCTEXT_NAMESPACE "Editor Tab"

void FBaseEditorToolkit::Init()
{
	// Create the viewport client
	ViewportClient = MakeShareable(new FViewportClient());

	// Create the property view
	//PropertyView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);

	// Create the command list
	ToolkitCommands = MakeShareable(new FUICommandList);

	// Set up the UI
	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout =  FBaseActorEditorLayout::EditorLayout();

	// Initialize the toolkit
	InitAssetEditor(
		EToolkitMode::Standalone,
		nullptr,
		FName("MyCustomTextureEditor"),
		StandaloneDefaultLayout,
		true,
		true
	);
}

void FBaseEditorToolkit::InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost,
	UObject* ObjectToEdit)
{
	// Save a reference to the object that we're editing
	BaseActor = Cast<UBaseActor>(ObjectToEdit);

	// Create the main widget for the editor
	SAssignNew(MainWidget, SMyCustomEditorWidget, MyAsset)
		.OnSaveClicked(this, &FMyCustomEditorToolkit::OnSave)
		.OnCancelClicked(this, &FMyCustomEditorToolkit::OnCancel);

	// Initialize the toolkit
	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, FName("MyCustomEditor"), GetDefaultLayout(), true, true, ObjectToEdit);

	// Add the main widget to the editor window
	AddWidget(MainWidget.ToSharedRef());
}
}
