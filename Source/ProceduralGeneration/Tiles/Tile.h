/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/

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
	
	
	void Init (int InIndex, FVector2D InPos2D,FVector InWorldLocation);

	bool AllocateSpawnables (TMap<int32, USpawnable*>* InTotalSpawnables);
	
	EcollapseStatus GetCollapseStatus (){return CollapseStatus;};
	void SetCollapseStatus( EcollapseStatus CollapseStatuss);

	int GetID (){return Index;};
	void SetID (int InID){Index=InID;};
	
	FVector GetWorldLocation (){return  World_Location;};
	void SetWorldLocation (FVector InWorldLocation){World_Location=InWorldLocation;};
	
	FVector2D GetPosition2D (){return Position_2D ;};
	void SetPosition2D (FVector2D InPosition2D){Position_2D=InPosition2D;};

	
	bool IsSaturated (){return bIsSaturated;};
	void SetSaturated (bool InbIsSaturated){bIsSaturated=InbIsSaturated;};

	
	TArray<USpawnable*> GetSupportedSpawnable (){return AllocatedSpawnables;};
	void SetSupportedSpawnable (TArray<USpawnable*> InAvailableSpawnable){AllocatedSpawnables = InAvailableSpawnable;};

	USpawnable* GetSelectedSpawnable (){return  SelectedSpawnable;};
	void SetSelectedSpawnable (USpawnable*InSpawnable){SelectedSpawnable=InSpawnable;};



	
private:
	
	
	UPROPERTY()
	int Index ;
	UPROPERTY()
	USpawnable* SelectedSpawnable;
	UPROPERTY()
	TArray<USpawnable*> AllocatedSpawnables;
	UPROPERTY()
	FVector2D Position_2D ;
	UPROPERTY()
	FVector World_Location ;
	UPROPERTY()
	EcollapseStatus CollapseStatus ;
	bool bIsSaturated ;
	
};