// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

DECLARE_DELEGATE_RetVal(bool,FonButtonClick)

class PROCEDURALGENERATIONEDITOR_API SMainUI : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMainUI)
		{
		}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	static FonButtonClick  ButtonClickDelegate ;

	static FReply HandleButtonClick ();

	
	bool  OnButtonClicked();
};
