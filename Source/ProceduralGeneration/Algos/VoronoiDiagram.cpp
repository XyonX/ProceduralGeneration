#include "VoronoiDiagram.h"


void UVoronoiDiagram::Init(TArray<FVector> InVertices, TArray<FVector> InSeeds)
{

	Vertices=InVertices;
	Seeds=InSeeds;

	// Initialize VoronoiData map with seed points as keys
	for (const FVector& Seed : Seeds)
	{
		VoronoiData.Add(Seed, TArray<FVector>());
	}

}

void UVoronoiDiagram::Run()
{
	for (const FVector& Vert : Vertices)
	{
		float ClosestSeedDistance = MAX_FLT;
		FVector ClosestSeed;

		for (const FVector& Seed : Seeds)
		{
			float SeedDistance = FVector::Distance(Vert, Seed);

			if (SeedDistance < ClosestSeedDistance)
			{
				ClosestSeedDistance = SeedDistance;
				ClosestSeed = Seed;
			}
		}

		TArray<FVector>& ValueArray = VoronoiData.FindChecked(ClosestSeed);
		ValueArray.Add(Vert);
	}

}
