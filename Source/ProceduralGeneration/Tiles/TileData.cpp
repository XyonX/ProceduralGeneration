// Fill out your copyright notice in the Description page of Project Settings.


#include "TileData.h"

UTileData::UTileData()
{
}

UTileData::UTileData(FVector2D in_Loc2D, FVector in_LocWorld, int in_Index,TArray<FVector>* in_Vertices,
                     int Len_X, int Len_Y)
{
	Index =in_Index;
	Loc2D=in_Loc2D;
	LocationWorld =in_LocWorld;
	Vertices=in_Vertices;
	Length_X=Len_X;
	Length_Y=Len_Y;
}

void UTileData::Const(FVector2D in_Loc2D, FVector in_LocWorld, int in_Index, int Len_X, int Len_Y)
{
	Index =in_Index;
	Loc2D=in_Loc2D;
	LocationWorld =in_LocWorld;
	Length_X=Len_X;
	Length_Y=Len_Y;

}

void UTileData::Init(TArray<FVector>* in_Vertices )
{
	Vertices=in_Vertices;
	TArray<FVector>Verts = GetVertices(Index);
	
	Normal= CalculateNorMal(Verts);
	CenterPoint= CalculateCenterPoint(Verts);
}



FVector UTileData::CalculateNorMal(TArray<FVector>&in_Verts)
{
	FVector A =in_Verts[0];
	FVector B =in_Verts[1];
	FVector C =in_Verts[2];
	FVector D =in_Verts[3];
	
	return FVector::CrossProduct(A-B,C-A).GetSafeNormal();
	
}

FVector UTileData::CalculateCenterPoint(TArray<FVector>& in_Verts)
{
	FVector A =in_Verts[0];
	FVector B =in_Verts[1];
	FVector C =in_Verts[2];
	FVector D =in_Verts[3];

	return (A+B+C+D)/4;
	
}

TArray<FVector> UTileData::GetVertices(int in_Index)
{
	TArray<FVector>Verts ;
	TArray<FVector>VertC = *Vertices;
	FVector X00 =VertC[in_Index] ;
	FVector X10 =VertC[in_Index+1] ;
	FVector X11 =VertC[in_Index+Length_X+1] ;
	FVector X12 =VertC[in_Index+Length_X+2] ;

	Verts.Add(X00);
	Verts.Add(X10);
	Verts.Add(X11);
	Verts.Add(X12);

	return Verts;
}