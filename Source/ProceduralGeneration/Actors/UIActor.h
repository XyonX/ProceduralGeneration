// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreUI/UI/TopDownIngameScreen.h"
#include "GameFramework/Actor.h"
#include "UIActor.generated.h"

UCLASS()
class PROCEDURALGENERATION_API AUIActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AUIActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="UI")
	float Height;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="UI")
	float Width;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="UI")
	UTexture2D* BGImage;

	UFUNCTION(BlueprintCallable)
	UTopDownIngameScreen*GetIngameWidget () { return IngameScreen;}



	//public functions

	void SpawnUI_UMG_1 ();
	void SpawnUI_Slate_1 ();
	TSharedPtr<UGameViewportClient ,ESPMode::ThreadSafe>GViewport;


	TSharedPtr<SBottomBuildingsPanel>BottomPanelWidget ;
	
private:

	
	UTopDownIngameScreen*IngameScreen ;
};
