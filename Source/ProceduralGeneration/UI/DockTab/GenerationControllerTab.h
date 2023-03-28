// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class SGenerationControllerTab : public SDockTab
{
public:
	SLATE_BEGIN_ARGS(SGenerationControllerTab) {}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	// Register the dockable tab
	static void RegisterTabSpawner();
	
	// Create an instance of the dockable tab
	static TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& SpawnTabArgs);


	//THIS NAME IS FOR  IDENTIFY THIS ACTS   AS A  IDENTIFIER
	static const FName TabName;
	// Get the tab identifier
	FName GetTabIdentifier() const;
private:
	TSharedPtr<SVerticalBox> Widget;
	
};
				