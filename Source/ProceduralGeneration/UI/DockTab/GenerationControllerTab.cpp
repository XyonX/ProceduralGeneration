// Fill out your copyright notice in the Description page of Project Settings.


#include "GenerationControllerTab.h"
#include "EditorStyleSet.h"
#include "SControllerTab.h"
#include "Internationalization//Internationalization.h"
#include "WorkspaceMenuStructure/Public/WorkspaceMenuStructure.h"
#include "WorkspaceMenuStructure/Public/WorkspaceMenuStructureModule.h"


#define LOCTEXT_NAMESPACE "ControllerText"

 FName SGenerationControllerTab::TabName(TEXT("ControllerTab"));

SGenerationControllerTab::SGenerationControllerTab()
{
}

void SGenerationControllerTab::Construct(const FArguments& InArgs)
{
	/*// Create an instance of your widget
	Widget = SNew(SVerticalBox);

	// Add some content to the widget using AddSlot
	Widget->AddSlot()
		.AutoHeight()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
			[SNew(STextBlock)
			.Text(FText::FromString("Hello, World!"))
			];


	
	// Add the widget to a SBox so we can control the size of the widget
	
	TSharedPtr<SBox> MyBox = SNew(SBox)
		.WidthOverride(100.0f)
		.HeightOverride(500.0f)
		[
			Widget.ToSharedRef()
		];

	// Set the content of the dockable tab to the SBox containing the widget
	this->SetContent(MyBox.ToSharedRef());*/


	ChildSlot
	
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(STextBlock)
				.Text(FText::FromString("My Tab"))
			]
		];
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
	// Create an instance of your widget
	TSharedPtr<SControllerTab> MyWidget = SNew(SControllerTab);

	// Add the widget to a SBox so we can control the size of the widget
	TSharedPtr<SBox> MyBox = SNew(SBox)
		.WidthOverride(100.0f)
		.HeightOverride(500.0f)
		[
			MyWidget.ToSharedRef()
		];

	// Set the content of the dockable tab to the SBox containing the widget
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		.Label(LOCTEXT("MyTabLabel", "My Tab"))
		[
			MyBox.ToSharedRef()
		];
}

FName SGenerationControllerTab::GetTabIdentifier() const
{
	return TabName;
}

#undef  LOCTEXT_NAMESPACE