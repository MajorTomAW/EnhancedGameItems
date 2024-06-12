#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class IAssetTypeActions;
class IAssetTools;

class FEnhancedGameItemsEditorModule : public IModuleInterface
{
public:
    //~ Begin IModuleInterface
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
    virtual bool SupportsDynamicReloading() override;
    //~ End IModuleInterface

    static FSlateImageBrush* DefaultBrush;
    static TSharedPtr<FSlateStyleSet> StyleSet;

protected:
    void RegisterAssetTypeActions(IAssetTools& AssetTools, const TSharedRef<IAssetTypeActions>& Action);

    TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;
};
