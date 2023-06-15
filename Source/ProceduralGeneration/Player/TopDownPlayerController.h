// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include"GameFramework/PlayerController.h"
#include "ProceduralGeneration/Pawn/TopDownPawn.h"
#include "TopDownPlayerController.generated.h"


UCLASS()
class PROCEDURALGENERATION_API ATopDownPlayerController  : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;

	ATopDownPlayerController ();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Controller")
	FVector CursorWorldPosition ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Controller")
	FVector CursorWorldDirection;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Controller")
	bool bCanPan ;

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Controller")
	UStaticMesh*CubeMesh ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Test")
	TSubclassOf<AActor>TesTActor;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Controller")
	ATopDownPawn*TopDownPawn;

	ATopDownPawn* GetTopDownPawn ();
	void OnMouseMoveX (const FInputActionValue& Value);
	void OnMouseMoveY (const FInputActionValue& Value);
	void OnMouseLMB (const FInputActionValue& Value);
	void OnMouseRMBHold (const FInputActionValue& Value);
	void OnMouseRMBReleased (const FInputActionValue& Value);
	void PanHorizontal (float Axis);
	void PanVertical (float Axis);
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Controller")
	float HorizontalPanAcc ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Controller")
	float VerticalPanAcc ;

	

	UFUNCTION(BlueprintCallable)
	void OnMouseMove(const FVector2D& MousePosition);
	UFUNCTION(BlueprintCallable)
	void SpawnActorAtCursor ();

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input Actions")
	class UInputAction* MouseX ;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input Actions")
	class UInputAction* MouseY ;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input Actions")
	class UInputAction* MouseLMB ;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input Actions")
	class UInputAction* MouseRMB ;
	
};
