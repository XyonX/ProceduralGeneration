// Fill out your copyright notice in the Description page of Project Settings.


#include "DetailsPanelTab.h"

FName SDetailsPanelTab::GetTabIdentifier() const
{
	return TabName;
}

void SDetailsPanelTab::Construct(const FArguments& InArgs)
{
	// This creates the procedural generation layout that will be added to the tab widget
	TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox);
	
	// Add a text block to the layout to display a label
	VerticalBox->AddSlot()
		.VAlign(VAlign_Top)
		.HAlign(HAlign_Left)
		.Padding(5.0f)
		[SNew(SButton)
			.Text(FText::FromString("Name:"))];
	
}
