// Fill out your copyright notice in the Description page of Project Settings.


#include "UIActor.h"

#include "Actions/AsyncAction_CreateWidgetAsync.h"
#include "CoreUI/UI/TopDownIngameScreen.h"


// Sets default values
AUIActor::AUIActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AUIActor::BeginPlay()
{
	Super::BeginPlay();
	// Spawn the UTopDownIngameScreen widget
	 IngameScreen = CreateWidget<UTopDownIngameScreen>(GetWorld(), UTopDownIngameScreen::StaticClass());
	IngameScreen->SizeBoxSize=Size;
	IngameScreen->BGImage=BGImage;
	IngameScreen->AddToViewport();
	
}

// Called every frame
void AUIActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

