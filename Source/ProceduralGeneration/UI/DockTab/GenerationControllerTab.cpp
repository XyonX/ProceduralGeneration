// Fill out your copyright notice in the Description page of Project Settings.


#include "GenerationControllerTab.h"
#include "EditorStyleSet.h"
#include "Internationalization//Internationalization.h"
#include "WorkspaceMenuStructure/Public/WorkspaceMenuStructure.h"
#include "WorkspaceMenuStructure/Public/WorkspaceMenuStructureModule.h"


#define LOCTEXT_NAMESPACE "ControllerText"

const FName SGenerationControllerTab::TabName(TEXT("ControllerTab"));

void SGenerationControllerTab::Construct(const FArguments& InArgs)
{
	// Create an instance of your widget
	Widget = SNew(SVerticalBox);

	// Add the widget to a SBox so we can control the size of the widget
	TSharedPtr<SBox> MyBox = SNew(SBox)
		.WidthOverride(100.0f)
		.HeightOverride(500.0f)
		[
			Widget.ToSharedRef()
		];

	// Set the content of the dockable tab to the SBox containing the widget
	this->SetContent(MyBox.ToSharedRef());
}

void SGenerationControllerTab::RegisterTabSpawner()
{
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
		TabName,
		FOnSpawnTab::CreateStatic(&SGenerationControllerTab::SpawnTab))
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details"))
		.SetTooltipText(LOCTEXT("MyTabTooltip", "Open MyTab"))
		.SetGroup(WorkspaceMenu::GetMenuStructure().GetDeveloperToolsMiscCategory())
		.SetDisplayName(LOCTEXT("Collapsible Box Tab", "CBOX"));
	
}

TSharedRef<SDockTab> SGenerationControllerTab::SpawnTab(const FSpawnTabArgs& SpawnTabArgs)
{
	TSharedRef<SGenerationControllerTab> NewTab = SNew(SGenerationControllerTab);
	return NewTab;
}

FName SGenerationControllerTab::GetTabIdentifier() const
{
	return TabName;
}

#undef  LOCTEXT_NAMESPACE