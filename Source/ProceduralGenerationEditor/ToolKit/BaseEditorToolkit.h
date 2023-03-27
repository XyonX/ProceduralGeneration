// Fill out your copyright notice in the Description page of Project Settings
#pragma once

#include "CoreMinimal.h"
#include "ProceduralGeneration/Actors/CustomAssetClass/BaseActor.h"
#include "Toolkits/AssetEditorToolkit.h"


struct FTabPayload;

class FBaseEditorToolkit : public FAssetEditorToolkit
{
	
	
	//OVERRIDES
	//Register Tab Spawner
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FText GetToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual bool IsAssetEditor() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual void SaveAsset_Execute() override;
	virtual void SaveAssetAs_Execute() override;
	virtual bool OnRequestClose() override;

public:
	
	//SETUP THE UI
	void Init(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost);
	void  OpenEditor(const TArray< UObject* >& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor);

	
private:
	// Member variables
	TSharedPtr<class FViewportClient> ViewportClient;
	TSharedPtr<class IDetailsView> PropertyView;
	TSharedPtr<class FUICommandList> ToolkitCommands;
	UBaseActor*BaseActor;
	//UMyCustomTexture* MyCustomTexture;


	TSharedRef<SDockTab>  SpawnBlueprintEditorTab(const FSpawnTabArgs& Args);
	
};
	