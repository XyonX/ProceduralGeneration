// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLandscapeActor.h"



#include "IImageWrapper.h"
#include "Misc/FileHelper.h"
#include "IImageWrapperModule.h"

// Sets default values
ABaseLandscapeActor::ABaseLandscapeActor()
{

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	SetRootComponent(RootSceneComponent);

	PMC = CreateDefaultSubobject<UProceduralMeshComponent>("Procedural Mesh Component ");
	MapHeight =100000;
	MapWidth =100000;

	NumVertsX =1000;
	NumVertsY=1000;
	CellSizeX=MapHeight /(NumVertsX-1);
	CellSizeY=MapWidth/(NumVertsY-1);

	FilePath = FPaths::Combine(FPaths::ProjectDir(), TEXT("HeightMap/Heightmap_4096x4096_01.raw"));

}

// Called when the game starts or when spawned
void ABaseLandscapeActor::BeginPlay()
{
	Super::BeginPlay();
	
	if(ImportHeightMap(FilePath,4096,HeightMap))
	{
		
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
		return false;
	}

	// Get the image wrapper module
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));

	// Detect the image format from the file extension
	EImageFormat ImageFormat = ImageWrapperModule.DetectImageFormat(FileData.GetData(), FileData.Num());
	if (ImageFormat == EImageFormat::Invalid)
	{
		// Failed to detect the image format
		return false;
	}

	// Create the image wrapper for the detected format
	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(ImageFormat);
	if (!ImageWrapper.IsValid() || !ImageWrapper->SetCompressed(FileData.GetData(), FileData.Num()))
	{
		// Failed to create image wrapper or set the compressed data
		return false;
	}

	// Convert the image to RGBA32 format
	TArray64<uint8> RawData;
	if (!ImageWrapper->GetRaw(ERGBFormat::Gray, 8, RawData))
	{
		// Failed to get the raw data
		return false;
	}

	// Check if the image size matches the desired size
	if (ImageWrapper->GetWidth() != ImageSize || ImageWrapper->GetHeight() != ImageSize)
	{
		// Image size does not match the desired size
		return false;
	}

	// Clear the height map array
	OutHeightMap.Empty();

	// Iterate through the pixel data and extract the height values
	for (int32 i = 0; i < RawData.Num(); ++i)
	{
		// Convert the pixel value to a normalized height value in the range of 0.0 to 1.0
		float Height = static_cast<float>(RawData[i]) / 255.0f;
		// Add the height value to the height map array
		OutHeightMap.Add(Height);
	}

	return true;
	
}

FVector ABaseLandscapeActor::CalculateVertexNormal(const TArray<float>& inHeightMap, int32 inNumVertsX, int32 inNumVertsY,int32 VertexX, int32 VertexY)
{
	float CenterHeight = inHeightMap[VertexY*inNumVertsX+VertexX];
	float LeftHeight = inHeightMap[(VertexY-1)*inNumVertsX+VertexX];
	float RightHeight = inHeightMap[(VertexY+1)*inNumVertsX+VertexX];
	float TopHeight = inHeightMap[VertexY*inNumVertsX+(VertexX+1)];
	float BottomHeight = inHeightMap[VertexY*inNumVertsX+(VertexX-1)];

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
			FVector VertexLocation = FVector(X*CellSizeX,Y*CellSizeY,Height);
			Vertices.Add(VertexLocation);

			// Calculate the normal using neighboring vertices (optional)
			FVector Normal = CalculateVertexNormal(HeightMap, NumVertsX, NumVertsY, X, Y);
			Normals.Add(Normal);

			if( Y<NumVertsY-1 && X < NumVertsX-1)
			{
				int32 A = Y*NumVertsX+1 ;
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

	return true;

}

