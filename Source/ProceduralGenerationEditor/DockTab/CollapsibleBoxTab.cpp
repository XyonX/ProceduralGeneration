#include "CollapsibleBoxTab.h"

#include "EditorStyleSet.h"
#include "ProceduralGenerationEditor/UI/DetailsPanelElements/SCollapsibleBox_01.h"
#include "Internationalization//Internationalization.h"
#include "WorkspaceMenuStructure/Public/WorkspaceMenuStructure.h"
#include "WorkspaceMenuStructure/Public/WorkspaceMenuStructureModule.h"

#define LOCTEXT_NAMESPACE "ProceduralEditorLocalization"

//  Defining   the  
const FName SCollapsibleBoxTab::TabName(TEXT("CollapsibleBoxTab"));


SCollapsibleBoxTab::SCollapsibleBoxTab()
{
	
}

void SCollapsibleBoxTab::Construct(const FArguments& InArgs)
{
	// Create an instance of your widget
	MyWidget = SNew(SCollapsibleBox_01);

	// Add the widget to a SBox so we can control the size of the widget
    TSharedPtr<SBox> MyBox = SNew(SBox)
        .WidthOverride(500.0f)
        .HeightOverride(500.0f)
        [
            MyWidget.ToSharedRef()
        ];

	// Set the content of the dockable tab to the SBox containing the widget
	this->SetContent(MyBox.ToSharedRef());
}

void SCollapsibleBoxTab::RegisterTabSpawner()
{
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
		"Collapsible Box Tab ",
		FOnSpawnTab::CreateStatic(&SCollapsibleBoxTab::SpawnTab))
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details"))
		.SetTooltipText(LOCTEXT("MyTabTooltip", "Open MyTab"))
		.SetGroup(WorkspaceMenu::GetMenuStructure().GetDeveloperToolsMiscCategory())
		.SetDisplayName(LOCTEXT("Collapsible Box Tab", "CBOX"));
	
}

TSharedRef<SDockTab> SCollapsibleBoxTab::SpawnTab(const FSpawnTabArgs& SpawnTabArgs)
{
	TSharedRef<SCollapsibleBoxTab> NewTab = SNew(SCollapsibleBoxTab);

	return NewTab;
}

FName SCollapsibleBoxTab::GetTabIdentifier() const
{
	return TabName;
}

FReply SCollapsibleBoxTab::GenerateProceduralContent()
{
	// TODO: Implement procedural content generation logic here
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE