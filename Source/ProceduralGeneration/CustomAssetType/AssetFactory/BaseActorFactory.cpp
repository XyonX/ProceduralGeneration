/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/


#include "BaseActorFactory.h"
#include "ProceduralGeneration/CustomAssetClass/BaseActor.h"

UBaseActorFactory::UBaseActorFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UBaseActor::StaticClass();
}

UObject* UBaseActorFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
                                             UObject* Context, FFeedbackContext* Warn)
{
	UBaseActor* NewAsset = NewObject<UBaseActor>(InParent, InClass, InName, Flags);
	return NewAsset;
}
