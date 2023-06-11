// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ProceduralGeneration/TileMesh/TileMesh.h"
#include "functional"
#include "Tile.generated.h"


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
	FMatrixPosition(int x , int y) :X(x),Y(y){}
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Position")
	int X ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Position")
	int Y ;
	FORCEINLINE FMatrixPosition GetPosition () { FMatrixPosition pos(X,Y); return pos;}
	// Constructors and other members...

	bool operator==(const FMatrixPosition& other) const
	{
		return X == other.X && Y == other.Y;
	}
};


UCLASS(BlueprintType)
class PROCEDURALGENERATION_API UTile : public UObject
{
	GENERATED_BODY()

public:

	// Constructor and distructor
	UTile();
	virtual ~UTile() override;
	//UTile(int id ,FMatrixPosition pos2d ,FVector worldloc  , TArray<UTileMesh>& totaltilemesh);

	void Init (int id ,FMatrixPosition pos2d ,FVector2D Unscaledloc , TArray<UTileMesh*>& totaltilemesh);
    
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	int ID ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	UTileMesh* SelectedTiledMesh;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	FMatrixPosition Position_2D ;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	FVector World_Location ;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	FVector2D World_Location_2D_UnScaled ;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tile")
	EcollapseStatus CollapseStatus ;
	
	void SetCollapseStatus( EcollapseStatus CollapseStatuss);
	
	bool bIsSaturated ;

	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category= "Tile")
	TArray<UTileMesh*> AllAvailableMeshToChooseFrom;
	
	
	
};


namespace std
{
	template <>
	struct hash<FMatrixPosition>
	{
		std::size_t operator()(const FMatrixPosition& position) const
		{
			std::size_t hashValue = 0;
			// Compute the hash value based on the members of FMatrixPosition
			// You can use the `std::hash` function for the individual members
			hashValue ^= std::hash<int>()(position.X);
			hashValue ^= std::hash<int>()(position.Y);
			return hashValue;
		}
	};
}