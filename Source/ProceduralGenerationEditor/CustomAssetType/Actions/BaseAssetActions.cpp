// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAssetActions.h"

#include "EditorStyleSet.h"
#include "Brushes/SlateImageBrush.h"
#include "ProceduralGenerationEditor/ToolKit/BaseEditorToolkit.h"
#include "Styling/SlateStyleRegistry.h"
//#include "AssetThumbnail.h"


#define LOCTEXT_NAMESPACE "BaseActorActions"
FTestDelegate FBaseActorActions::TestDelegate;


FBaseActorActions::FBaseActorActions()
{
	TestDelegate.BindRaw(this, &FBaseActorActions::AnotherFunction);
}

//}
void FBaseActorActions::GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder)
{

	FAssetTypeActions_Base::GetActions(InObjects, MenuBuilder);

	auto TextAssets = GetTypedWeakObjectPtrs<UBaseActor>(InObjects);
	
	MenuBuilder.AddMenuEntry(
		FText::FromString("My Entry"),
		FText::FromString("My Tooltip"),
				FSlateIcon(),
				FUIAction(
			FExecuteAction::CreateStatic(&FBaseActorActions::TestFunction),
			EUIActionRepeatMode::RepeatDisabled
		));
		

}

void FBaseActorActions::OpenAssetEditor(const TArray<UObject*>& InObjects,
	TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{

	if(!CustomEditorToolkit.IsValid())
	{
		// Create a new instance of our custom editor toolkit class
		CustomEditorToolkit = MakeShareable(new FBaseEditorToolkit());
		CustomEditorToolkit->Init(EToolkitMode::Standalone,EditWithinLevelEditor,InObjects);
	}
	//CustomEditorToolkit->OpenEditor(InObjects,EditWithinLevelEditor);

}

TSharedPtr<SWidget> FBaseActorActions::GetThumbnailOverlay(const FAssetData& AssetData) const
{
	TSharedPtr<SImage> ThumbnailImage;
	UObject* Asset = AssetData.GetAsset();


/*	// Load the custom image brush
	const FName BrushName = FName(TEXT("/ProceduralGeneration/EditorData_UAsset/SB_BAThumb.SB_BAThumb"));
	const FVector2D IconSize(64.f, 64.f);
	const FSlateBrush* Brush = FAppStyle::GetBrush(BrushName);
	if (Brush == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load custom thumbnail brush."));
		return nullptr;
	}*/
	const FString ThumbnailPath = "/ProceduralGeneration/Source/ProceduralGenerationEditor/EditorContent/BaseActorThumbnail.jpg"; // Replace with your own image file path
	
	if (Asset)
	{
		ThumbnailImage = SNew(SImage)
			.ColorAndOpacity(FLinearColor::Green)
			.ToolTipText(FText::FromString("Thumbnail Tooltip"));
	}
	if (FPaths::FileExists(ThumbnailPath))
	{
		const FSlateBrush* ThumbnailBrush = FAppStyle::GetBrush("NoTexture");
		FSlateImageBrush* ImageBrush = new FSlateImageBrush(ThumbnailPath, FVector2D(64.0f, 64.0f));
		if (ImageBrush->GetResourceObject() == nullptr)
		{
			delete ImageBrush;
			ImageBrush = nullptr;
		}
		else
		{
			ThumbnailBrush = ImageBrush;
		}
		ThumbnailImage->SetImage(ImageBrush);
	}
    
	return SNew(SBox)
		.WidthOverride(64.0f)
		.HeightOverride(64.0f)
		[
			ThumbnailImage.ToSharedRef()
		];
}

void FBaseActorActions::TestFunction()
{
	TestDelegate.Execute();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Blue,FString("Context MenU Function Called "),false);
	}
	
}

bool FBaseActorActions::AnotherFunction()
{
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Blue,FString("CAnother Function Called "),false);
	}
	return true;
}


#undef LOCTEXT_NAMESPACE