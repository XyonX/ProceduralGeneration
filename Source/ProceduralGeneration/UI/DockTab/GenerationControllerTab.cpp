// Fill out your copyright notice in the Description page of Project Settings.


#include "GenerationControllerTab.h"
#include "EditorStyleSet.h"
#include "SControllerTab.h"
#include "Internationalization//Internationalization.h"
#include "WorkspaceMenuStructure/Public/WorkspaceMenuStructure.h"
#include "WorkspaceMenuStructure/Public/WorkspaceMenuStructureModule.h"
#include "SlateOptMacros.h"
#include "Widgets/Layout/SExpandableArea.h"
#include "Widgets/Input/SSpinBox.h"


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
	SNew(SBox)
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Center)
	[
		
	SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		.AutoHeight()
		[
			SNew(SExpandableArea)
			.HeaderContent()
			[    SNew(STextBlock)
				  .Text(FText::FromString("Duration"))
			]
			.BodyContent()
			[
				SNew(SVerticalBox)
						
				//SLOT 1 
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					  SNew(SHorizontalBox)
					  + SHorizontalBox::Slot()
					  .AutoWidth()
						  [
							SNew(STextBlock)
							.Text(FText::FromString("Emitter Duration:"))
						  ]
					  + SHorizontalBox::Slot()
					  .AutoWidth()
						  [
							SNew(SSpinBox<float>)
							.Value(1.0f)
							.MinValue(0.0f)
							.MaxValue(100.0f)
							//.OnValueChanged(this, &MyClass::OnSpinBoxValueChanged)
						  ]
				]

				//SLOT   2
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
							
				  SNew(SHorizontalBox)
				  + SHorizontalBox::Slot()
				  .AutoWidth()
					  [
						SNew(STextBlock)
						.Text(FText::FromString("Emitter Loop:"))
					  ]
				  + SHorizontalBox::Slot()
				  .AutoWidth()
					  [
						SNew(SCheckBox)
						.IsChecked(false)
					  ]
				]
			]
		]
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		.AutoHeight()
		[
			SNew(SExpandableArea)
			.HeaderContent()
			[    SNew(STextBlock)
				  .Text(FText::FromString("Duration"))
			]
			.BodyContent()
			[
				SNew(SButton)
				.Text(FText::FromString("Generate"))
			]
		]
		
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