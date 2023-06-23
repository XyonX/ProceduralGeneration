﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownPlayerController.h"

#include "EnhancedInputComponent.h"
#include "Actions/AsyncAction_CreateWidgetAsync.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "ProceduralGeneration/Helpers/DelegateHelper.h"
#include "ProceduralGeneration/Tiles/TileData.h"


//FOnMouseMovementDelegate ATopDownPlayerController::OnMouseMovementDelegate;

class ABaseGridActor;

ATopDownPlayerController::ATopDownPlayerController()
{
	bCanPan =false;
	HorizontalPanAcc=100;
	VerticalPanAcc=100;
	CursorRange=100000;
	//bShowCursor = true;
	SpawnOffset_Cursor = 200.0f;
	SpawnOffset_Tile=200.0f;
}

void ATopDownPlayerController::BeginPlay()
{

	Super::BeginPlay();
	OnMouseMovementDelegate.AddDynamic(this,&ATopDownPlayerController::CursorMovementReceiver);
	GetTopDownPawn();
	// Set input mode to Game and UI
	FInputModeGameAndUI InputMode;
	//InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	//InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	InputMode.SetWidgetToFocus(nullptr);
	SetInputMode(InputMode);

	// Show and enable the mouse cursor
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	OnMouseMovementDelegate.Broadcast(FVector::ZeroVector);

	/*if (bShowCursor)
	{
		// Show the cursor
		bShowMouseCursor = true;
		bEnableClickEvents = true;
		bEnableMouseOverEvents = true;

		// Set the input mode to Game and UI
		SetInputMode(FInputModeGameAndUI());

		// Create your custom cursor widget
		// UUserWidget* CursorWidget = CreateWidget<UUserWidget>(this, YourCursorWidgetClass);

		// Set the cursor type to default and use the default cursor widget
		SetMouseCursorWidget(EMouseCursor::Hand, nullptr);
	}
	else
	{
		// Hide the cursor
		bShowMouseCursor = false;
		bEnableClickEvents = false;
		bEnableMouseOverEvents = false;

		// Set the input mode back to game mode
		SetInputMode(FInputModeGameOnly());

		// Release the mouse capture
		SetMouseCursorWidget(EMouseCursor::None, nullptr);
	}*/

}

void ATopDownPlayerController::Tick(float DeltaSeconds)
{

	Super::Tick(DeltaSeconds);
	
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
	//OnMouseMovementDelegate.Execute();
	FVector2D MousePosition;
	GetMousePosition(MousePosition.X, MousePosition.Y);
	OnMouseMove(MousePosition);
	if(bCanPan)
	{
		PanHorizontal(-1*Value[0]);
	}
	//MouseTrace();

	
	FString DebugMessage = FString::Printf(TEXT("Velocity X : %f"),Value[0]);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DebugMessage);
	// Check if mouse movement velocity is below a threshold value (e.g., 1.0)
	/*if (FMath::IsNearlyZero(Value[0], 0.1f))
	{
		MouseTrace();
	}*/
		
	
}

void ATopDownPlayerController::OnMouseMoveXAxis(float Value)
{
	FVector2D MousePosition;
	GetMousePosition(MousePosition.X, MousePosition.Y);
	OnMouseMove(MousePosition);
	if(bCanPan)
	{
		PanHorizontal(-1*Value);
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
		// Check if mouse movement velocity is below a threshold value (e.g., 1.0)
		
	}
	//MouseTrace();

	
	/*(
	if (FMath::IsNearlyZero(Value[0], 1.0f))
	{
		MouseTrace();
	}*/
	
}

void ATopDownPlayerController::OnMouseMoveYAxis(float Value)
{
	FVector2D MousePosition;
	GetMousePosition(MousePosition.X, MousePosition.Y);
	OnMouseMove(MousePosition);
	if(bCanPan)
	{
		PanVertical(-1*Value);
		
	}
}

