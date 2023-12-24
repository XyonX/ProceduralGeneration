

#include "CoreGenerator.h"
#include "CorePlugin/Helpers/FileImporter.h"
#include "ProceduralGeneration/Terrain/GridSection.h"
#include "Async/Async.h"
#include "ProceduralGeneration/Threading/GridGenerationWorker.h"


UCoreGenerator::UCoreGenerator()
{
	
}

void UCoreGenerator::CustomTick()
{
	
}

UGridSection* UCoreGenerator::Run( )
{
	Owner = GetTypedOuter<AActor>();
	if (Owner == nullptr)
	{
		return nullptr;
	}
	ProceduralMesh= NewObject<UProceduralMeshComponent>(Owner);
	ProceduralMesh->RegisterComponent();
	//ProceduralMesh->SetupAttachment(Owner->GetRootComponent());
	ProceduralMesh->SetVisibility(true);
	ProceduralMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ProceduralMesh->Activate();
	if(ProceduralMesh == nullptr)
	{
		return nullptr;
	}

	Init(Defaults);
	ConfigureGrid();
	GenerateGrid( GridSize ,Grid );
	//GenerateGridSections();
	GenerateGridSections_Async();

	//return  DynamicGirdSection;
	return nullptr;
}

bool UCoreGenerator::Init(FGridData GridData)
{
	HeightMapPath=GridData.HeightMapFilePath;
    Origin=GridData.CustomOrigin;
	QuadDensity_Lod0 = GridData.QuadDensity_Lod0;
	NumOfSection=GridData.NumOfGridSections;
	DefaultMaterial=GridData.DefaultMaterial;
	

	
	return true;
}

void UCoreGenerator::ConfigureGrid()
{
	
	SectionSize=FVector2D(50'00,50'00);
	GridSize=SectionSize*NumOfSection;
	ComponentSize =FVector2D(10'00,10'00);
	NumOfComponentsPerSection =SectionSize/ComponentSize;
	
	NumVerts_Lod0 =((GridSize/100) *QuadDensity_Lod0)+1;
	NumVerts_Lod1 =((GridSize/100)*QuadDensity_Lod1)+1;

	Center=Origin+FVector(GridSize.X/2,GridSize.Y/2,0);
	
	Extents = FVector(GridSize.X/2,GridSize.Y/2,0);
	HeightMultiplier=1;
	HeightMapPath = FPaths::Combine(FPaths::ProjectDir(), TEXT("HeightMap/Heightmap_1024x1024_01.raw"));
	AFileImporter::ImportHeightMap(HeightMapPath, 1024, HeightMap);
}

bool UCoreGenerator::GenerateGrid(FVector2D InGridSize, TArray<UGridSection*>& OutGrid)
{
	int index=0;
	for (int32 Y = 0 ; Y<  NumVerts_Lod0.Y ; Y++)
	{
		for (int32 X = 0 ; X<NumVerts_Lod0.X ; X++)
		{
			//float Height = HeightMap[(Y*NumVerts_Lod0.X)+X];
			int32 DistanceBetweenVertex_X = 100/QuadDensity_Lod0.X;
			int32 DistanceBetweenVertex_Y = 100/QuadDensity_Lod0.Y;

			float Height = HeightMap[Y*1024+X];
			FVector Location = FVector(X*DistanceBetweenVertex_X,Y*DistanceBetweenVertex_Y,Height*HeightMultiplier);
			Vertices.Add(Location);
		}
	}
	return true;
}

bool UCoreGenerator::GenerateGridSections()
{
	//UGridGenerationWorker* MeshGenerationWorker = NewObject<UGridGenerationWorker>();
	//MeshGenerationWorker->SetParameters(this);
	//FRunnableThread::Create(MeshGenerationWorker, TEXT("MeshGenerationThread"));

	//if(Generator==nullptr)
	//{
		//return;
	//}

	
	int32 SectionIndex =0;

	for (int32 SecY =0 ;SecY<NumOfSection.Y ; SecY++)
	{
		for(int32 SecX =0 ;SecX<NumOfSection.X ; SecX++)
		{
			SectionIndex++;
			UGridSection*Section =NewObject<UGridSection>(Owner);
			Section->Index=SectionIndex;

			FVector2D Pos2D = FVector2D(SecX,SecY);
			FVector WorldLocation = FVector (SecX*SectionSize.X,SecY*SectionSize.Y,0);
			Section->Pos2D =Pos2D;
			Section->WorldLocation =WorldLocation;
			Section->Center =WorldLocation+FVector(SectionSize.X/2,SectionSize.Y/2,0);

			int SecStartY =(SecY*(SectionSize.Y/100)*QuadDensity_Lod0.Y);
			int  SecEndY =((SecY+1)*(SectionSize.Y/100)*QuadDensity_Lod0.Y);
			int  SecStartX =(SecX*(SectionSize.X/100)*QuadDensity_Lod0.X);
			int SecEndX =((SecX+1)*(SectionSize.X/100)*QuadDensity_Lod0.X);

			Section->Init(Owner,SectionIndex,Vertices,SectionSize,ComponentSize,QuadDensity_Lod0,ProceduralMesh,NumVerts_Lod0,DefaultMaterial);
			AddSectionToGrid(Section);
		}
	}

	return true;
}

bool UCoreGenerator::GenerateGridSections_Async()
{
	FGraphEventRef MyTask = FFunctionGraphTask::CreateAndDispatchWhenReady([&]()
	{
		GenerateGridSections ();
	}, TStatId(), nullptr, ENamedThreads::AnyThread);

	return true;
}

bool UCoreGenerator::AddSectionToGrid(UGridSection* InSection)
{
	Grid.Add(InSection);
	return true;
}

void UCoreGenerator::Receiver_OnCharacterMovement(FVector CharacterLocation)
{

	
	
}
