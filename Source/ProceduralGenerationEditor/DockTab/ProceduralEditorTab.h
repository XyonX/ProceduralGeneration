#pragma once

#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SScrollBox.h"

class SProceduralEditorTab : public SDockTab
{
public:
	SLATE_BEGIN_ARGS(SProceduralEditorTab)
	{}

	SLATE_END_ARGS()

	SProceduralEditorTab();

	//THIS NAME IS FOR  IDENTIFY THIS ACTS   AS A  IDENTIFIER
	static const FName TabName;

	// Get the tab identifier
	FName GetTabIdentifier() const;

	void Construct(const FArguments& InArgs);

private:
	FReply GenerateProceduralContent();
};
