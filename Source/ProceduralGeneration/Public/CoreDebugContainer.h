// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoreDebugContainer.generated.h"

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
