#pragma once

#include "IAssetTools.h"
#include "IAssetTypeActions.h"
#include "Modules/ModuleManager.h"

class FMyEditorModule
	: public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	
	
};

IMPLEMENT_MODULE(FMyEditorModule, MyEditorModule)