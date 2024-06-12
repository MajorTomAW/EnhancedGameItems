//  Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ActorFactories/ActorFactory.h"
#include "EnhancedGameItemActorFactory.generated.h"

/**
 * 
 */
UCLASS()
class ENHANCEDGAMEITEMSEDITOR_API UEnhancedGameItemActorFactory : public UActorFactory
{
	GENERATED_BODY()

public:
	UEnhancedGameItemActorFactory();

	//~ Begin UActorFactory Interface
	virtual AActor* SpawnActor(UObject* InAsset, ULevel* InLevel, const FTransform& InTransform, const FActorSpawnParameters& InSpawnParams) override;
	virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;
	//~ End UActorFactory Interface
};
