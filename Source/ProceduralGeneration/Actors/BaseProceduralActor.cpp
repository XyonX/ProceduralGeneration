// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseProceduralActor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Containers/Array.h"
#include "ProceduralGeneration/Tiles/Tile.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CoreUI/DockTab/GenerationControllerTab.h"
#include "Engine/LocalPlayer.h"
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
	Map_Height=4;
	Map_Width=4;
	
}

void ABaseProceduralActor::BeginPlay()
{
	
	Super::BeginPlay();
	
	SetupInput();
	
	TopDownGameInstance=Cast<UTopDownGameInstance>(GetGameInstance());
	if(TopDownGameInstance)
	{
		TotalSpawnables=&TopDownGameInstance->ProceduralSpawnables;
	}
	else
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Top Down Game Instance not found !!!  "));
		}
		return;
	}

	DefaultGenerator = UCoreGenerator::StaticClass();
	DefaultSpawner=UCoreSpawner::StaticClass();
	

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

	for (int32 i = TotalTiles->Num() - 1; i >= 0; i--)
	{
		UTile* Tile = (*TotalTiles)[i];
		Tile->ConditionalBeginDestroy();
		TotalTiles->RemoveAt(i);
	}
	TotalTiles->Empty();

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

	// Get the enhanced input subsystem for the local player
	ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	if (!LocalPlayer)
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Local player Not found "));}
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputModule = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if(!EnhancedInputModule)
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Enhancce input subsystem not fofund "));}
		return;
	}
	
	if(!ProceduralGenerationMapping )
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Maping  context  not fofund "));}
		return;
	}
	EnhancedInputModule->AddMappingContext(ProceduralGenerationMapping,-1);
	
	// Create an input component and attach it to the player controller
	UEnhancedInputComponent* EnhancedInputComp =  Cast<UEnhancedInputComponent>(PlayerController->InputComponent) ;
	if (!EnhancedInputComp )
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" EnhancedInputComp  ccast failded "));}
		return;
	}
	
	if(OpenUIAction)
	{
		EnhancedInputComp->BindAction(	OpenUIAction,ETriggerEvent::Triggered,this,&ABaseProceduralActor::ToggleTab);
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" BindAcction done "));}
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
			//Generator->AddUIEntry();
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
	Generator = NewObject<UCoreGenerator>(this, DefaultGenerator);
	if(Generator != nullptr)
	{
		Generator->Init(TotalSpawnables,FloorMesh,Map_Height,Map_Width);
    	TotalTiles =  Generator->Run();
	}

	if(TotalTiles==nullptr || TotalTiles->IsEmpty())
	{
		return false;
	}
	return true;

}

bool ABaseProceduralActor::RunSpawner()
{
	Spawner = NewObject<UCoreSpawner>(this,DefaultSpawner);
	if(Spawner !=nullptr)
	{
		Spawner->Init(TotalTiles,TotalSpawnables,Map_Height,Map_Width);
    	return  Spawner->Run();
	}
	return false;

}










