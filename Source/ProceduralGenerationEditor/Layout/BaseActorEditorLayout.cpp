// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActorEditorLayout.h"

#include "K2Node_FunctionEntry.h"
#include "Framework/Docking/TabManager.h"
#include "Kismet2/KismetEditorUtilities.h"
/*
void FBaseActorEditorLayout::CreateBlueprintGraph()
{
	// Create the blueprint asset
	UBlueprint* NewBlueprint = FKismetEditorUtilities::CreateBlueprint(nullptr, TEXT("MyBlueprint"), EBlueprintType::BPTYPE_Normal, UBlueprint::StaticClass(), UEdGraph::StaticClass());
	// Get the graph associated with the EventGraph of the blueprint
	UEdGraph* Graph = NewBlueprint->UbergraphPages[0]->Graphs[0];

	// Add nodes to the graph
	UK2Node_FunctionEntry* FunctionEntryNode = FKismetEditorUtilities::CreateDefaultEventNode<UK2Node_FunctionEntry>(Graph);
	FunctionEntryNode->SetFlags(RF_Transactional);
	FunctionEntryNode->EventReference.SetExternalMember(FName(TEXT("Execute")), UBlueprint::StaticClass());
	FunctionEntryNode->AllocateDefaultPins();

	UK2Node_CallFunction* PrintStringNode = FKismetEditorUtilities::CreateNode<UK2Node_CallFunction>(Graph);
	PrintStringNode->FunctionReference.SetExternalMember(FName(TEXT("PrintString")), UBlueprintFunctionLibrary::StaticClass());
	PrintStringNode->AllocateDefaultPins();
	PrintStringNode->GetInputPin()->DefaultValue = FString(TEXT("Hello World"));

	// Create the editor tab and add the graph to it
	TSharedRef<SDockTab> BlueprintEditorTab = FGlobalTabmanager::Get()->InvokeTab(FName(TEXT("BlueprintEditor")));
	TSharedPtr<SGraphEditor> GraphEditor = FBlueprintEditorUtils::CreateGraphEditorWidget(Graph);
	BlueprintEditorTab->SetContent(GraphEditor.ToSharedRef());

}*/


const TSharedRef<FTabManager::FLayout> FBaseActorEditorLayout::EditorLayout()
{
	
	

	static const TSharedRef<FTabManager::FLayout> Layout =FTabManager::NewLayout("ProceduralGenerationEditor_Layout_v1")
			->AddArea(
				FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
				/*->Split
				(
				FTabManager::NewStack()
					->AddTab("BlueprintEditor", ETabState::OpenedTab)
					->SetHideTabWell(true)
					->SetSizeCoefficient(0.7f)
					->SetForegroundTab(FName("Kismet2"))
				)*/
				->Split
				(
				FTabManager::NewStack()
					->AddTab("Details", ETabState::OpenedTab)
					->SetHideTabWell(true)
					->SetSizeCoefficient(0.3f)
				)
			)
	;

	return Layout;
	
}



/*
FTabManager& FBaseActorEditorLayout::CreateEditorTabs()
{
	static const FName BlueprintEditorTabName("BlueprintEditor");
	static const FName DetailsTabName("Details");

	FTabManager& TabManager = FGlobalTabmanager::Get()->NewTabManager(SharedThis(this));

	TabManager
		->RegisterTabSpawner(BlueprintEditorTabName, FOnSpawnTab::CreateRaw(this, &MyEditorLayout::SpawnBlueprintEditorTab))
		.SetDisplayName(NSLOCTEXT("MyEditorLayout", "BlueprintEditorTabTitle", "Blueprint Editor"))
		.SetGroup(WorkspaceMenu::GetMenuStructure().GetLevelEditorCategory());

	TabManager
		->RegisterTabSpawner(DetailsTabName, FOnSpawnTab::CreateRaw(this, &MyEditorLayout::SpawnDetailsTab))
		.SetDisplayName(NSLOCTEXT("MyEditorLayout", "DetailsTabTitle", "Details"))
		.SetGroup(WorkspaceMenu::GetMenuStructure().GetLevelEditorCategory());

	return TabManager;
}*/
