// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLandscapeActor.h"



#include "IImageWrapper.h"
#include "Misc/FileHelper.h"
#include "IImageWrapperModule.h"

// Sets default values
ABaseLandscapeActor::ABaseLandscapeActor()
{

	//RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	//SetRootComponent(RootSceneComponent);

	PMC = CreateDefaultSubobject<UProceduralMeshComponent>("PMC ");
	SetRootComponent(PMC);
	MapHeight =1000000;
	MapWidth =1000000;

	NumVertsX =1024;
	NumVertsY=1024;
	CellSizeX=MapHeight /(NumVertsX-1);
	CellSizeY=MapWidth/(NumVertsY-1);

	//FilePath = FPaths::Combine(FPaths::ProjectDir(), TEXT("HeightMap/Heightmap_4096x4096_01.raw"));
	FilePath = FPaths::Combine(FPaths::ProjectDir(), TEXT("HeightMap/Heightmap_1024x1024_01.raw"));

	HeightMultiplier=1;

}

// Called when the game starts or when spawned
void ABaseLandscapeActor::BeginPlay()
{
	Super::BeginPlay();
	
	if(ImportHeightMap(FilePath,1024,HeightMap))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red,"Height Map Import Successful");
		GenerateLandscape();
	}

}



bool ABaseLandscapeActor::ImportHeightMap(const FString& inFilePath, int32 ImageSize, TArray<float>& OutHeightMap)
{
	// Load the image file
	TArray<uint8> FileData;
	if (!FFileHelper::LoadFileToArray(FileData, *inFilePath))
	{
		// Failed to load the file
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "Failed to load the file");
		return false;
	}

	// Calculate the expected size of the raw data based on the desired image size
	int32 ExpectedDataSize = ImageSize * ImageSize * sizeof(uint8);

	if (FileData.Num() != ExpectedDataSize)
	{
		// Invalid data size
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "Invalid data size");
		return false;
	}

	// Clear the height map array
	OutHeightMap.Empty();

	// Iterate through the raw data and extract the height values
	for (int32 i = 0; i < FileData.Num(); ++i)
	{
		// Cast the uint8 value to float and normalize within the range of 0.0 to 1.0
		float Height = static_cast<float>(FileData[i]) / 255.0f;
		// Add the height value to the height map array
		OutHeightMap.Add(Height);
	}

	return true;
	
}

FVector ABaseLandscapeActor::CalculateVertexNormal(const TArray<float>& inHeightMap, int32 inNumVertsX, int32 inNumVertsY, int32 VertexX, int32 VertexY)
{
	float CenterHeight = inHeightMap[VertexY * inNumVertsX + VertexX];

	// Check boundary conditions for neighboring vertices
	float LeftHeight = (VertexY > 0) ? inHeightMap[(VertexY-1)*inNumVertsX+VertexX] : CenterHeight;
	float RightHeight = (VertexY < inNumVertsY - 1) ? inHeightMap[(VertexY+1)*inNumVertsX+VertexX] : CenterHeight;
	float TopHeight =  (VertexX < inNumVertsX - 1)? inHeightMap[VertexY*inNumVertsX+(VertexX+1)] : CenterHeight;
	float BottomHeight = (VertexX > 0) ? inHeightMap[VertexY*inNumVertsX+(VertexX-1)] : CenterHeight;

	// Calculate the gradient in the X and Y directions
	float GradientX = RightHeight - LeftHeight;
	float GradientY = BottomHeight - TopHeight;

	// Calculate the normal vector using the gradient
	FVector Normal(GradientX, -GradientY, 1.0f);
	Normal.Normalize();

	return Normal;
}



bool ABaseLandscapeActor::GenerateLandscape()
{
	for (int32 Y =0 ; Y<NumVertsY;Y++)
	{
		for (int X = 0; X <NumVertsX ; X++)
		{
			float Height = HeightMap[Y*NumVertsX + X];
			FVector VertexLocation = FVector(X*CellSizeX,Y*CellSizeY,Height*HeightMultiplier);
			Vertices.Add(VertexLocation);

			// Calculate the normal using neighboring vertices (optional)
			FVector Normal = CalculateVertexNormal(HeightMap, NumVertsX, NumVertsY, X, Y);
			Normals.Add(Normal);

			if( Y<NumVertsY-1 && X < NumVertsX-1)
			{
				int32 A = Y*NumVertsX+X ;
				int32 B = (Y+1)*NumVertsX +X;
				int32 C =B+1;
				int32 D =A+1;

				Triangles.Add(A);
				Triangles.Add(B);
				Triangles.Add(C);

				Triangles.Add(C);
				Triangles.Add(D);
				Triangles.Add(A);
			}
		}
		
	}

	PMC->CreateMeshSection(0,Vertices,Triangles,Normals,TArray<FVector2D>(), TArray<FColor>(), TArray<FProcMeshTangent>(), true);

	if(LandscapeMaterial)
	{
		PMC->SetMaterial(0,LandscapeMaterial);
	}

	

	return true;

}

