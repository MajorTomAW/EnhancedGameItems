//  Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ThumbnailRendering/ClassThumbnailRenderer.h"
#include "EnhancedGameItemsThumbnailRenderer.generated.h"

/**
 * 
 */
UCLASS()
class ENHANCEDGAMEITEMSEDITOR_API UEnhancedGameItemsThumbnailRenderer : public UClassThumbnailRenderer
{
	GENERATED_BODY()

public:
	UEnhancedGameItemsThumbnailRenderer(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~ Begin UThumbnailRenderer Interface
	virtual void GetThumbnailSize(UObject* Object, float Zoom, uint32& OutWidth, uint32& OutHeight) const override;
	virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget* Viewport, FCanvas* Canvas, bool bAdditionalViewFamily) override;
	virtual bool CanVisualizeAsset(UObject* Object) override;
	//~ End UThumbnailRenderer Interface

	static UTexture2D* GetIconFromDataAsset(UDataAsset* Class);
};
