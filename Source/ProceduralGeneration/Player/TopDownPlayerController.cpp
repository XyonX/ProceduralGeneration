// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownPlayerController.h"

#include "EnhancedInputComponent.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "ProceduralGeneration/Actors/BaseGridActor.h"




class ABaseGridActor;

ATopDownPlayerController::ATopDownPlayerController()
{
	bCanPan =false;
	HorizontalPanAcc=100;
	VerticalPanAcc=100;
}

void ATopDownPlayerController::BeginPlay()
{

	Super::BeginPlay();
	GetTopDownPawn();
}


ATopDownPawn* ATopDownPlayerController::GetTopDownPawn()
{
	TopDownPawn = Cast<ATopDownPawn>(GetPawn());
	if(TopDownPawn)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Succesfully Possed TOPDOWN Pawn ");
		return TopDownPawn;
	}
	return nullptr;
	
}

void ATopDownPlayerController::OnMouseMoveX(const FInputActionValue& Value)
{
	FVector2D MousePosition;
	GetMousePosition(MousePosition.X, MousePosition.Y);
	OnMouseMove(MousePosition);
	if(bCanPan)
	{
		PanHorizontal(-1*Value[0]);
		
	}
}

void ATopDownPlayerController::OnMouseMoveY(const FInputActionValue& Value)
{
	FVector2D MousePosition;
	GetMousePosition(MousePosition.X, MousePosition.Y);
	OnMouseMove(MousePosition);
	if(bCanPan)
	{
		PanVertical(-1*Value[0]);
	}
}

void ATopDownPlayerController::OnMouseLMB(const FInputActionValue& Value)
{

	FActorSpawnParameters SpawnParams ;
	SpawnParams.SpawnCollisionHandlingOverride =ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (TesTActor)
	{
		GetWorld()->SpawnActor<AActor>(TesTActor,CursorWorldPosition + (CursorWorldDirection * 500), CursorWorldDirection.Rotation(), SpawnParams);
	}
	
}

void ATopDownPlayerController::OnMouseRMBHold(const FInputActionValue& Value)
{
	if(TopDownPawn)
	{
		bCanPan =true;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Can Pan : True ");
	}
	
}

void ATopDownPlayerController::OnMouseRMBReleased(const FInputActionValue& Value)
{
	bCanPan =false;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Can Pan : False");
}

void ATopDownPlayerController::PanHorizontal(float Axis)
{
	float ClampAxis = FMath::Clamp(Axis,-1.0f,1.0f);
	FVector RightVector = TopDownPawn->TopDownCamera->GetRightVector();
	FVector Offset = RightVector*HorizontalPanAcc*ClampAxis*GetWorld()->GetDeltaSeconds();
	TopDownPawn->AddActorWorldOffset(Offset);
}

void ATopDownPlayerController::PanVertical(float Axis)
{
	float ClampAxis = FMath::Clamp(Axis,-1.0f,1.0f);
	FVector UpVector = TopDownPawn->TopDownCamera->GetUpVector();
	FVector Offset = UpVector*HorizontalPanAcc*ClampAxis*GetWorld()->GetDeltaSeconds();
	TopDownPawn->AddActorWorldOffset(Offset);
}


void ATopDownPlayerController::OnMouseMove(const FVector2D& MousePosition)
{
	// Implement the logic for hovering over the grid and updating the mesh here
	// You can call the corresponding function in your grid actor or widget class
	//if (ABaseGridActor* GridActor = Cast<ABaseGridActor>(GetPawn()))
	//{
	//	GridActor->OnMouseMove(MousePosition);
	//}

	FVector WorldPosition;
	FVector WorldDirection;
	UGameplayStatics::DeprojectScreenToWorld(this, MousePosition, WorldPosition, WorldDirection);
	CursorWorldPosition=WorldPosition;
	CursorWorldDirection = WorldDirection;
	if (GEngine)
	{
		FString DebugMessage = FString::Printf(TEXT("Mouse World Location: %f, %f"), WorldPosition.X, WorldPosition.Y);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DebugMessage);
	}

	

}

void ATopDownPlayerController::SpawnActorAtCursor()
{
	/*
	UWorld* World = GetWorld();
	ABaseGridActor* MyActorReference;
	if (World)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(World, ABaseGridActor::StaticClass(), FoundActors);

		if (FoundActors.Num() > 0)
		{
			// Assuming you only have one instance of the actor, you can assign it to the variable.
			MyActorReference = Cast<ABaseGridActor>(FoundActors[0]);

			if (MyActorReference)
			{
				FVector SpawnLoc = MyActorReference->CursorWorldPosition;
				FVector SpawnLoc = MyActorReference->CursorWorldPosition;
			}
				
		}
	}*/
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
		if(MouseLMB)
		{
			EnhancedInputComp->BindAction(MouseLMB,ETriggerEvent::Triggered,this,&ATopDownPlayerController::OnMouseLMB);
		}
		if(MouseRMB)
		{
			EnhancedInputComp->BindAction(MouseRMB,ETriggerEvent::Triggered,this,&ATopDownPlayerController::OnMouseRMBHold);
			EnhancedInputComp->BindAction(MouseRMB,ETriggerEvent::Completed,this,&ATopDownPlayerController::OnMouseRMBReleased);
			
		}
	}
	
}



