

#include "CoreGenerator.h"
#include "CorePlugin/Helpers/FileImporter.h"
#include "ProceduralGeneration/Terrain/GridSection.h"
#include "ProceduralGeneration/Threading/GridGenerationWorker.h"


UCoreGenerator::UCoreGenerator()
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
	GenerateGridSections();

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
	UGridGenerationWorker* MeshGenerationWorker = NewObject<UGridGenerationWorker>();
	MeshGenerationWorker->SetParameters(this);
	FRunnableThread::Create(MeshGenerationWorker, TEXT("MeshGenerationThread"));

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
