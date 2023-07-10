// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownPlayerController.h"

#include "EnhancedInputComponent.h"
#include "../../../../../../../UE_5.1/Engine/Platforms/Hololens/Source/Runtime/ApplicationCore/Public/HoloLensPlatformApplicationMisc.h"
#include "Actions/AsyncAction_CreateWidgetAsync.h"
#include "Components/InputComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "CorePlugin/Spawnables/SpawnableActor.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "ProceduralGeneration/Tiles/TileData.h"

class ABaseGridActor;

ATopDownPlayerController::ATopDownPlayerController()
{
	bCanPan =false;
	HorizontalPanAcc=100;
	VerticalPanAcc=100;
	CursorRange=100000;
	//bShowCursor = true;
	SpawnOffset_Cursor = 2000.0f;
	SpawnOffset_Tile=0.0f;
	SnappingExtents.X = 2000;
	SnappingExtents.Y = 2000;
	SnappingExtents.Z = 2000;
	SnappingDistance =20;
}

void ATopDownPlayerController::BeginPlay()
{

	Super::BeginPlay();
	TopDownGameInstance = Cast<UTopDownGameInstance>(GetGameInstance());
	
	//ADelegateHelper::OnMouseMovementDelegate.AddDynamic(this,&ATopDownPlayerController::CursorMovementReceiver);
	ADelegateHelper::DragDelegate_Down.AddDynamic(this,&ATopDownPlayerController::OnCardDragReceiver_Down);
	//ADelegateHelper::OnDragDelegate.AddDynamic(this,&ATopDownPlayerController::OnCardDragReceiver);
	ADelegateHelper::OnDragDelegate.BindDynamic(this,&ATopDownPlayerController::OnCardDragReceiver);
	ADelegateHelper::DragDelegate_Up.AddDynamic(this,&ATopDownPlayerController::OnCardDragReceiver_Up);
	
	
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

	
	//FString DebugMessage = FString::Printf(TEXT("Velocity X : %f"),Value[0]);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DebugMessage);
	// Check if mouse movement velocity is below a threshold value (e.g., 1.0)
	///*if (FMath::IsNearlyZero(Value[0], 0.1f))
	//{
	//	MouseTrace();
	//}
		
	
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

	FVector2D MousePosition;
	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (LocalPlayer && LocalPlayer->ViewportClient)
	{
		LocalPlayer->ViewportClient->GetMousePosition(MousePosition);
		OnMouseMove(MousePosition);
	}
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


void ATopDownPlayerController::TraceInstanceInBound(UInstancedStaticMeshComponent* inISMC, FVector CenterPoint,FVector Extents, TArray<int32>& OutOverlappingIndices)
{
	
	FBox Bounds;
	
	FVector min = FVector(CenterPoint.X - (Extents.X) ,CenterPoint.Y-(Extents.Y),CenterPoint.Z-(Extents.Z));
	FVector max = FVector(CenterPoint.X + (Extents.X) ,CenterPoint.Y+(Extents.Y),CenterPoint.Z+(Extents.Z));

	Bounds.Min=min;
	Bounds.Max=max;
	
	if (inISMC)
	{

		DrawDebugBox(GetWorld(), CenterPoint,Extents,FColor::Green,false,-1.0f );
		OutOverlappingIndices= inISMC->GetInstancesOverlappingBox(Bounds,true);

	}

	
}

int32 ATopDownPlayerController::TraceSingleInstanceInBound(UInstancedStaticMeshComponent* inISMC, FVector CenterPoint)
{
	TArray<int32> OutOverlappingIndices;
	
	int32 X  =100;
	int32 Y =100;
	FBox Bounds;
	FVector min = FVector((CenterPoint.X - X/2) ,(CenterPoint.Y-Y/2),CenterPoint.Z);
	FVector max = FVector((CenterPoint.X + X/2) ,(CenterPoint.Y+Y/2),CenterPoint.Z+100);

	OutOverlappingIndices= inISMC->GetInstancesOverlappingBox(Bounds,true);

	if (OutOverlappingIndices.Num() > 0)
	{
		return OutOverlappingIndices[0];
	}

	return -1; // Indicate no instance found
}


int32 ATopDownPlayerController::CalculateClosestInstance(UInstancedStaticMeshComponent* inISMC, FVector HitLocation,TArray<int32>&inOverlappingIndices, int32 inCurrentInstanceIndex)
{
	
	float NearestDistance=100000 ;
	int32 NearestInstanceIndex = -1;
	FTransform NearestInstanceTransform;
	
	for	 (int i =0 ; i <inOverlappingIndices.Num() ; i++)
	{
		int32 index =inOverlappingIndices[i];
		FTransform OutTransform;
		inISMC->GetInstanceTransform(index,OutTransform,true);

		//float CurrentDistance =FVector::DistSquared(HitLocation,OutTransform.GetLocation());
		float CurrentDistance =FVector::Dist(HitLocation,OutTransform.GetLocation());
		if(CurrentDistance<NearestDistance)
		{
			NearestDistance=CurrentDistance;
			NearestInstanceIndex = index;
			NearestInstanceTransform = OutTransform ;

		}
		
	}

	//FString DebugMessage = FString::Printf(TEXT("Nearest Instance Location  : %f , %f,%f"),NearestInstanceLocation.X,NearestInstanceLocation.Y,NearestInstanceLocation.Z);
	//FString DebugMessage = FString::Printf(TEXT("Nearest Instance Index  : %d "),NearestInstanceIndex);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DebugMessage);
	
	return NearestInstanceIndex;
}

FVector ATopDownPlayerController::CalculateSnappingPoints(ASpawnableActor* SelectedActor,int32 TargetIndex , FVector HitLocation)
{
	FVector NearestSnappingPoint;
	

	FTransform TargetTransform;
	SelectedActor->GetInstanceMesh()->GetInstanceTransform(TargetIndex,TargetTransform,true);
	FVector TargetLocation = TargetTransform.GetLocation();
	FVector CenterOffset = CurrentSpawnable->GetPivotOffset_Center();
	FVector TargetCenterPivot = TargetLocation + CenterOffset;
	

	float lenx = CurrentSpawnable->MeshLength_X;
	float leny = CurrentSpawnable->MeshLength_Y;
	float lenz = CurrentSpawnable->MeshLength_Z;

	ETilingType TilingType = CurrentSpawnable->GetTilingType();

	if(TilingType==ETilingType::Horizontal)
	{
		FVector SnappingPoint1 =  FVector(TargetCenterPivot.X,TargetCenterPivot.Y+leny,TargetCenterPivot.Z);
		FVector SnappingPoint2 =  FVector(TargetCenterPivot.X,TargetCenterPivot.Y-leny,TargetCenterPivot.Z);

		float dist1 =  FVector::Dist(HitLocation,SnappingPoint1);
		float dist2 =	FVector::Dist(HitLocation,SnappingPoint2);

		if(dist1<dist2)
		{
			NearestSnappingPoint=SnappingPoint1;
		}
		else
		{
			NearestSnappingPoint=SnappingPoint2;
		}
		return NearestSnappingPoint-CenterOffset;
		
	}
	if(TilingType==ETilingType::Vertical)
	{
		FVector SnappingPoint1 =  FVector(TargetCenterPivot.X+lenx,TargetCenterPivot.Y,TargetCenterPivot.Z);
		FVector SnappingPoint2 =  FVector(TargetCenterPivot.X-lenx,TargetCenterPivot.Y,TargetCenterPivot.Z);

		float dist1 =  FVector::Dist(HitLocation,SnappingPoint1);
		float dist2 =	FVector::Dist(HitLocation,SnappingPoint2);

		if(dist1<dist2)
		{
			NearestSnappingPoint=SnappingPoint1;
		}
		else
		{
			NearestSnappingPoint=SnappingPoint2;
		}
		return NearestSnappingPoint-CenterOffset;
		
	}
	if(TilingType==ETilingType::BothDirection)
	{
		FVector SnappingPoints[4] ;
		SnappingPoints[0] =  FVector(TargetCenterPivot.X+lenx,TargetCenterPivot.Y,TargetCenterPivot.Z);
		SnappingPoints[1] =  FVector(TargetCenterPivot.X-lenx,TargetCenterPivot.Y,TargetCenterPivot.Z);
		SnappingPoints[2] =  FVector(TargetCenterPivot.X,TargetCenterPivot.Y+leny,TargetCenterPivot.Z);
		SnappingPoints[3] =  FVector(TargetCenterPivot.X,TargetCenterPivot.Y-leny,TargetCenterPivot.Z);

		float NearestDistance = 100000;
		for (int i =0 ; i< 4 ; i++)
		{
			FVector SnappingPoint =SnappingPoints[i];
			float dist = FVector::Dist(HitLocation,SnappingPoint);
			if(dist<NearestDistance)
			{
				NearestDistance=dist;
				NearestSnappingPoint=SnappingPoint;
			}
		}
		return NearestSnappingPoint-CenterOffset;
		
	}

	return HitLocation;

}

FVector2D ATopDownPlayerController::ScreenScapeToWindowSpace(FVector2D ScreeSpace)
{

	//int32 SizeX;
	//int32 SizeY;
	//GetViewportSize(SizeX,SizeY);
	
	TSharedPtr<SWindow> MainGameWindow= GEngine->GameViewport->GetWindow();

	FVector2D WindowPosition = MainGameWindow->GetPositionInScreen();
	FVector2D WindowSzie = MainGameWindow->GetSizeInScreen();

	FVector2D WindowSpace = ScreeSpace-WindowPosition;

	return WindowSpace;
	
	
}

void ATopDownPlayerController::OnMouseMove(const FVector2D& MousePosition)
{
	// Implement the logic for hovering over the grid and updating the mesh here
	// You can call the corresponding function in your grid actor or widget class
	//if (ABaseGridActor* GridActor = Cast<ABaseGridActor>(GetPawn()))
	//{
	//	GridActor->OnMouseMove(MousePosition);
	//}

	//FString DebugMessage = FString::Printf(TEXT("Screen pos , X : %f , Y : %f "),MousePosition.X,MousePosition.Y);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DebugMessage);

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
	
	ADelegateHelper::OnMouseMovementDelegate.Broadcast(	CursorWorldHitLocation);

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
	TraceParams.AddIgnoredActor(CursorActor);

	// Perform the line trace
	//if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, TraceParams))
	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, TraceParams))
	{
		bIsCursorPointing=true;
		CursorWorldHitLocation = HitResult.Location;

		
		// Debug visualization of the line trace
		//DrawDebugLine(GetWorld(), TraceStart, HitResult.Location, FColor::Red, false, 20.0f);
		//DrawDebugSphere(GetWorld(), CursorWorldHitLocation, 100.0f, 16, FColor::Blue, false, 20.0f);
		return true;
	}
	bIsCursorPointing=false;
	return false;
}

