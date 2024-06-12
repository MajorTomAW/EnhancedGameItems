//  Copyright © 2024 MajorT. All rights reserved.


#include "EnhancedGameItemsThumbnailRenderer.h"

#include "CanvasItem.h"
#include "CanvasTypes.h"
#include "ImageUtils.h"
#include "EditorSettings/EnhancedGameItemsDeveloperSettings.h"
#include "GameItems/EnhancedGameItemDefinition.h"

UEnhancedGameItemsThumbnailRenderer::UEnhancedGameItemsThumbnailRenderer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UEnhancedGameItemsThumbnailRenderer::GetThumbnailSize(UObject* Object, float Zoom, uint32& OutWidth,uint32& OutHeight) const
{
	if (const UEnhancedGameItemDefinition* GameItem = Cast<UEnhancedGameItemDefinition>(Object))
	{
		if (const UTexture2D* Icon = GameItem->ItemIcon.LoadSynchronous())
		{
			OutWidth = FMath::TruncToInt(Zoom * Icon->GetSurfaceWidth());
			OutHeight = FMath::TruncToInt(Zoom * Icon->GetSurfaceHeight());
		}
	}
	Super::GetThumbnailSize(Object, Zoom, OutWidth, OutHeight);
}

void UEnhancedGameItemsThumbnailRenderer::Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height,
	FRenderTarget* Viewport, FCanvas* Canvas, bool bAdditionalViewFamily)
{
	if (const UEnhancedGameItemDefinition* GameItem = Cast<UEnhancedGameItemDefinition>(Object))
	{
		if (UTexture2D* Icon = GameItem->ItemIcon.LoadSynchronous())
		{
			const bool bUseTranslucentBlend = Icon && Icon->HasAlphaChannel() && ((Icon->LODGroup == TEXTUREGROUP_UI) || (Icon->LODGroup == TEXTUREGROUP_Pixels2D));
			TRefCountPtr<FBatchedElementParameters> BatchedElementParameters;
			if (bUseTranslucentBlend)
			{
				// If using alpha, draw a checkerboard underneath first.
				const int32 CheckerDensity = 8;
				auto* Checker = FImageUtils::CreateCheckerboardTexture(FColor::FromHex("808080"), FColor::FromHex("404040"), 8);
				Canvas->DrawTile(
					0.0f, 0.0f, Width, Height,
					0.0f, 0.0f, CheckerDensity, CheckerDensity,
					FLinearColor::White, Checker->GetResource());
			}
			FCanvasTileItem CanvasTile(FVector2D(X, Y), Icon->GetResource(), FVector2D(Width, Height), FLinearColor::White);
			CanvasTile.BlendMode = bUseTranslucentBlend ? SE_BLEND_Translucent : SE_BLEND_Opaque;
			CanvasTile.BatchedElementParameters = BatchedElementParameters;
			CanvasTile.Draw(Canvas);
			if (Icon && Icon->IsCurrentlyVirtualTextured())
			{
				auto VTChars = TEXT("VT");
				int32 VTWidth = 0;
				int32 VTHeight = 0;
				StringSize(GEngine->GetLargeFont(), VTWidth, VTHeight, VTChars);
				float PaddingX = Width / 128.0f;
				float PaddingY = Height / 128.0f;
				float ScaleX = Width / 64.0f;
				float ScaleY = Height / 64.0f;
				FCanvasTextItem TextItem(FVector2D(Width - PaddingX - VTWidth * ScaleX, Height - PaddingY - VTHeight * ScaleY), FText::FromString(VTChars), GEngine->GetLargeFont(), FLinearColor::White);
				TextItem.EnableShadow(FLinearColor::Black);
				TextItem.Scale = FVector2D(ScaleX, ScaleY);
				TextItem.Draw(Canvas);
			}
			return;
		}
		// If we don't have an icon, draw a placeholder which is the default data asset thumbnail.
		UObject* Loaded = LoadObject<UObject>(nullptr, TEXT("/EnhancedGameItems/Icons/DataAsset_64.DataAsset_64"));
		UTexture2D* DefaultIcon = Cast<UTexture2D>(Loaded);

		FColor DefaultColor = FColor::FromHex("1a1a1a");

		if (const UEnhancedGameItemsDeveloperSettings* DevSettings = GetMutableDefault<UEnhancedGameItemsDeveloperSettings>())
		{
			DefaultColor = DevSettings->DefaultItemStyle.DefaultBackgroundColor.ToFColor(DevSettings->DefaultItemStyle.bDefaultBackgroundSRGB);
		}

		UTexture2D* Checker = FImageUtils::CreateCheckerboardTexture(DefaultColor, DefaultColor, 1);
		constexpr float SizeMultiplier = 0.9f;
		const float Size = Height * SizeMultiplier;
		const float Padding = (Height - (Height * SizeMultiplier)) / 2.f;
		
		Canvas->DrawTile(0.f, 0.f, Width, Height, 0.f, 0.f, 1.f, 1.f, FLinearColor::White, Checker->GetResource());
		Canvas->DrawTile(Padding, Padding, Size, Size, 0.f, 0.f, 1.f, 1.f, FLinearColor::White, DefaultIcon->GetResource());
		return;
	}
	
	Super::Draw(Object, X, Y, Width, Height, Viewport, Canvas, bAdditionalViewFamily);
}

bool UEnhancedGameItemsThumbnailRenderer::CanVisualizeAsset(UObject* Object)
{
	if (Object->IsA(UEnhancedGameItemDefinition::StaticClass()))
	{
		return true;
	}

	return Super::CanVisualizeAsset(Object);
}

UTexture2D* UEnhancedGameItemsThumbnailRenderer::GetIconFromDataAsset(UDataAsset* Class)
{
	if (const UEnhancedGameItemDefinition* GameItem = Cast<UEnhancedGameItemDefinition>(Class))
	{
		return GameItem->ItemIcon.LoadSynchronous();
	}
	return nullptr;
}
