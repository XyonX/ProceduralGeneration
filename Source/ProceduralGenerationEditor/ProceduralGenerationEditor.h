#pragma once

#include "IAssetTools.h"
#include "IAssetTypeActions.h"
#include "Modules/ModuleManager.h"

class FMyEditorModule
	: public IHasMenuExtensibility
	, public IHasToolBarExtensibility
	, public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	virtual bool SupportsDynamicReloading() override;

	
	

public:	//INTERFACE  OVERIDES
	
	//~ IHasMenuExtensibility interface
	virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override;
	//~ IHasToolBarExtensibility interface
	virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override;


protected: //FUNCTION FOR CUSTOM ASSET  TYPE

	/** Registers asset tool actions. */
	void RegisterAssetTools();
	/** Unregisters asset tool actions. */
	void UnregisterAssetTools();
	
	void RegisterSettings();
	/** Unregister the text asset editor settings. */
	void UnregisterSettings();

	void RegisterAssetTypeAction(IAssetTools& AssetTools, const TSharedRef<IAssetTypeActions>& Action);

	void RegisterAssetFaccory();

	/** Registers main menu and tool bar menu extensions. */
	void RegisterMenuExtensions();
	/** Unregisters main menu and tool bar menu extensions. */
	void UnregisterMenuExtensions();

	void ConfigureDirectory (const IAssetTools& AssetTools);

	

private:
	
	/** Holds the menu extensibility manager. */
	TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;

	/** The collection of registered asset type actions. */
	TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetTypeActions;

	/** Holds the plug-ins style set. */
	TSharedPtr<ISlateStyle> Style;

	/** Holds the tool bar extensibility manager. */
	TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;
	
	
	
};

IMPLEMENT_MODULE(FMyEditorModule, MyEditorModule)