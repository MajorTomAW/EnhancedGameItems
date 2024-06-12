//  Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnhancedGameItemsInterface.generated.h"

class UEnhancedWorldGameItemDefinition;

// This class does not need to be modified.
UINTERFACE()
class ENHANCEDGAMEITEMS_API UEnhancedGameItemsInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface to be implemented in actors that can be spawned by Enhanced Game Items
 */
class ENHANCEDGAMEITEMS_API IEnhancedGameItemsInterface
{
	GENERATED_BODY()
public:
#if WITH_EDITOR
	/**
	 * Called whenever the actor has been spawned through a drag and drop operation in the viewport
	 * Editoronly
	 * @param InWorldGameItemDef	The definition of the Enhanced Game Item that was used to spawn the actor, could be used to set up the actor 
	 */
	virtual void PostDraggedInViewport(UEnhancedWorldGameItemDefinition* InWorldGameItemDef);
#endif
};
