#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Factories/Factory.h"
#include "BaseActorFactory.generated.h"

UCLASS()
class PROCEDURALGENERATION_API UBaseActorFactory : public UFactory
{
	GENERATED_BODY()

public:
	UBaseActorFactory();

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

	
};