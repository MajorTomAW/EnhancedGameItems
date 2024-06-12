//  Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"

/**
 * The release state of the item.
 * Used to determine if the asset manager should find the item.
 */
UENUM(BlueprintType)
enum class EEnhancedGameItemReleaseState : uint8
{
	/** The item is not set to any specific release state */
	Unset,

	/** The item is fully released and available for use */
	Released,

	/** The item is not released but is available for preview */
	ComingSoon,
};