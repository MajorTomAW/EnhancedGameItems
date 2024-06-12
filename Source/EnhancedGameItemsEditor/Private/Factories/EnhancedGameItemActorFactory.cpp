//  Copyright © 2024 MajorT. All rights reserved.


#include "EnhancedGameItemActorFactory.h"

#include "GameItems/EnhancedWorldGameItemDefinition.h"
#include "Interfaces/EnhancedGameItemsInterface.h"

class IEnhancedGameItemsInterface;

UEnhancedGameItemActorFactory::UEnhancedGameItemActorFactory()
{
	DisplayName = FText::FromString(TEXT("Enhanced Game Item Actor Factory"));
	NewActorClass = AActor::StaticClass();
	bShowInEditorQuickMenu = true;
}

AActor* UEnhancedGameItemActorFactory::SpawnActor(
	UObject* InAsset, ULevel* InLevel, const FTransform& InTransform, const FActorSpawnParameters& InSpawnParams)
{
	if (UEnhancedWorldGameItemDefinition* WorldGameItem = Cast<UEnhancedWorldGameItemDefinition>(InAsset))
	{
		NewActorClass = WorldGameItem->WorldGameItemActor.LoadSynchronous();
	}

	AActor* SpawnedActor = Super::SpawnActor(InAsset, InLevel, InTransform, InSpawnParams);

	if (IEnhancedGameItemsInterface* GameItemsInterface = Cast<IEnhancedGameItemsInterface>(SpawnedActor))
	{
		GameItemsInterface->PostDraggedInViewport(Cast<UEnhancedWorldGameItemDefinition>(InAsset));
	}

	return SpawnedActor;
}

bool UEnhancedGameItemActorFactory::CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg)
{
	if (AssetData.GetClass() == nullptr)
	{
		OutErrorMsg = FText::FromString(TEXT("Asset is not a valid class"));
		UE_LOG(LogTemp, Error, TEXT("OutErrorMsg: %s"), *OutErrorMsg.ToString());
		return false;
	}

	if (UEnhancedWorldGameItemDefinition* WorldItem = Cast<UEnhancedWorldGameItemDefinition>(AssetData.GetAsset()))
	{
		if (WorldItem->WorldGameItemActor.LoadSynchronous() == nullptr)
		{
			OutErrorMsg = FText::FromString(TEXT("World Game Item Actor is not set"));
			UE_LOG(LogTemp, Error, TEXT("OutErrorMsg: %s"), *OutErrorMsg.ToString());
			return false;
		}
	}
	else
	{
		OutErrorMsg = FText::FromString(TEXT("Asset is not a World Game Item Definition"));
		UE_LOG(LogTemp, Error, TEXT("OutErrorMsg: %s"), *OutErrorMsg.ToString());
		return false;
	}
	return true;
}