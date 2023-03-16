// Fill out your copyright notice in the Description page of Project Settings.


#include "SMainUI.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
FonButtonClick SMainUI::ButtonClickDelegate;
void SMainUI::Construct(const FArguments& InArgs)
{
	ButtonClickDelegate.BindSP(this, &SMainUI::OnButtonClicked);

	ChildSlot
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("My Custom Panel")))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SButton)
				.Text(FText::FromString(TEXT("Button")))
				//.OnClicked(this, &SMyCustomPanelWidget::HandleButtonClick)
				.OnClicked_Static(&HandleButtonClick)
			]
		];
}

FReply SMainUI::HandleButtonClick()
{
	if(ButtonClickDelegate.IsBound() )
	{
		bool bHandled = ButtonClickDelegate.Execute();
		if (bHandled)
		{
			return FReply::Handled();
		}
	}
	return FReply::Unhandled();
}

bool SMainUI::OnButtonClicked()
{
	return  true;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
