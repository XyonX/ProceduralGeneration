using UnrealBuildTool;

public class ProceduralGenerationEditor : ModuleRules
{
    public ProceduralGenerationEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "Slate",
            "SlateCore",
            "UnrealEd",
            
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "ProceduralGeneration", "EditorStyle","UnrealEd","Slate","EditorFramework","Serialization", "EditorStyle","Projects", "WorkspaceMenuStructure", "WorkspaceMenuStructure"
        });
    }
}
