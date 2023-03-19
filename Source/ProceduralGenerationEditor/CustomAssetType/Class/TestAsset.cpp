// Fill out your copyright notice in the Description page of Project Settings.


#include "TestAsset.h"


// Sets default values
ATestAsset::ATestAsset()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATestAsset::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestAsset::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestAsset::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
	Ar<< TestInt;
	
}

void ATestAsset::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

