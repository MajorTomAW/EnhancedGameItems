#include "EnhancedGameItemsEditor.h"

#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "AssetActions/EnhancedGameItemsActions.h"
#include "GameItems/EnhancedGameItemDefinition.h"
#include "Style/EnhancedGameItemsEditorStyle.h"
#include "ThumbnailRenderer/EnhancedGameItemsThumbnailRenderer.h"

#define LOCTEXT_NAMESPACE "FEnhancedGameItemsEditorModule"

TSharedPtr<FSlateStyleSet> FEnhancedGameItemsEditorModule::StyleSet;

void FEnhancedGameItemsEditorModule::StartupModule()
{
    StyleSet = MakeShared<FEnhancedGameItemsEditorStyle>();
	UThumbnailManager::Get().RegisterCustomRenderer(UEnhancedGameItemDefinition::StaticClass(), UEnhancedGameItemsThumbnailRenderer::StaticClass());

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	RegisterAssetTypeActions(AssetTools, MakeShareable(new FEnhancedGameItemsActions(StyleSet.ToSharedRef())));
}

void FEnhancedGameItemsEditorModule::ShutdownModule()
{
}

bool FEnhancedGameItemsEditorModule::SupportsDynamicReloading()
{
	return true;
}

void FEnhancedGameItemsEditorModule::RegisterAssetTypeActions(IAssetTools& AssetTools, const TSharedRef<IAssetTypeActions>& Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FEnhancedGameItemsEditorModule, EnhancedGameItemsEditor)