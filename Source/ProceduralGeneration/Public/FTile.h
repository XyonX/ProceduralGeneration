// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FTileMesh.h"
#include "FTile.generated.h"


//Collapse status enum
UENUM(BlueprintType)
enum class EcollapseStatus : uint8
{
	NotCollapsed = 0		UMETA(DisplayName = "Not Collapsed"),
	Collapsed =1		UMETA(DisplayName = "Collaped")	
};


// 2D STRUCT FOR STORING XY LOCATION
USTRUCT(BlueprintType)
struct FMatrixPosition
{
	GENERATED_BODY()
	FMatrixPosition():X(0),Y(0){};
	FMatrixPosition(int height , int width) :X(height),Y(width){}
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Position")
	int X ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Position")
	int Y ;
	FORCEINLINE FMatrixPosition GetPosition () { FMatrixPosition pos(X,Y); return pos;}
};


USTRUCT(BlueprintType)
struct FTile
{
	GENERATED_BODY()

	FTile();
	FTile(int id ,FMatrixPosition pos2d ,FVector worldloc  , TArray<FTileMesh>& totaltilemesh); 

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	int ID ;
	//UPROPERTY(EditInstanceOnly,Category="Tile")
	FTileMesh* SelectedTiledMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	FMatrixPosition Position_2D ; 
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	FVector World_Location ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	EcollapseStatus CollapseStatus ;
	void SetCollapseStatus( EcollapseStatus CollapseStatuss);
	//UPROPERTY(BlueprintReadWrite,Category="Tile")
	TArray<FTileMesh* > AllAvailableMeshToChooseFrom;
	
	
	
};

UCLASS()
class PROCEDURALGENERATION_API UFTile : public UObject
{
	GENERATED_BODY()
};
