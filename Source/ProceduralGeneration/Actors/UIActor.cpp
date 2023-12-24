/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/


#include "UIActor.h"

#include "Actions/AsyncAction_CreateWidgetAsync.h"
#include "CoreUI/Slate/Cards/SBuildingCard.h"
#include "CoreUI/UI/LoadingScreenUI.h"
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

	TDGameInstance=Cast<UTopDownGameInstance>(GetGameInstance());
	if(TDGameInstance)
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange, TEXT(" USing TDGameInstance "));}
	}

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
	IngameScreen->SetSize(Height,Width);
	if(TDGameInstance)
	{
		IngameScreen->SetSpawnable(&TDGameInstance->SpawnableItems);
	}
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

