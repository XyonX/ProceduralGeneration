#include "PerlinNoise.h"

#include "Kismet/KismetMathLibrary.h"

UPerlinNoise::UPerlinNoise()
{
	GridSize = FVector2D(256,256);
}

float UPerlinNoise::Interpolate(float A, float B, float T)
{
	return (1 - T) * A + T * B ;
}

void UPerlinNoise::Init(FVector2D InGridSize)
{
	GridSize=InGridSize;
}

void UPerlinNoise::Run()
{
	for ( int Y = 0 ; Y < GridSize.Y ; Y++)
	{
		for (int X =0 ; X <GridSize.X ; X++)
		{
			// Generate random angle
			float angle = UKismetMathLibrary::RandomFloatInRange(0, 2 * PI);

			// Convert angle to gradient vector
			FVector2D Gradient(FMath::Cos(angle), FMath::Sin(angle));
			Gradient.Normalize();

			//Displacement of the pixel
			FVector2D Displacement = FVector2D(X,Y);

			// Dot Between	Gradient and Displacement
			float DotProduct = Gradient.X * Displacement.X + Gradient.Y * Displacement.Y;

			// Interpolate dot product using linear interpolation
			float InterpolatedValue = Interpolate(0, 1, DotProduct);

			// Store the interpolated value
			PerlinData.Add(InterpolatedValue);

		}
	}
}