#pragma once

#include "AssetTypeActions_Base.h"
#include "ProceduralGeneration/Actors/CustomAssetClass/BaseActor.h"
#include "ProceduralGeneration/CustomAssetType/ToolKit/BaseEditorToolkit.h"

DECLARE_DELEGATE_RetVal(bool, FTestDelegate)

class PROCEDURALGENERATION_API FBaseActorActions : public FAssetTypeActions_Base
{
	
public:
	FBaseActorActions();
	
	virtual FText GetName() const override {return FText::FromString("Procedural Actor"); };
	virtual uint32 GetCategories() override {return EAssetTypeCategories::Misc; };
	virtual UClass* GetSupportedClass() const override {return UBaseActor::StaticClass();};
	virtual bool HasActions(const TArray<UObject*>& InObjects) const override {return true;};
	virtual void GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder) override;
	// this function is for the old users who used to program the in the toolkit 
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor) override;
	virtual bool CanFilter() override{return  true;};
	virtual FColor GetTypeColor() const override{return FColor::Yellow;};
	virtual TSharedPtr<SWidget> GetThumbnailOverlay(const FAssetData& AssetData) const override;
	static FTestDelegate TestDelegate;
	static void TestFunction ();
	bool AnotherFunction ();


private :
	TSharedPtr<FBaseEditorToolkit>CustomEditorToolkit ;
	
};
