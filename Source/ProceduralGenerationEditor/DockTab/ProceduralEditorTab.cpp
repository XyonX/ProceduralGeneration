// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralEditorTab.h"

//  Defining   the  
const FName SProceduralEditorTab::TabName(TEXT("ProceduralEditorTab"));

SProceduralEditorTab::SProceduralEditorTab()
{
	
}

FName SProceduralEditorTab::GetTabIdentifier() const
{
	return TabName;
}

void SProceduralEditorTab::Construct(const FArguments& InArgs)
{
	// Call the parent constructor
	SDockTab::Construct(
		SDockTab::FArguments()
			.TabRole(ETabRole::NomadTab)
			.Label(FText::FromString("Procedural Generation"))
	);

	// This creates the procedural generation layout that will be added to the tab widget
	TSharedRef<SHorizontalBox> ProceduralGenerationLayout = SNew(SHorizontalBox);

	// Add a text block to the layout to display a label
	ProceduralGenerationLayout->AddSlot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Left)
		.Padding(5.0f)
		[SNew(STextBlock)
			.Text(FText::FromString("Name:"))];

	// Add a button to the layout to generate procedural content
	ProceduralGenerationLayout->AddSlot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Right)
		.Padding(5.0f)
		[SNew(SButton)
			.Text(FText::FromString("Generate"))
			.OnClicked(this, &SProceduralEditorTab::GenerateProceduralContent)];

	// Set the content of the tab widget to be the procedural generation layout
	SetContent(ProceduralGenerationLayout);
}

FReply SProceduralEditorTab::GenerateProceduralContent()
{
	// TODO: Implement procedural content generation logic here
	return FReply::Handled();
}
