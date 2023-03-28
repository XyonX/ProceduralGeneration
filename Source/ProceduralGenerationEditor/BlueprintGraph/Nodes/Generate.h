// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Generate.Generated.h"

UCLASS()
class UGenerate : public UEdGraphNode
{
	GENERATED_BODY()

public:
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void AllocateDefaultPins() override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual void NodeConnectionListChanged() override;

	UFUNCTION(BlueprintCallable, Category = "Custom Node")
	void MyCustomFunction();
};