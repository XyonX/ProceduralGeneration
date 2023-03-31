// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProceduralGeneration.h"

#include "EditorStyleSet.h"
#include "Internationalization//Internationalization.h"
#include "WorkspaceMenuStructure/Public/WorkspaceMenuStructure.h"
#include "WorkspaceMenuStructure/Public/WorkspaceMenuStructureModule.h"


#define LOCTEXT_NAMESPACE "FProceduralGenerationModule"

void FProceduralGenerationModule::StartupModule()
{
	

}

void FProceduralGenerationModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FProceduralGenerationModule, ProceduralGeneration)