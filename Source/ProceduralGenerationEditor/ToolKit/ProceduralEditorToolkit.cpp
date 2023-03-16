// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralEditorToolkit.h"

FProceduralEditorToolkit::FProceduralEditorToolkit()
{
}

FProceduralEditorToolkit::~FProceduralEditorToolkit()
{
}

void FProceduralEditorToolkit::Initialize(UObject* InAsset, const EToolkitMode::Type InMode,
	const TSharedPtr<IToolkitHost>& InToolkitHost)
{
}

void FProceduralEditorToolkit::ExtendToolbar()
{
}



FName FProceduralEditorToolkit::GetToolkitFName() const
{
	return DefaultName;
}

FText FProceduralEditorToolkit::GetBaseToolkitName() const
{
	return DefaultText;
}

UObject* FProceduralEditorToolkit::GetEditingObject()
{
	return nullptr;
}


void FProceduralEditorToolkit::SaveAsset_Execute()
{
	FAssetEditorToolkit::SaveAsset_Execute();
}
