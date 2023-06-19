// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DelegateHelper.generated.h"

//DECLARE Delegates Here
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMouseMovementDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMouseMovementDelegate, FVector, CursorHitLocation);

UCLASS()
class PROCEDURALGENERATION_API UDelegateHelper : public UObject
{
	GENERATED_BODY()
};
