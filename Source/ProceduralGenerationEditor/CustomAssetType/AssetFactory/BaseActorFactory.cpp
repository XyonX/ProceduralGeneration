// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActorFactory.h"
#include "ProceduralGeneration/Actors/CustomAssetClass/BaseActor.h"

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
