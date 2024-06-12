#pragma once

#include "CoreMinimal.h"
#include "AssetTypeCategories.h"
#include "Factories/Factory.h"
#include "Modules/ModuleManager.h"
#include "EnhancedGameItemsEditor.generated.h"

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

    static EAssetTypeCategories::Type GetGameItemsAssetsCategory();

    static FSlateImageBrush* DefaultBrush;

protected:
    void RegisterAssetTypeActions(IAssetTools& AssetTools, const TSharedRef<IAssetTypeActions>& Action);

    static EAssetTypeCategories::Type GameItemAssetsCategory;

    TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;
    TSharedPtr<FSlateStyleSet> StyleSet;
};

////////////////////////////////////////////////////////////////////
// Asset factories

UCLASS()
class ENHANCEDGAMEITEMSEDITOR_API UEnhancedGameItemDefinition_Factory : public UFactory
{
    GENERATED_UCLASS_BODY()
public:
    UPROPERTY(EditAnywhere, Category = GameItem)
    TSubclassOf<class UEnhancedGameItemDefinition> GameItemClass;

    virtual bool ConfigureProperties() override;
    virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};