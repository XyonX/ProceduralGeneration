﻿// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseProceduralActor.h"
#include "ProceduralGeneration/Game/TopDownGameInstance.h"
#include "ProceduralGeneration/Generator/CoreGenerator.h"
#include "ProceduralGeneration/Spawner/CoreSpawner.h"



#define LogSwitch 1
TSharedPtr<SWindow> ABaseProceduralActor::ControllerWindow;
FOnGenerateButtonClick ABaseProceduralActor::GenerateClickDelegate_Actor;



ABaseProceduralActor::ABaseProceduralActor()
{
	// TURNING OFF TICK
	PrimaryActorTick.bCanEverTick = false;
	
}

void ABaseProceduralActor::BeginPlay()
{
	
	Super::BeginPlay();
	SetupInput();
	
	TopDownGameInstance=Cast<UTopDownGameInstance>(GetGameInstance());
	

	if(RunGenerator() == false)
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Generator Failed !!!  "));
		}
		return;
	}
	if(RunSpawner() ==false)
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Spawner Failed !!!  "));
		}
		return;
	}
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Generation Successfull !!!  "));
	}

}

void ABaseProceduralActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (ControllerWindow.IsValid() && ControllerWindow->IsVisible())
	{
		// The window is already visible, so just hide it
		ControllerWindow->HideWindow();
		FSlateApplication::Get().DestroyWindowImmediately(ControllerWindow.ToSharedRef());
		ControllerWindow.Reset();
	}
	
}

void ABaseProceduralActor::SetupInput()
{
	
	// Get the player controller
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController)
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Controller Not found "));}
		return;
	}
	
}

void ABaseProceduralActor::ToggleTab()
{
	if (!IsInGameThread())
	{
		// The game is not running, return or handle the error
		return;
	}
	
	if (ControllerWindow.IsValid() && ControllerWindow->IsVisible())
	{
		// The window is already visible, so just hide it
		ControllerWindow->HideWindow();
		FSlateApplication::Get().DestroyWindowImmediately(ControllerWindow.ToSharedRef());
		ControllerWindow.Reset();
	}
	else
	{
		// Create a new window and keep a reference to it
		if (!ControllerWidget.IsValid())
		{
			ControllerWidget = SNew(SGenerationControllerTab);
			//SGenerationControllerTab::GenerateDelegate.BindUObject(this,&ABaseProceduralActor::OnReGenerate);
			SGenerationControllerTab::DebugDelegate.BindUObject(this,&ABaseProceduralActor::OnDelegate);
			Generator->SetControllerTab(ControllerWidget);
			Generator->AddUIEntry();
		}

		ControllerWindow = SNew(SWindow)
			.Title(FText::FromString("Controller"))
			.SizingRule(ESizingRule::UserSized)
			.AutoCenter(EAutoCenter::PreferredWorkArea)
			.ClientSize(FVector2D(300, 800))
			[
				SNew(SBorder)
					.Padding(10.0f)
					.BorderImage(FCoreStyle::Get().GetBrush("ToolPanel.GroupBorder"))
					.BorderBackgroundColor(FLinearColor(0.5f, 0.5f, 0.5f, 1.0f))
					[
						SNew(SBox)
						[
							SNew(STextBlock)
							.Text(FText::FromString("Hello World!"))
							.ColorAndOpacity(FLinearColor::White)
							.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 16))
						]
					]
			]
			.IsTopmostWindow(true)
			.CreateTitleBar(true)
			.SupportsMaximize(true)
			.SupportsMinimize(false)
			.HasCloseButton(true)
			.CreateTitleBar(true)
			.Content()
			[                ControllerWidget.ToSharedRef()            ];

		FSlateApplication::Get().AddWindow(ControllerWindow.ToSharedRef(), true);
	}
	
	
}

void ABaseProceduralActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	// Check if the dock tab has been created yet
	if (MyDockTab.IsValid())
	{
		// Update the dock tab's label with the actor's name
		FString ActorName = GetName();
		MyDockTab->SetLabel(FText::FromString(ActorName));
	}
}

bool ABaseProceduralActor::OnDelegate()
{
	if(Generator)
	{
		Generator->OnDebug();
		return true;
	}

	if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("  Debug Called   !!"));}
	return true;
	
}

bool ABaseProceduralActor::RunGenerator()
{
	// Create a new instance of UCoreGenerator class
	//Generator = NewObject<UCoreGenerator>(this, CustomGenerator);
	//Generator->Init(ControllerWidget,FloorMesh,Map_Height,CustomGenerator);
	//Generator->AddUIEntry();
	//return  Generator->Run(AllTilesPTR,TotalSpawnables);
	return false;
}

bool ABaseProceduralActor::RunSpawner()
{
	//Spawner = NewObject<UCoreSpawner>(this,DefaultSpawner);
	//Spawner->Init(&AllTilesPTR,TotalSpawnables,DefaultTile,DefaultSpawnable,Map_Height,Map_Width);

	//return  Spawner->Run();
	return false;
}










