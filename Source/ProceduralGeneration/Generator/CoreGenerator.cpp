// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreGenerator.h"

#include "EditorStyleSet.h"
#include "Widgets/Layout/SExpandableArea.h"
#include "PropertyCustomizationHelpers.h"

UCoreGenerator::UCoreGenerator()
{
	
}

TArray<UTile*> UCoreGenerator::Run()
{
}

void UCoreGenerator::AddUIEntry()
{
	if(ControllerTab ==nullptr)
	{
		return;
	}

	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.bAllowSearch = true;
	DetailsViewArgs.bHideSelectionTip = false;
	DetailsViewArgs.bLockable = true;
	DetailsViewArgs.bSearchInitialKeyFocus = true;
	DetailsViewArgs.bUpdatesFromSelection = true;
	//DetailsViewArgs.NotifyHook = this;
	//DetailsViewArgs.SelectionMode = ESelectionMode::Multi;
	//DetailsViewArgs.ViewIdentifier = ViewIdentifier;


	//TSharedPtr<IDetailsView> DetailsView = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor").CreateDetailView(DetailsViewArgs);
	//DetailsView->SetObject(MyObject);

	
	

	// Get the vertical box widget
	TSharedPtr<SVerticalBox> VerticalBoxWidget = StaticCastSharedRef<SVerticalBox>(ControllerTab->GetWidget().ToSharedRef());

	// Add a new slot to the vertical box and create a collapsible box widget inside the slot
	VerticalBoxWidget->AddSlot()
					.AutoHeight()
	
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
								  .Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 16))
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
								SNew(SObjectPropertyEntryBox)
								.PropertyHandle(PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(UDataAsset, GeneratorDataAsset)))
								.AllowClear(true)
								.DisplayUseSelected(true)
								.ObjectPath(this, &UYourWidgetClass::OnGetDataAssetPath)
								.OnObjectChanged(this, &UYourWidgetClass::OnGeneratorDataAssetChanged)
								.ThumbnailPool(ThumbnailPool)
								.ThumbnailScale(0.125f)
								.Metadata()
								[
									SNew(SHorizontalBox)
									+ SHorizontalBox::Slot()
									.AutoWidth()
									[
										SNew(SImage)
										.Image(FEditorStyle::GetBrush("ClassIcon"))
									]
									+ SHorizontalBox::Slot()
									.FillWidth(1.0f)
									[
										SNew(STextBlock)
										.Text(FText::FromString("Select Generator Data Asset"))
										.Font(FEditorStyle::GetFontStyle(TEXT("ContentBrowser.SourceTreeTitleFont")))
									]
								]
							]
					]
			];




	
}
