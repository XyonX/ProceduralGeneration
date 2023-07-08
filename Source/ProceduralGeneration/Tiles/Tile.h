// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ProceduralGeneration/TileMesh/TileMesh.h"
#include "functional"
#include "CorePlugin/Spawnables/Spawnable.h"
#include "Tile.generated.h"


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
	//UTile(int id ,FVector2D pos2d ,FVector worldloc  , TArray<UTileMesh>& totaltilemesh);
	
	void Init (int id, FVector2D pos2d, FVector2D Unscaledloc, TMap<int32, USpawnable*>* TotalSpawnables );
    
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	int ID ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	USpawnable* SelectedSpawnable;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	FVector2D Position_2D ;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	FVector World_Location ;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	FVector2D World_Location_2D_UnScaled ;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	EcollapseStatus CollapseStatus ;
	
	void SetCollapseStatus( EcollapseStatus CollapseStatuss);
	
	bool bIsSaturated ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category= "Tile")
	TArray<USpawnable*> AllAvailableSpawnableToChooseFrom;
	
	
	
};