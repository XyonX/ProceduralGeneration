// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEditorToolkit.h"

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
	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_CustomTextureEditor_Layout_v1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewStack()->SetSizeCoefficient(0.66f)
				->AddTab("Viewport", ETabState::OpenedTab, FTabManager::FTab()
					//.AddLabel(LOCTEXT("ViewportTabTitle", "Viewport"))
					.SetContent
					(
						SNew(SViewport)
							.ViewportInterface(ViewportClient.ToSharedRef())
					)
				)
				->Split
				(
					FTabManager::NewStack()->SetSizeCoefficient(0.33f)
					->AddTab("Details", ETabState::OpenedTab, FTabManager::FTab()
						.SetLabel(LOCTEXT("DetailsTabTitle", "Details"))
						.SetContent(PropertyView.ToSharedRef())
					)
				)
			)
		);

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
