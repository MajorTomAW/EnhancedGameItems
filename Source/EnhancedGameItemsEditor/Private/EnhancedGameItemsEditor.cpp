#include "EnhancedGameItemsEditor.h"

#include "AssetToolsModule.h"
#include "ClassViewerFilter.h"
#include "ClassViewerModule.h"
#include "EnhancedGameItems.h"
#include "IAssetTools.h"
#include "AssetActions/EnhancedGameItemsActions.h"
#include "GameItems/EnhancedGameItemDefinition.h"
#include "GameItems/EnhancedWorldGameItemDefinition.h"
#include "Kismet2/SClassPickerDialog.h"
#include "Style/EnhancedGameItemsEditorStyle.h"
#include "ThumbnailRenderer/EnhancedGameItemsThumbnailRenderer.h"

#define LOCTEXT_NAMESPACE "FEnhancedGameItemsEditorModule"

EAssetTypeCategories::Type FEnhancedGameItemsEditorModule::GameItemAssetsCategory;

IMPLEMENT_MODULE(FEnhancedGameItemsEditorModule, EnhancedGameItemsEditor)

void FEnhancedGameItemsEditorModule::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	// PropertyModule.RegisterCustomClassLayout(UEnhancedGameItemDefinition::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FEnhancedGameItemDefinitionDetails::MakeInstance));
	
    StyleSet = MakeShared<FEnhancedGameItemsEditorStyle>();
	UThumbnailManager::Get().RegisterCustomRenderer(UEnhancedGameItemDefinition::StaticClass(), UEnhancedGameItemsThumbnailRenderer::StaticClass());

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	GameItemAssetsCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("GameItems")), LOCTEXT("GameItemsAssetCategory", "Game Items"));
	{
		RegisterAssetTypeActions(AssetTools, MakeShareable(new FEnhancedGameItemsActions(StyleSet.ToSharedRef())));	
	}
}

void FEnhancedGameItemsEditorModule::ShutdownModule()
{
}

bool FEnhancedGameItemsEditorModule::SupportsDynamicReloading()
{
	return true;
}

EAssetTypeCategories::Type FEnhancedGameItemsEditorModule::GetGameItemsAssetsCategory()
{
	return GameItemAssetsCategory;
}

void FEnhancedGameItemsEditorModule::RegisterAssetTypeActions(IAssetTools& AssetTools, const TSharedRef<IAssetTypeActions>& Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

////////////////////////////////////////////////////////////////////
// Class viewer filter
class FGameItemsClassParentFilter : public IClassViewerFilter
{
public:
	FGameItemsClassParentFilter()
		: DisallowedClassFlags(CLASS_Abstract | CLASS_Deprecated | CLASS_NewerVersionExists | CLASS_HideDropDown) {}

	// All children of these classes are allowed
	TSet<const UClass*> AllowedChildrenOfClasses;

	// Disallowed class flags
	EClassFlags DisallowedClassFlags;

	virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef<FClassViewerFilterFuncs> InFilterFuncs) override
	{
		return !InClass->HasAnyClassFlags(DisallowedClassFlags)
			&& InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InClass) != EFilterReturn::Failed;
	}

	virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef<const IUnloadedBlueprintData> InUnloadedClassData, TSharedRef<FClassViewerFilterFuncs> InFilterFuncs) override
	{
		return !InUnloadedClassData->HasAnyClassFlags(DisallowedClassFlags)
			&& InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InUnloadedClassData) != EFilterReturn::Failed;
	}
};

////////////////////////////////////////////////////////////////////
// Asset factories 
UEnhancedGameItemDefinition_Factory::UEnhancedGameItemDefinition_Factory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UEnhancedGameItemDefinition::StaticClass();
	bEditAfterNew = true;
	bCreateNew = true;
}

bool UEnhancedGameItemDefinition_Factory::ConfigureProperties()
{
	// nullptr the class so that the user has to select a class
	GameItemClass = nullptr;

	// Load the class viewer module to display a class picker
	FClassViewerModule& ClassViewerModule = FModuleManager::LoadModuleChecked<FClassViewerModule>("ClassViewer");

	// Fill in options
	FClassViewerInitializationOptions Options;
	Options.Mode = EClassViewerMode::ClassPicker;

	TSharedPtr<FGameItemsClassParentFilter> Filter = MakeShareable(new FGameItemsClassParentFilter);
	Filter->AllowedChildrenOfClasses.Add(UEnhancedGameItemDefinition::StaticClass());

	Options.ClassFilters.Add(Filter.ToSharedRef());

	const FText TitleText = LOCTEXT("CreateGameItem", "Pick Class For Game Item Definition Asset");
	UClass* ChosenClass = nullptr;
	const bool bPressedOk = SClassPickerDialog::PickClass(TitleText, Options, ChosenClass, UEnhancedGameItemDefinition::StaticClass());

	if (bPressedOk)
	{
		GameItemClass = ChosenClass;
	}
	
	return bPressedOk;
}

UObject* UEnhancedGameItemDefinition_Factory::FactoryCreateNew(
	UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UEnhancedGameItemDefinition* NewGameItem = nullptr;

	if (GameItemClass != nullptr)
	{
		return NewObject<UEnhancedGameItemDefinition>(InParent, GameItemClass, Name, Flags, Context);
	}
	else
	{
		check(Class->IsChildOf(UEnhancedGameItemDefinition::StaticClass()));
		return NewObject<UEnhancedGameItemDefinition>(InParent, Class, Name, Flags, Context);
	}
}

#undef LOCTEXT_NAMESPACE

