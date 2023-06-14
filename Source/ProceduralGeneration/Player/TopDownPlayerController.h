// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include"GameFramework/PlayerController.h"
#include "TopDownPlayerController.generated.h"


UCLASS()
class PROCEDURALGENERATION_API ATopDownPlayerController  : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;


	void OnMouseMoveX (const FInputActionValue& Value);
	void OnMouseMoveY (const FInputActionValue& Value);

	void OnMouseMove(const FVector2D& MousePosition);

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input Actions")
	class UInputAction* MouseX ;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input Actions")
	class UInputAction* MouseY ;
	
};