void ATopDownPlayerController::OnMouseLMBHold(const FInputActionValue& Value)
{
	/*FActorSpawnParameters SpawnParams ;
SpawnParams.SpawnCollisionHandlingOverride =ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


if (TesTActor)
{
	GetWorld()->SpawnActor<AActor>(TesTActor,CursorWorldPosition + (CursorWorldDirection * 500), CursorWorldDirection.Rotation(), SpawnParams);
}*/


	//FVector Loc = CursorWorldPosition+(CursorWorldDirection*10)
	DrawDebugString(GetWorld(), CursorWorldPosition, *FString::Printf(TEXT("Position: %f,%f"),CursorWorldPosition.X, CursorWorldPosition.Y), nullptr, FColor::Red, -1.0f, false);
	//DrawDebugSphere(GetWorld(), CursorWorldPosition, 50, 16, FColor::Blue, false, 20.0f);
	/*float Length = 50.0f; // The length of the cone
	float AngleWidth = FMath::DegreesToRadians(20.0f); // The width angle of the cone in radians
	float AngleHeight = FMath::DegreesToRadians(20.0f); // The height angle of the cone in radians
	int32 NumSides = 16; // The number of sides of the cone
	FColor Color = FColor::Red; // The color of the cone
	bool bPersistentLines = true; // Whether the cone should persist or not
	float LifeTime = -1.0f; // The lifetime of the cone in seconds (-1 means infinite)
	uint8 DepthPriority = 0; // The depth priority of the cone
	float Thickness = 1.0f; // The thickness of the cone lines

	// Call the function to draw the cone
	DrawDebugCone(
	  GetWorld(),
	  CursorWorldPosition,
	  CursorWorldDirection,
	  Length,
	  AngleWidth,
	  AngleHeight,
	  NumSides,
	  Color,
	  bPersistentLines,
	  LifeTime,
	  DepthPriority,
	  Thickness
	);*/
	//MouseTrace();
	bShouldDrag=true;
}

void ATopDownPlayerController::OnMouseLMBReleased(const FInputActionValue& Value)
{
	bShouldDrag=false;
}

void ATopDownPlayerController::OnMouseRMBHold(const FInputActionValue& Value)
{
	if(TopDownPawn)
	{
		bCanPan =true;
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Can Pan : True ");
	}
	
}

void ATopDownPlayerController::OnMouseRMBReleased(const FInputActionValue& Value)
{
	bCanPan =false;
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Can Pan : False");
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

bool ATopDownPlayerController::BoxIntersectionTest(FVector Direction, TArray<FVector> Verts)
{
	FVector A =Verts[0];
	FVector B =Verts[1];
	FVector C =Verts[2];
	FVector D =Verts[3];
	
	FVector Normal = FVector::CrossProduct(B-A,C-B).GetSafeNormal();

	float DotProduct = FVector::DotProduct(Normal,Direction);

	if (FMath::IsNearlyZero(DotProduct))
	{
		// The cursor's forward vector is nearly perpendicular to the triangle's normal
		// Consider this case as the cursor not being on the specific triangle
		return false;
	}

	// Perform the ray-box intersection test

	// Calculate the box's center
	FVector BoxCenter = (A + B + C + D) / 4.0f;

	// Calculate the box's extents (half width, half height, half depth)
	FVector BoxExtents = (B - A) / 2.0f;
	
	// Calculate the minimum and maximum corners of the box
	FVector BoxMin = BoxCenter - BoxExtents;
	FVector BoxMax = BoxCenter + BoxExtents;

	FBox Box (BoxMin,BoxMax);

	// Calculate the line start and end points
	FVector LineStart = GetPawn()->GetActorLocation();
	FVector LineEnd = GetPawn()->GetActorLocation() + Direction * 1000.0f;

	// Calculate the intersection point between the ray and the box
	FVector IntersectionPoint;
	FVector HitN;
	float RTime ;
	bool bIntersects = FMath::LineExtentBoxIntersection(Box, LineStart, LineEnd, BoxExtents, IntersectionPoint,HitN,RTime);

	if (bIntersects)
	{
		// The ray intersects the box
		// You can perform additional checks or actions here
		// ...
		return true;
	}

	return false;
	
	
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
	/*if (GEngine)
	{
		FString DebugMessage = FString::Printf(TEXT("Mouse World Location: %f, %f"), WorldPosition.X, WorldPosition.Y);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DebugMessage);
	}*/

	 MouseTrace();
	OnMouseMovementDelegate.Broadcast(CursorWorldHitLocation);

	//FString DebugMessage = FString::Printf(TEXT("Velocity X : %f"),Value);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DebugMessage);

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

bool ATopDownPlayerController::MouseTrace()
{
	// Start and end points of the line trace
	FVector TraceStart = CursorWorldPosition; // Set the starting point of the trace
	FVector TraceEnd =CursorWorldPosition+(CursorWorldDirection*CursorRange); // Set the ending point of the trace
	
	FCollisionQueryParams TraceParams(FName(TEXT("LineTrace")), true, GetOwner());

	// Perform the line trace
	//if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, TraceParams))
	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, TraceParams))
	{
		bIsCursorPointing=true;
		// A hit has occurred
		// Process the hit result
		AActor* HitActor = HitResult.GetActor();
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		CursorWorldHitLocation = HitResult.Location;
		FVector HitNormal = HitResult.Normal;

		// Perform further actions based on the hit result
		// ...

		// Debug visualization of the line trace
		//DrawDebugLine(GetWorld(), TraceStart, HitResult.Location, FColor::Red, false, 20.0f);
		//DrawDebugSphere(GetWorld(), HitLocation, 100.0f, 16, FColor::Blue, false, 20.0f);
		return true;
	}
	bIsCursorPointing=false;
	return false;
}

