/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/


#include "DebugPointMesh.h"

ADebugPointMesh::ADebugPointMesh()
{
	// Create the Procedural Mesh Component
	ProceduralMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMeshComponent"));
	RootComponent = ProceduralMeshComponent;
}

ADebugPointMesh::~ADebugPointMesh()
{
	
}

void ADebugPointMesh::CreateMesh()
{/*
	// Define the vertices of the cube
	FVector Vertices[] = {
		FVector(-50.0f, -50.0f, -50.0f),  // Bottom left back
		FVector(50.0f, -50.0f, -50.0f),   // Bottom right back
		FVector(-50.0f, 50.0f, -50.0f),   // Top left back
		FVector(50.0f, 50.0f, -50.0f),    // Top right back
		FVector(-50.0f, -50.0f, 50.0f),   // Bottom left front
		FVector(50.0f, -50.0f, 50.0f),    // Bottom right front
		FVector(-50.0f, 50.0f, 50.0f),    // Top left front
		FVector(50.0f, 50.0f, 50.0f)      // Top right front
	  };

	// Define the triangles that make up the cube
	int32 Triangles[] = {
		0, 2, 1,  // Back face
		1, 2, 3,
		4, 5, 6,  // Front face
		5, 7, 6,
		0, 1, 4,  // Left face
		1, 5, 4,
		2, 6, 3,  // Right face
		3, 6, 7,
		0, 4, 2,  // Bottom face
		2, 4, 6,
		1, 3, 5,  // Top face
		3, 7, 5
	  };

	// Define the normals of the cube (in this case, we use the face normals)
	FVector Normals[] = {
		FVector(0.0f, 0.0f, -1.0f),  // Back face
		FVector(0.0f, 0.0f, -1.0f),
		FVector(0.0f, 0.0f, -1.0f),
		FVector(0.0f, 0.0f, -1.0f),
		FVector(0.0f, 0.0f, 1.0f),   // Front face
		FVector(0.0f, 0.0f, 1.0f),
		FVector(0.0f, 0.0f, 1.0f),
		FVector(0.0f, 0.0f, 1.0f),
		FVector(-1.0f, 0.0f, 0.0f),  // Left face
		FVector(-1.0f, 0.0f, 0.0f),
		FVector(-1.0f, 0.0f, 0.0f),
		FVector(-1.0f, 0.0f, 0.0f),
		FVector(1.0f, 0.0f, 0.0f),   // Right face
		FVector(1.0f, 0.0f, 0.0f),
		FVector(1.0f, 0.0f, 0.0f),
		FVector(1.0f, 0.0f, 0.0f),
		FVector(0.0f, -1.0f, 0.0f),  // Bottom face
		FVector(0.0f, -1.0f, 0.0f),
		FVector(0.0f, 1.0f, 0.0f),   // Top face
		FVector(0.0f, 1.0f, 0.0f),
		
		};

	// Define the texture coordinates of the cube
	FVector2D UVs[] = {
		FVector2D(0.0f, 0.0f),   // Back face
		FVector2D(1.0f, 0.0f),
		FVector2D(0.0f, 1.0f),
		FVector2D(1.0f, 1.0f),
		FVector2D(0.0f, 0.0f),   // Front face
		FVector2D(1.0f, 0.0f),
		FVector2D(0.0f, 1.0f),
		FVector2D(1.0f, 1.0f),
		FVector2D(0.0f, 0.0f),   // Left face
		FVector2D(1.0f, 0.0f),
		FVector2D(0.0f, 1.0f),
		FVector2D(1.0f, 1.0f),
		FVector2D(0.0f, 0.0f),   // Right face
		FVector2D(1.0f, 0.0f),
		FVector2D(0.0f, 1.0f),
		FVector2D(1.0f, 1.0f),
		FVector2D(0.0f, 0.0f),   // Bottom face
		FVector2D(1.0f, 0.0f),
		FVector2D(0.0f, 1.0f),
		FVector2D(1.0f, 1.0f),
		FVector2D(0.0f, 0.0f),   // Top face
		FVector2D(1.0f, 0.0f),
		FVector2D(0.0f, 1.0f),
		FVector2D(1.0f, 1.0f),
	  };

		// Define the vertex colors of the cube (in this case, we use white)
		FColor Colors[] = {
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
			FColor::White,
		};

	// Define the triangle indices of the cube (note that each face is made up of two triangles)
	int32 Indices[] = {
		0, 1, 2, 2, 1, 3,         // Back face
		4, 6, 5, 6, 7, 5,         // Front face
		8, 9, 10, 10, 9, 11,      // Left face
		12, 14, 13, 14, 15, 13,   // Right face
		16, 17, 18, 18, 17, 19,   // Bottom face
		20, 22, 21, 22, 23, 21    // Top face
	  };

	// Create a new static mesh
	UStaticMesh* Mesh = NewObject<UStaticMesh>();
/*
	// Initialize the mesh with the vertex positions, normals, UVs, vertex colors, and triangle indices
	Mesh->InitResources();
	Mesh->Materials.Empty();
	Mesh->Materials.Add(NULL);
	Mesh->AddSourceModel().Build(
	  [Vertices, Normals, UVs, Colors, Indices](FStaticMeshLODResourcesBuilder& LODModel)
	  {
		FStaticMeshSection& Section = LODModel.AddSection();
		Section.MaterialIndex = 0;

		int32 NumVerts = ARRAY_COUNT(Vertices);
		for (int32 i = 0; i < NumVerts; ++i)
		{
		  LODModel.Positions.Add(Vertices[i]);
		  LODModel.TexCoords[0].Add(UVs[i]);
		  LODModel.VertexColors.Add(Colors[i]);
		  LODModel.Tangents.Add(FVector::ZeroVector);
		  LODModel.BinormalSigns.Add(1.0f);
		  LODModel.NormalIndices.Add(i);
		}

		int32 NumIndices = ARRAY_COUNT(Indices);
		for (int32 i = 0; i < NumIndices; ++i)
		{
		  LODModel.IndexBuffer.Add(Indices[i]);
		}
	  });

	// Build the mesh's collision data (in this case, we use simple box collision)
	Mesh->CreateBodySetup();
	Mesh->BodySetup->AggGeom.BoxElems.Add(FKBoxElem(FVector(50.0f, 50.0f, 50.0f)));

	return Mesh;*/
}
