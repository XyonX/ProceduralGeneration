/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/


#include "programmedMeshActor.h"


// Sets default values
AprogrammedMeshActor::AprogrammedMeshActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AprogrammedMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AprogrammedMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

