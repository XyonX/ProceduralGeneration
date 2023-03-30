// Fill out your copyright notice in the Description page of Project Settings.


#include "SControllerTab.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SControllerTab::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(STextBlock)
				.Text(FText::FromString("My Tab"))
			]
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
