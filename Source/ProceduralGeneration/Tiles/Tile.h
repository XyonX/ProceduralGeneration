// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Tile.generated.h"

class USpawnable;

//Collapse status enum
UENUM(BlueprintType)
enum class EcollapseStatus : uint8
{
	NotCollapsed = 0		UMETA(DisplayName = "Not Collapsed"),
	Collapsed =1		UMETA(DisplayName = "Collaped")	
};


UCLASS(BlueprintType)
class PROCEDURALGENERATION_API UTile : public UObject
{
	GENERATED_BODY()

public:

	// Constructor and distructor
	UTile();
	virtual ~UTile() override;
	
	
	void Init (int id, FVector2D pos2d, TMap<int32, USpawnable*>* TotalSpawnables );
	
	EcollapseStatus GetCollapseStatus (){return CollapseStatus;};
	void SetCollapseStatus( EcollapseStatus CollapseStatuss);

	int GetID (){return ID;};
	void SetID (int InID){ID=InID;};
	
	FVector GetWorldLocation (){return  World_Location;};
	void SetWorldLocation (FVector InWorldLocation){World_Location=InWorldLocation;};
	
	FVector2D GetPosition2D (){return Position_2D ;};
	void SetPosition2D (FVector2D InPosition2D){Position_2D=InPosition2D;};

	
	bool IsSaturated (){return bIsSaturated;};
	void SetSaturated (bool InbIsSaturated){bIsSaturated=InbIsSaturated;};

	
	TArray<USpawnable*> GetSupportedSpawnable (){return AllAvailableSpawnableToChooseFrom;};
	void SetSupportedSpawnable (TArray<USpawnable*> InAvailableSpawnable){AllAvailableSpawnableToChooseFrom = InAvailableSpawnable;};

	USpawnable* GetSelectedSpawnable (){return  SelectedSpawnable;};
	void SetSelectedSpawnable (USpawnable*InSpawnable){SelectedSpawnable=InSpawnable;};

private:
	
	
	UPROPERTY()
	int ID ;
	UPROPERTY()
	USpawnable* SelectedSpawnable;
	UPROPERTY()
	TArray<USpawnable*> AllAvailableSpawnableToChooseFrom;
	UPROPERTY()
	FVector2D Position_2D ;
	UPROPERTY()
	FVector World_Location ;
	UPROPERTY()
	EcollapseStatus CollapseStatus ;
	bool bIsSaturated ;
	
};