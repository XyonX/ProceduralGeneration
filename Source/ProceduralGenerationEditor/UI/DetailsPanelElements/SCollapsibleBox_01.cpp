// Fill out your copyright notice in the Description page of Project Settings.
#include "SCollapsibleBox_01.h"
#include "SlateOptMacros.h"
#include "Widgets/Layout/SExpandableArea.h"
#include "Widgets/Input/SSpinBox.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SCollapsibleBox_01::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SVerticalBox)
		
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SExpandableArea)
			.HeaderContent()
			[    SNew(STextBlock)
	  			.Text(FText::FromString("Duration"))
	  		]
			.BodyContent()
			[
				SNew(SVerticalBox)
				
				//SLOT 1 
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					  SNew(SHorizontalBox)
					  + SHorizontalBox::Slot()
					  .AutoWidth()
						  [
							SNew(STextBlock)
							.Text(FText::FromString("Emitter Duration:"))
						  ]
					  + SHorizontalBox::Slot()
					  .AutoWidth()
						  [
							SNew(SSpinBox<float>)
							.Value(1.0f)
							.MinValue(0.0f)
							.MaxValue(100.0f)
							//.OnValueChanged(this, &MyClass::OnSpinBoxValueChanged)
						  ]
				]

				//SLOT   2
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					
				  SNew(SHorizontalBox)
				  + SHorizontalBox::Slot()
				  .AutoWidth()
					  [
						SNew(STextBlock)
						.Text(FText::FromString("Emitter Loop:"))
					  ]
				  + SHorizontalBox::Slot()
				  .AutoWidth()
					  [
						SNew(SCheckBox)
						.IsChecked(false)
					  ]
				]
			]
]

	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
