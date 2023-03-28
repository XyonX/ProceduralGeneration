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
	//virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual FName GetToolkitFName() const override {return FName("Editor Toolkit");};
	virtual FText GetBaseToolkitName() const override{return  FText::FromString("Editor Toolkit");};
	//virtual FText GetToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override{return  FText::FromString("This is the Custom Toolkit");};
	virtual FString GetWorldCentricTabPrefix() const override{ return TEXT("M_Toolkit");};
	virtual bool IsAssetEditor() const override{return true;};
	virtual FLinearColor GetWorldCentricTabColorScale() const override{return FLinearColor(1.0,1.0,1.0,1.0);};
	//virtual void SaveAsset_Execute() override;
	//virtual void SaveAssetAs_Execute() override;
	virtual bool OnRequestClose() override{return true;};
	
public:
	FBaseEditorToolkit();
	~FBaseEditorToolkit();
	
	//SETUP THE UI
	void Init(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost,const TArray<UObject*>& InObjects);


	
private:
	// Member variables
	TSharedPtr<class FViewportClient> ViewportClient;
	TSharedPtr<class IDetailsView> PropertyView;
	TSharedPtr<class FUICommandList> ToolkitCommands;
	UBaseActor*BaseActor;
	//UMyCustomTexture* MyCustomTexture;
	
	TSharedRef<SDockTab>  SpawnBlueprintEditorTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab>  SpawnDetailsPanel(const FSpawnTabArgs& Args);
	
};
	