#include "AssetTypeActions_Base.h"
#include  "ProceduralGeneration/CustomAssetType/Class/TestAsset.h"
class FMyCustomAssetActions : public FAssetTypeActions_Base
{
public:
	virtual FText GetName() const override { return FText::FromString("MyCustomAsset"); }
	virtual FColor GetTypeColor() const override { return FColor::Blue; }
	virtual UClass* GetSupportedClass() const override { return ATestAsset::StaticClass(); }
	virtual bool HasActions(const TArray<UObject*>& InObjects) const override { return true; }
	virtual void GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder) override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor) override {}
	virtual bool CanFilter() override { return true; }
	virtual uint32 GetCategories() override { return EAssetTypeCategories::Misc; }
};
