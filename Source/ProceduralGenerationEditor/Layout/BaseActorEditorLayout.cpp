// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActorEditorLayout.h"
#include "Framework/Docking/TabManager.h"

TSharedRef<FTabManager::FLayout> FBaseActorEditorLayout::EditorLayout()
{
	return FTabManager::NewLayout("ProceduralGenerationEditor_Layout_v1")
			->AddArea(
				FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
				->Split(
					FTabManager::NewStack()
					->AddTab(GetTabName(), ETabState::OpenedTab)
					->SetHideTabWell(true)
				)
			);
	
}
