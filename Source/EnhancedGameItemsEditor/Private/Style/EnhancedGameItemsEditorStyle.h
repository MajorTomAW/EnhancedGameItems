#pragma once

#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleMacros.h"
#include "Styling/SlateStyleRegistry.h"

class FEnhancedGameItemsEditorStyle final : public FSlateStyleSet
{
public:
	FEnhancedGameItemsEditorStyle() : FSlateStyleSet("EnhancedGameItemsEditorStyle")
	{
		const FString BaseDir = IPluginManager::Get().FindPlugin("EnhancedGameItems")->GetBaseDir();
		FSlateStyleSet::SetContentRoot(BaseDir / TEXT("Content"));
        
		FSlateStyleRegistry::RegisterSlateStyle(*this);

		SetParentStyleName(FAppStyle::GetAppStyleSetName());
		FSlateStyleSet::SetContentRoot(FPaths::EngineContentDir() / TEXT("Editor/Slate/UMG"));
		FSlateStyleSet::SetCoreContentRoot(FPaths::EngineContentDir() / TEXT("Slate"));

		static const FVector2D Icon16 = FVector2D(16.0f, 16.0f);
		static const FVector2D Icon64 = FVector2D(64.0f, 64.0f);

		FSlateStyleSet::SetContentRoot(FPaths::EngineContentDir() / TEXT("Editor/Slate/Starship/AssetIcons"));
		Set("ClassIcon.EnhancedGameItemDefinition", new IMAGE_BRUSH_SVG("DataAsset_16", Icon16));
	}

	~FEnhancedGameItemsEditorStyle()
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*this);
	}
};