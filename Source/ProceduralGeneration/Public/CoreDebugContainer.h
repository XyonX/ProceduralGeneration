// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Misc/CString.h"
#include "CoreDebugContainer.generated.h"
/*
template <typename T>
USTRUCT(BlueprintType)
struct FDebugVariable
{
	//GENERATED_BODY()
	
	FText VariableName ;
	FText VariableValue ;

	void SetVariableNameAndValue (T& Input) ;

	FDebugVariable(T& Input) : input(Input)
	{
		SetVariableNameAndValue(input);
	}
	T& input;
	
};

template <typename T>
void FDebugVariable<T>::SetVariableNameAndValue(T& Input)
{
	FString InputAsString = LexToString(Input);
	VariableName = FText::FromString(InputAsString);
	VariableValue = FText::FromString(InputAsString);
}*/

/*
template <typename T>
void FMyStruct<T>::SetVariableNameAndValue(T& Value)
{
	if constexpr (std::is_same_v<T, FString>)
	{
		FText ValueAsFText = FText::FromString(Value);
		UE_LOG(LogTemp, Log, TEXT("Value as FText: %s"), *ValueAsFText.ToString());
	}
	else if constexpr (std::is_same_v<T, FName>)
	{
		FText ValueAsFText = FText::FromName(Value);
		UE_LOG(LogTemp, Log, TEXT("Value as FText: %s"), *ValueAsFText.ToString());
	}
	else if (std::is_same_v<T,float >)
	{
		UE_LOG(LogTemp, Error, TEXT("Unsupported type"));
	}
	else if (std::is_same_v<T,int  >)
	{
		UE_LOG(LogTemp, Error, TEXT("Unsupported type"));
	}
}*/

USTRUCT(BlueprintType)
struct FVariableContainer
{
	GENERATED_BODY()
	// Variables you want to display in the UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug Container")
	TArray<int>IntVariableList ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug Container")
	TArray<float>FloatVariableList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug Container")
	TArray<bool>BoolVariableList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug Container")
	TArray<FVector>VectorVariableList;
};


UCLASS()
class PROCEDURALGENERATION_API ACoreDebugContainer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoreDebugContainer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category="DEBUG")
	FVariableContainer DebugVariableList ;

	

};
