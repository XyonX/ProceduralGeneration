// Fill out your copyright notice in the Description page of Project Settings
#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"



class FBaseEditorToolkit : public FAssetEditorToolkit
{

	// Initialize the asset editor
	//void Initialize(UProceduralGenerationData* InProceduralAsset, const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost);
	
	
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
	
	
	void Init ();
	
	
	private:
	// Member variables
	TSharedPtr<class FViewportClient> ViewportClient;
	TSharedPtr<class IDetailsView> PropertyView;
	TSharedPtr<class FUICommandList> ToolkitCommands;
	//UMyCustomTexture* MyCustomTexture;
	
};
	