void ATopDownPlayerController::CursorMovementReceiver(FVector Value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(" Hit Location :  %f = FloatVariable"), Value.X));
	DrawDebugSphere(GetWorld(), Value, 100.0f, 16, FColor::Blue, false, 20.0f);
}

void ATopDownPlayerController::OnActorDrag(UStaticMesh* Mesh)
{
/*	AStaticMeshActor* SpawnedActor;
	
	FVector SpawnLoc_Cursor = CursorWorldPosition+ (SpawnOffset_Cursor*CursorWorldDirection);
	
	FActorSpawnParameters SpawnParams ;
	SpawnParams.SpawnCollisionHandlingOverride =ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	if(bShouldDrag)
	{
		

		if(SpawnedActor==nullptr)
		{
			SpawnedActor = Cast<AStaticMeshActor>( GetWorld()->SpawnActor<AActor>(AStaticMeshActor::StaticClass(),SpawnLoc_Cursor + (CursorWorldDirection * 500), CursorWorldDirection.Rotation(), SpawnParams));
			if (SpawnedActor)
			{
				UStaticMeshComponent* MeshComponent = SpawnedActor->GetStaticMeshComponent();
				if (MeshComponent)
				{
					MeshComponent->SetStaticMesh(Mesh);
				}
			}
		}
	
		SpawnedActor->SetActorLocation(SpawnLoc_Cursor);

		if (bIsCursorPointing)
		{
			if(HitTile!=nullptr)
			{
				FVector SpawnLoc_Tile = CursorWorldHitLocation+ (SpawnOffset_Tile*HitTile->Normal);
				SpawnedActor->SetActorLocation(SpawnLoc_Tile);
				if(IsLMBReleased )
				{
					SpawnedActor->SetActorLocation(CursorWorldHitLocation);
					SpawnedActor=nullptr;
				}
					
					
			}

		
		}
		else
		{
			if
		}
	}
	if(!bIsDragSucessfull)
	SpawnedActor->Destroy();
	*/
	
}

void ATopDownPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// Bind mouse movement to functions
	InputComponent->BindAxis(TEXT("MouseX"), this, &ATopDownPlayerController::OnMouseMoveXAxis);
	InputComponent->BindAxis(TEXT("MouseY"), this, &ATopDownPlayerController::OnMouseMoveYAxis);
	//InputComponent->BindAction(TEXT("MouseLMB"),IE_Pressed,this,&ATopDownPlayerController::OnMouseLC);



	
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
			EnhancedInputComp->BindAction(MouseLMB,ETriggerEvent::Triggered,this,&ATopDownPlayerController::OnMouseLMBHold);
			EnhancedInputComp->BindAction(MouseLMB,ETriggerEvent::Completed,this,&ATopDownPlayerController::OnMouseLMBReleased);
		}
		if(MouseRMB)
		{
			EnhancedInputComp->BindAction(MouseRMB,ETriggerEvent::Triggered,this,&ATopDownPlayerController::OnMouseRMBHold);
			EnhancedInputComp->BindAction(MouseRMB,ETriggerEvent::Completed,this,&ATopDownPlayerController::OnMouseRMBReleased);
			
		}
	}
	
}



