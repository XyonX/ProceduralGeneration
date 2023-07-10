// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownPawn.h"
#include "Kismet/GameplayStatics.h"
#include "ProceduralGeneration/Actors/BaseGridActor.h"


// Sets default values
ATopDownPawn::ATopDownPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	TopDownCamera=CreateDefaultSubobject<UCameraComponent>("TopDownCamera");
	SetRootComponent(TopDownCamera);

	bAdjustCameraLocation=false;
	Offset_Vector =FVector ( 1000.0f,1000.0f,500.0f);
	Offset_Scaler =1;
}

// Called when the game starts or when spawned
void ATopDownPawn::BeginPlay()
{
	Super::BeginPlay();
	GridActor=GetGridActor();
	if(GridActor!= nullptr)
	{
		SetSpawnLocation();
	}
	
	
	
}

// Called every frame
void ATopDownPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATopDownPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UCameraComponent* ATopDownPawn::GetCameraComponent()
{
	return TopDownCamera;
}

ABaseGridActor* ATopDownPawn::GetGridActor()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseGridActor::StaticClass(), FoundActors);

	if(FoundActors.Num()>0)
	{
		GridActor = Cast<ABaseGridActor>(FoundActors[0]);

		if(GridActor)
		{
			return GridActor;
		}
	}
	
	return nullptr;
}

void ATopDownPawn::SetSpawnLocation()
{
	if(bAdjustCameraLocation)
	{
		FVector Loc = GridActor->GetActorLocation()+(Offset_Scaler*Offset_Vector);
		SetActorLocation(Loc);
	}
}

