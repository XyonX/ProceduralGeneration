#pragma once

#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SScrollBox.h"

class SProceduralEditorTab : public SDockTab
{
public:
	SLATE_BEGIN_ARGS(SProceduralEditorTab)
	{}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	FReply GenerateProceduralContent();
};
