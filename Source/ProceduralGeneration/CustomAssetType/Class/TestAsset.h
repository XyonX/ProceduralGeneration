// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestAsset.generated.h"

UCLASS()
class PROCEDURALGENERATION_API ATestAsset : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATestAsset();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Serialize(FArchive& Ar) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(SaveGame,EditAnywhere,BlueprintReadWrite,Category="Asset")
	int  TestInt  ;
	UPROPERTY(SaveGame,EditAnywhere,BlueprintReadWrite,Category="Asset")
	int TestFloat;
	UPROPERTY(SaveGame,EditAnywhere,BlueprintReadWrite,Category="Asset")
	TArray<int>TestIntArray;
};
