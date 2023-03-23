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

	
	
	void RegisterAssetAction () ;
	void UnRegisterAssetAction ();

	void RegisterMenuExtensions();
	void UnregisterMenuExtensions();


private:
	TSharedPtr<IAssetTypeActions>CustomAssetActions;
	TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;
	TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;
	
};

IMPLEMENT_MODULE(FMyEditorModule, MyEditorModule)