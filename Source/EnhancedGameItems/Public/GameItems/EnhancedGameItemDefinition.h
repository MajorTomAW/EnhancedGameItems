//  Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnhancedGameItemDefinition.generated.h"

enum class EEnhancedGameItemReleaseState : uint8;

/**
 * Base Game Item Definition class
 * Used to store common properties for all game items, can be extended to add more properties
 * Supports custom class Thumbnail rendering etc.
 */
UCLASS(BlueprintType, DisplayName = "Game Item Definition")
class ENHANCEDGAMEITEMS_API UEnhancedGameItemDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UEnhancedGameItemDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~ Begin UEnhancedGameItemDefinition Interface
	virtual bool IsItemValid() const;
	//~ End UEnhancedGameItemDefinition Interface
	
#if WITH_EDITOR
	//~ Begin UObject Interface
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
	//~ End UObject Interface

	/**
	 * Called to generate a new serial number for this item.
	 * Only required for items that have its current release state set to "Released" or "Coming Soon"
	 */
	UFUNCTION(CallInEditor, Category = "Management")
	void GenerateSerialNumber();

	/**
	 * Called to invalidate the current serial number for this item.
	 */
	UFUNCTION(CallInEditor, Category = "Management")
	void InvalidateSerialNumber();
#endif

	//~ Begin UPrimaryDataAsset Interface
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	//~ End UPrimaryDataAsset Interface

public:
	/**
	 * The unique serial number for this item, used to identify it in the game or editor.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Managements")
	FGuid ItemSerialNumber;

	/**
	* The release state of the item.
	* Used to determine if the asset manager should find the item.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Managements")
	EEnhancedGameItemReleaseState ReleaseState;

	/**
	 * Used to display the item name in the UI or in the world.
	 * Supports' localization.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Item")
	FText ItemDisplayName;

	/**
	 * Used to explain the item even further, will be displayed in the UI or in the world.
	 * Supports' localization.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Item")
	FText ItemDescription;

	/**
	 * The icon that represents the item in the UI.
	 * EDITOR: This texture will be used to render the custom class thumbnail.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Item")
	TSoftObjectPtr<UTexture2D> ItemIcon;
};
