// Fill out your copyright notice in the Description page of Project Settings.


#include "UIActor.h"

#include "Actions/AsyncAction_CreateWidgetAsync.h"
#include "CoreUI/Slate/CompoundWidgets/SBottomBuildingsPanel.h"
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

	SpawnUI_UMG_1();
	
}

// Called every frame
void AUIActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUIActor::SpawnUI_UMG_1()
{
	IngameScreen = CreateWidget<UTopDownIngameScreen>(GetWorld(), UTopDownIngameScreen::StaticClass());
	IngameScreen->SetBackgroundImage(BGImage);
	IngameScreen->SetSize(Height,Width);
	IngameScreen->SynchronizeProperties();
	IngameScreen->AddToViewport();
}

void AUIActor::SpawnUI_Slate_1()
{
	///Slate widgets are added to the viewport by passing a reference (a TSharedref<SWidget>) to the widget to GameViewportClient::AddViewportWidgetContent()
/*	if(GEngine)
	{
		GEngine->GameViewport->AddViewportWidgetContent(
		SAssignNew(BottomPanelWidget,SBottomBuildingsPanel)
		.PossiblyNullContent(SBottomBuildingsPanel::StaticWidgetClass());
	}*/
	
}

