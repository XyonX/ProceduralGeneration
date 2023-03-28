// Fill out your copyright notice in the Description page of Project Settings.


#include "Generate.h"

FText UGenerate::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(TEXT("My Custom Node"));
}

void UGenerate::AllocateDefaultPins()
{
	// Create an input pin for the node
	UEdGraphPin* ExecPin = CreatePin(EGPD_Input, TEXT("ExecPin"), TEXT("ABADABA"), nullptr, false, false, TEXT("Exec"));
}

FLinearColor UGenerate::GetNodeTitleColor() const
{
	return FLinearColor(0, 0, 1);
}

void UGenerate::NodeConnectionListChanged()
{
	Super::NodeConnectionListChanged();

	// Update the input pin on the node
	UEdGraphPin* ExecPin = FindPin(TEXT("ExecPin"));
	/*
	if (ExecPin != nullptr)
	{
		ExecPin->bHidden = !ExecPin->LinkedTo.Num() > 0;
	}*/
}

void UGenerate::MyCustomFunction()
{
}
