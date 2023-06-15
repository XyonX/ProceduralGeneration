// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownPawn.h"


// Sets default values
ATopDownPawn::ATopDownPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	TopDownCamera=CreateDefaultSubobject<UCameraComponent>("TopDownCamera");
	SetRootComponent(TopDownCamera);
}

// Called when the game starts or when spawned
void ATopDownPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATopDownPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATopDownPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UCameraComponent* ATopDownPawn::GetCameraComponent()
{
	return TopDownCamera;
}

