// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownPlayerController.h"

#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "ProceduralGeneration/Actors/BaseGridActor.h"


class ABaseGridActor;

void ATopDownPlayerController::OnMouseMoveX(const FInputActionValue& Value)
{
	FVector2D MousePosition;
	GetMousePosition(MousePosition.X, MousePosition.Y);
	OnMouseMove(MousePosition);
}

void ATopDownPlayerController::OnMouseMoveY(const FInputActionValue& Value)
{
	FVector2D MousePosition;
	GetMousePosition(MousePosition.X, MousePosition.Y);
	OnMouseMove(MousePosition);
}

void ATopDownPlayerController::OnMouseMove(const FVector2D& MousePosition)
{
	// Implement the logic for hovering over the grid and updating the mesh here
	// You can call the corresponding function in your grid actor or widget class
	if (ABaseGridActor* GridActor = Cast<ABaseGridActor>(GetPawn()))
	{
		GridActor->OnMouseMove(MousePosition);
	}

}





void ATopDownPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComp =Cast <UEnhancedInputComponent>(InputComponent);

	if(EnhancedInputComp)
	{

		if(MouseX)
		{
			EnhancedInputComp->BindAction(MouseX,ETriggerEvent::Triggered,this,&ATopDownPlayerController::OnMouseMoveX);
		}
		if(MouseY)
		{
			EnhancedInputComp->BindAction(MouseY,ETriggerEvent::Triggered,this,&ATopDownPlayerController::OnMouseMoveY);
		}
	}
	
}


