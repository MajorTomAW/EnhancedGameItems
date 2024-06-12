using UnrealBuildTool;

public class EnhancedGameItemsEditor : ModuleRules
{
    public EnhancedGameItemsEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "AssetTools",
                "AssetDefinition",
                "SlateCore",
                "Slate",
                "EditorStyle",
                "UnrealEd", 
                "PluginUtils",
                "ContentBrowser",
                "Projects",
                "UMG",
                "DeveloperSettings",
                "EnhancedGameItems",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "EnhancedGameItems",
                "UnrealEd",
            }
        );
    }
}