#pragma once

#include "AssetTypeActions_Base.h"
#include "ProceduralGeneration/Actors/CustomAssetClass/BaseActor.h"


class FBaseActorActions : public FAssetTypeActions_Base
{
	
public:
	
	virtual FText GetName() const override {return FText::FromString("Procedural Actor"); };
	virtual uint32 GetCategories() override {return EAssetTypeCategories::Misc; };
	virtual UClass* GetSupportedClass() const override {return UBaseActor::StaticClass();};
	virtual bool HasActions(const TArray<UObject*>& InObjects) const override {return false;};
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor) override{};
	virtual bool CanFilter() override{return  true;};
	virtual FColor GetTypeColor() const override{return FColor::Yellow;};
	
};
