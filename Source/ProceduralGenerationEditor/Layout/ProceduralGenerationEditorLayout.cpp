// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralGenerationEditorLayout.h"

#include "AssetToolsModule.h"
//#include "UI/SMainUI.h"
#include "Framework/Docking/TabManager.h"
#include "Widgets/Docking/SDockTab.h"
#include "EditorStyleSet.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Toolkits/AssetEditorModeUILayer.h"
#include "Framework/Docking/TabManager.h"
#include "Toolkits/IToolkitHost.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"

ProceduralGenerationEditorLayout::ProceduralGenerationEditorLayout()  : FGlobalTabmanager::FLayout("CustomEditorLayout")
{
	{
		FTabManager::NewLayout("MyCustomWindowLayout")
			->AddArea
			(
				FTabManager::NewPrimaryArea()
				->Split
				(
					FTabManager::NewStack()
					->AddTab("MyCustomPanel", ETabState::OpenedTab)
				)
			);

		//MyCustomAssetEditorToolkit* MyToolkit = static_cast<MyCustomAssetEditorToolkit*>(AssetEditorToolkit.Get());
		//IToolkitHost* ToolkitHost = MyToolkit->GetToolkitHost();

		// Add SMainUI panel widget to the tab
		//TSharedRef<SMainUI> MainUI = SNew(SMainUI);
		//GetTabManager().InsertNewDocumentTab("MyCustomPanel", FTabManager::ESearchPreference::PreferLiveTab, MainUI);
		//FGlobalTabmanager::Get()->InsertNewDocumentTab()
	}
}

ProceduralGenerationEditorLayout::~ProceduralGenerationEditorLayout()
{
	
}
