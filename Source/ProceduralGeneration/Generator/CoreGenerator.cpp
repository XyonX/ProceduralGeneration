// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreGenerator.h"
#include "EditorStyleSet.h"
#include "Widgets/Layout/SExpandableArea.h"
#include "PropertyEditorModule.h"
#include "PropertyCustomizationHelpers.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "CoreUI/DockTab/GenerationControllerTab.h"
#include "Widgets/Layout/SScrollBox.h"

#define LOCTEXT_NAMESPACE "Editor Window"

/*
TArray<UTile*> UCoreGenerator::Run()
{

}*/

UCoreGenerator::UCoreGenerator()
{
	
}

void UCoreGenerator::Init(TSharedPtr<SGenerationControllerTab> InTab)
{
	ControllerTab=InTab;
}

void UCoreGenerator::AddUIEntry()
{
	if(ControllerTab ==nullptr)
	{
		return;
	}
	// Get the vertical box widget
	TSharedPtr<SVerticalBox> VerticalBoxWidget = StaticCastSharedRef<SVerticalBox>(ControllerTab->GetWidget().ToSharedRef());

	if(VerticalBoxWidget==nullptr)
		return;

	// Add a new slot to the vertical box and create a collapsible box widget inside the slot
	VerticalBoxWidget->AddSlot()
					.VAlign(VAlign_Top)
					.HAlign(HAlign_Fill)
	
				[
					SNew(SExpandableArea)
					.BorderBackgroundColor(FLinearColor(1.0f, 1.0f, 1.0f, 0.5f))
					.BodyBorderBackgroundColor(FLinearColor(0.25f, 0.25f, 0.25f, 0.5f))
					.HeaderContent()
					[
							SNew(SBorder)
							.BorderBackgroundColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f))
								[
								  SNew(STextBlock)
								  .Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 10))
								  .ColorAndOpacity(FLinearColor::White)
								  .Text(FText::FromString("Generator"))
								]
					]
					.BodyContent()
					[
						SNew(SVerticalBox)
							+ SVerticalBox::Slot()
							.Padding(5.0f)
							
								[
									SNew(STextBlock)
									.Text(FText::FromString("New Area"))
									/*SNew(SComboButton)
									.OnGetMenuContent(this, &UCoreGenerator::HandleMenuContent)
									.ContentPadding(FMargin(2.0f, 2.0f))
									.ButtonContent()
									[
										SNew(STextBlock)
										.Text(LOCTEXT("CustomDataAsset", "Choose Custom Data Asset"))
									]*/
								]
							
					]
			];
}

FString UCoreGenerator::GetDataAssetPath() const
{
	return SelectedDataAssetPath;
}

TSharedRef<SWidget> UCoreGenerator::HandleMenuContent()
{
	ScanDataAssets();
	// Create a list view widget to display the available custom data assets
	TSharedPtr<SListView<UObject*>> ListView;
	SAssignNew(ListView, SListView<UObject*>)
		.ListItemsSource(&CustomDataAssetList)
		.OnGenerateRow(this, &UCoreGenerator::HandleCustomDataAssetListRow);

	// Create a scroll box widget to contain the list view
	TSharedPtr<SScrollBox> ScrollBox;
	SAssignNew(ScrollBox, SScrollBox)
		.Orientation(Orient_Vertical)
		.ScrollBarAlwaysVisible(true)
		+ SScrollBox::Slot()
		[
			ListView.ToSharedRef()
		];

	// Create a border widget to contain the scroll box
	TSharedPtr<SBorder> Border;
	SAssignNew(Border, SBorder)
		.Padding(FMargin(5.0f))
		.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
		[
			ScrollBox.ToSharedRef()
		];

	// Return the border widget as the menu content of the combo button
	return Border.ToSharedRef();
}

TSharedRef<ITableRow> UCoreGenerator::HandleCustomDataAssetListRow(UObject* Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(STableRow<UObject*>, OwnerTable)
		.Padding(FMargin(3.0f))
		[
			SNew(STextBlock)
			.Text(FText::FromName(Item->GetFName()))
		];
}

void UCoreGenerator::ScanDataAssets()
{

	// Get a reference to the asset registry module
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	// Create a filter that includes only custom data assets
	FARFilter Filter;
	Filter.ClassNames.Add(UDataAsset::StaticClass()->GetFName());

	// Search for all the custom data assets in the project directory
	TArray<FAssetData> AssetData;
	AssetRegistryModule.Get().GetAssets(Filter, AssetData);

	// Add the custom data assets to the CustomDataAssetList array
	for (const FAssetData& Asset : AssetData)
	{
		UObject* Object = Asset.GetAsset();
		if (Object != nullptr)
		{
			CustomDataAssetList.Add(Object);
		}
	}
}

#undef  LOCTEXT