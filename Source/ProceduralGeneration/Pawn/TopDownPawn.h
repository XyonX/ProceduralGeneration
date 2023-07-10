// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
//#include "ProceduralGeneration/Actors/BaseGridActor.h"
#include "TopDownPawn.generated.h"

class ABaseGridActor;
UCLASS()
class PROCEDURALGENERATION_API ATopDownPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATopDownPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TopDownPawn")
	UCameraComponent* TopDownCamera;
	FORCEINLINE UCameraComponent* GetCameraComponent ();

	ABaseGridActor* GetGridActor ();
	void SetSpawnLocation () ;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Pawn")
	FVector Offset_Vector;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Pawn")
	float Offset_Scaler;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Pawn")
	bool bAdjustCameraLocation;

	UPROPERTY()
	ABaseGridActor*GridActor;

	
};
