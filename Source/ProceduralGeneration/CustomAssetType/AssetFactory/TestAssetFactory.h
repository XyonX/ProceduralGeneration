#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "AssetTypeCategories.h"
#include "Factories/Factory.h"
#include "TestAssetFactory.generated.h"

UCLASS()
class UTestAssetFactory : public UFactory
{
	GENERATED_BODY()

public:
	UTestAssetFactory();

	// UFactory interface
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	// End of UFactory interface
};
