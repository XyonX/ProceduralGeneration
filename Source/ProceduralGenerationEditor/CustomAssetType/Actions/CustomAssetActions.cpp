// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomAssetActions.h"


FText FMyCustomAssetActions::GetName() const
{
	return FText::FromString("MyCustomAsset");
}
/*
void FMyCustomAssetActions::GetActions(const TArray<UObject*>& InObjects, FToolMenuSection& Section)
{
	FAssetTypeActions_Base::GetActions(InObjects, Section);

	FAssetTypeActions_Base::GetActions(InObjects, Section);

	auto TextAssets = GetTypedWeakObjectPtrs<ATestAsset>(InObjects);

	Section.AddMenuEntry(
		"ReverseText",
		LOCTEXT("TextAsset_ReverseText", "Reverse Text"),
		LOCTEXT("TextAsset_ReverseTextToolTip", "Reverse the text stored in the selected text asset(s)."),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateLambda([=]{
				for (auto& TextAsset : TextAssets)
				{
					if (TextAsset.IsValid() && !TextAsset->Text.IsEmpty())
					{
						TextAsset->Text = FText::FromString(TextAsset->Text.ToString().Reverse());
						TextAsset->PostEditChange();
						TextAsset->MarkPackageDirty();
					}
				}
			}),
			FCanExecuteAction::CreateLambda([=] {
				for (auto& TextAsset : TextAssets)
				{
					if (TextAsset.IsValid() && !TextAsset->Text.IsEmpty())
					{
						return true;
					}
				}
				return false;
			})
		)
	);
}*/