void ATopDownPlayerController::CursorMovementReceiver(FVector Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(" Hit Location :  %f = FloatVariable"), Value.X));
	DrawDebugSphere(GetWorld(), Value, 100.0f, 16, FColor::Blue, false, 20.0f);
/*	if (bIsCursorPointing)
	{
		
		UInstancedStaticMeshComponent*ISMC =Cast<UInstancedStaticMeshComponent>(MouseHitComponent);
		if(ISMC)
		{
			ASpawnableActor*SpawnableActor =Cast<ASpawnableActor>(MouseHitActor);
			UMaterialInterface* DefInterface = SpawnableActor->GetSpawnable()->GetMaterial_Interface();
			
			int32 ind= TraceSingleInstanceInBound(ISMC,HitResult.Location);
			if(ind >= 0)
			{
			
				if(DefaultMaterial)
				{
					
					ISMC->SetMaterial(ind,DefaultMaterial);
				}
				
			}
			else
			{
				ISMC->SetMaterial(ind,DefInterface);
			}

			
		}
		
		if(CurrentSpawnable != nullptr)
		{

			if(DefaultMaterial)
			CurrentSpawnableComponent->SetMaterial(HitInstanceIndex,DefaultMaterial);
		}
		
	}*/
	
}

void ATopDownPlayerController::OnCardDragReceiver_Down(USpawnable*inSpawnable)
{
	CurrentSpawnable=inSpawnable;
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride =ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	bShouldDrag_Card=true;
	FVector SpawnLoc =CursorWorldPosition + (CursorWorldDirection * SpawnOffset_Cursor);
	FTransform SpawnTransform = FTransform(FRotator::ZeroRotator,SpawnLoc);

	if(inSpawnable)
	{
		CurrentSpawnable=inSpawnable;
		if(inSpawnable->GetActor() ==nullptr)
		{
			return;
		}
		CurrentSpawnableActor= inSpawnable->GetActor();
		CurrentSpawnableActor->SetActorHiddenInGame(false);
		CurrentSpawnableComponent=CurrentSpawnableActor->GetInstanceMesh();
		if(CurrentSpawnableComponent==nullptr)
		{
			return;
		}
		CurrentSpawnableComponent->SetVisibility(true);
		CurrentInstanceIndex= CurrentSpawnableComponent->AddInstance(SpawnTransform);
		//FString DebugMessage = FString::Printf(TEXT("Instance Index : %d"),CurrentInstanceIndex);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DebugMessage);
		
	}
	
}

