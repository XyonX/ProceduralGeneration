#include "TestAssetFactory.h"
#include "ProceduralGenerationEditor/CustomAssetType/Class/TestAsset.h"

UTestAssetFactory::UTestAssetFactory()
{
	SupportedClass = ATestAsset::StaticClass();
	bCreateNew = true;
	bEditorImport = false;
	bEditAfterNew = true;
	Formats.Add(TEXT("mycustomformat;My Custom Format"));
}

UObject* UTestAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	ATestAsset* NewAsset = NewObject<ATestAsset>(InParent, Class, Name, Flags | RF_Transactional);

	// Perform any additional setup for the new asset here, if necessary

	return NewAsset;
}
