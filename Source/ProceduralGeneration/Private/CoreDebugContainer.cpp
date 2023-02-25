// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreDebugContainer.h"

// Sets default values
ACoreDebugContainer::ACoreDebugContainer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACoreDebugContainer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoreDebugContainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
/*
void TDebugger::log()
{
	if (GEngine)
	{
		FString Message = FString::Printf(TEXT("Function called: %s"), TEXT(__FUNCTION__));
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, Message);
	}

}*/