void ATopDownPlayerController::OnCardDragReceiver(FVector2D CursorPos )
{
	
	FVector2D CursorWindowSpace = ScreenScapeToWindowSpace(CursorPos);

	//FString DebugMessage = FString::Printf(TEXT("Windowed Position , X : %f , Y : %f "),CursorWindowSpace.X,CursorWindowSpace.Y);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DebugMessage);
	
	OnMouseMove(CursorWindowSpace);
	
	
	FVector SpawnLoc_Cursor =CursorWorldPosition + (CursorWorldDirection * SpawnOffset_Cursor);
	FTransform SpawnTransform_Cursor = FTransform(FRotator::ZeroRotator,SpawnLoc_Cursor);


	//DrawDebugLine(GetWorld(),CursorWorldPosition,CursorWorldPosition+(CursorWorldDirection*2000),FColor::Blue,true,-1,0,10);
	
if(CurrentSpawnable)
{
	ASpawnableActor*ISMC_Actor =CurrentSpawnable->GetActor();
	UInstancedStaticMeshComponent* ISMC =ISMC_Actor->GetInstanceMesh();
	
	if(ISMC)
	{
		if(bIsCursorPointing)
		{
			float Remainder_X = FMath::Fmod(HitResult.Location.X,SnappingDistance);
			float Remainder_Y = FMath::Fmod(HitResult.Location.Y,SnappingDistance);

			FVector newloc = FVector(HitResult.Location.X-Remainder_X,HitResult.Location.Y-Remainder_Y,HitResult.Location.Z);
			
			
			TArray<int32> OverlappingInstancesIndices;
			TraceInstanceInBound(ISMC,HitResult.Location,SnappingExtents,OverlappingInstancesIndices);

			//FString DebugMessage = FString::Printf(TEXT("Num Of Meshes In Bound : %d"),OverlappingInstancesIndices.Num());
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DebugMessage);

			OverlappingInstancesIndices.Remove(CurrentInstanceIndex);
			if(!OverlappingInstancesIndices.IsEmpty())
			{
				int32 index = CalculateClosestInstance(ISMC,newloc,OverlappingInstancesIndices,CurrentInstanceIndex);

				FVector NewSnappingLocation = CalculateSnappingPoints(CurrentSpawnableActor,index,newloc);
				
				FString DbgMessage = FString::Printf(TEXT("Nearest Isntance Index : %d"),index);
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DbgMessage);

				ISMC->UpdateInstanceTransform(CurrentInstanceIndex,FTransform(FRotator::ZeroRotator,NewSnappingLocation),true,true);
				
			}
			else
			{
				ISMC->UpdateInstanceTransform(CurrentInstanceIndex,FTransform(FRotator::ZeroRotator,newloc),true,true);
			}
			
			bIsObjectPlaced=true;
		}
		else
		{
			ISMC->UpdateInstanceTransform(CurrentInstanceIndex,SpawnTransform_Cursor,true,true,true);
			bIsObjectPlaced=false;
		}
		
	}
}
}
void ATopDownPlayerController::OnCardDragReceiver_Up()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Card Released");
	bShouldDrag_Card=false;

	if(CurrentSpawnableComponent)
	{
		if(bIsObjectPlaced)
		{
			CurrentSpawnableComponent=nullptr;
			//DrawDebugString(GetWorld(), Location, *FString::Printf(TEXT(" %f,%f"),Value.X, Value.Y), nullptr, FColor::Red, -1.0F, false);
			return;
		}
		CurrentSpawnableComponent->RemoveInstance(CurrentInstanceIndex);
	}
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



