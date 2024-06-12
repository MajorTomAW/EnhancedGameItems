//  Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedGameItemDefinition.h"
#include "EnhancedWorldGameItemDefinition.generated.h"

/**
 * World Game Item Definition class
 * Can be placed in the world or dragged into the viewport
 * Mostly something that the player can interact with in the world
 */
UCLASS(DisplayName = "World Game Item Definition")
class ENHANCEDGAMEITEMS_API UEnhancedWorldGameItemDefinition : public UEnhancedGameItemDefinition
{
	GENERATED_BODY()

public:
	UEnhancedWorldGameItemDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	/**
	 * Actor class that will be spawned by this item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "World Game Item")
	TSoftClassPtr<AActor> WorldGameItemActor;
};
