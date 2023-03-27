// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DetailsPanelTab.generated.h"

class SDetailsPanelTab : public SDockTab
{
public:
	SLATE_BEGIN_ARGS(SDetailsPanelTab) {}
	SLATE_END_ARGS()

	//THIS NAME IS FOR  IDENTIFY THIS ACTS   AS A  IDENTIFIER
	inline static const FName TabName  ="PDT_DetailsPanel";

	// Get the tab identifier
	FName GetTabIdentifier() const;

	void Construct(const FArguments& InArgs);
};
