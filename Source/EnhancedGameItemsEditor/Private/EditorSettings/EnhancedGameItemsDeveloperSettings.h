//  Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameItems/EnhancedGameItemDefinition.h"
#include "EnhancedGameItemsDeveloperSettings.generated.h"

/**
 * Holds information about the default item style that's used in the content browser.
 */
USTRUCT(BlueprintType)
struct FEnhancedGameItemDefinitionStyle
{
	GENERATED_BODY()

public:

	FEnhancedGameItemDefinitionStyle()
	{
	}

	UPROPERTY(EditAnywhere, Category = "Style")
	FLinearColor Color = FColor::FromHex("A0F476FF");

	UPROPERTY(EditAnywhere, Category = "Style")
	bool bSRGB = true;

	UPROPERTY(EditAnywhere, Category = "Style")
	FLinearColor DefaultBackgroundColor = FColor::FromHex("1a1a1a");

	UPROPERTY(EditAnywhere, Category = "Style")
	bool bDefaultBackgroundSRGB = true;

	UPROPERTY(EditAnywhere, Category = "Style")
	TObjectPtr<UTexture2D> DefaultIconOverride = nullptr;
};

/**
 * Editor settings class for changing the visual representation of game items inside the content browser. 
 */
UCLASS(Config = EditorPerProjectUserSettings, DisplayName = "Enhanced Game Items Settings")
class ENHANCEDGAMEITEMSEDITOR_API UEnhancedGameItemsDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	//~ Begin UDeveloperSettings Interface
	virtual FName GetCategoryName() const override;
	//~ End UDeveloperSettings Interface

	/**
	 * Holds information about the default item style that's used in the content browser.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "Game Items", meta = (ForceInlineRow))
	FEnhancedGameItemDefinitionStyle DefaultItemStyle;
	
	/**
	 * Filter keywords for the display name of the items in the content browser should be the prefix of the class names that you use in the project.
	 * For example, if you have a class named NiceItemDefinition, you may want to remove the "Nice" prefix and only display it as Item Definition
	 */
	UPROPERTY(Config, EditAnywhere, Category = "Game Items", meta = (ForceInlineRow))
	TArray<FString> FilterKeywords{TEXT("World"), TEXT("Enhanced")};
};
