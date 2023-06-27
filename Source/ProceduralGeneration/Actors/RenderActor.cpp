// Fill out your copyright notice in the Description page of Project Settings.


#include "RenderActor.h"

#include "ImageUtils.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Engine/Texture2D.h"
#include "Engine/TextureMipDataProviderFactory.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "Modules/ModuleManager.h"



// Sets default values
ARenderActor::ARenderActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and attach the scene capture component
	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent"));
	RootComponent = SceneCaptureComponent;
	
	// Create and attach the static mesh component
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneCaptureComponent);

	// Create the render target
	RenderTarget = CreateDefaultSubobject<UTextureRenderTarget2D>(TEXT("RenderTarget"));
	RenderTarget->InitAutoFormat(256, 256); // Set the dimensions of the render target as desired
}

// Called when the game starts or when spawned
void ARenderActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARenderActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARenderActor::CaptureRenderedTexture()
{
	// Set the render target on the scene capture component
	SceneCaptureComponent->TextureTarget = RenderTarget;

	// Disable capturing the skybox and background
	SceneCaptureComponent->CaptureSource = ESceneCaptureSource::SCS_SceneColorHDR;

	// Capture the scene by rendering
	SceneCaptureComponent->CaptureScene();

	// Save the render target as a PNG file
	FString SavePath = FPaths::ProjectContentDir() + "Textures/RenderedTexture.png";
	FArchive* Ar = IFileManager::Get().CreateFileWriter(*SavePath);
	if (Ar)
	{
		FImageUtils::ExportRenderTarget2DAsPNG(RenderTarget, *Ar);
		Ar->Close();
		delete Ar;
	}
}

