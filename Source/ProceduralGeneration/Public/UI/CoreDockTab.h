#pragma once

#include "CoreMinimal.h"
#include "Widgets/Docking/SDockTab.h"

class SCoreDockTab : public SDockTab
{
public:
	SLATE_BEGIN_ARGS(SCoreDockTab){}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
		SDockTab::Construct(
			SDockTab::FArguments()
				.TabRole(ETabRole::NomadTab)
				//.Content()
		);
	}
};

