// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RenderActor.generated.h"

UCLASS()
class PROCEDURALGENERATION_API ARenderActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARenderActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Components")
	USceneCaptureComponent2D* SceneCaptureComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Rendering")
	UTextureRenderTarget2D* RenderTarget;

	UFUNCTION(BlueprintCallable, Category = "Rendering")
	void CaptureRenderedTexture();

	
};
