#pragma once

#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SScrollBox.h"

class SCollapsibleBox_01;

class SCollapsibleBoxTab : public SDockTab
{
public:
	SLATE_BEGIN_ARGS(SCollapsibleBoxTab)
	{}

	SLATE_END_ARGS()

	SCollapsibleBoxTab();
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
	FReply GenerateProceduralContent();
	TSharedPtr<SCollapsibleBox_01>MyWidget ;
};
