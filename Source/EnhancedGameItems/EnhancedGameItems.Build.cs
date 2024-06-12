// Some copyright should be here...

using UnrealBuildTool;

public class EnhancedGameItems : ModuleRules
{
	public EnhancedGameItems(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{ 
			"CoreUObject",
			"Engine",
		});
	}
}
