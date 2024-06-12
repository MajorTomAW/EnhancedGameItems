//  Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions/AssetTypeActions_DataAsset.h"


class FEnhancedGameItemsActions : public FAssetTypeActions_DataAsset
{
public:
	FEnhancedGameItemsActions(const TSharedRef<ISlateStyle>& InStyle);

	//~ Begin IAssetTypeActions Interface
	virtual FText GetName() const override;
	virtual bool CanFilter() override;
	virtual UClass* GetSupportedClass() const override;
	virtual FText GetAssetDescription(const FAssetData& AssetData) const override;
	virtual FColor GetTypeColor() const override;
	virtual FText GetDisplayNameFromAssetData(const FAssetData& AssetData) const override;
	virtual uint32 GetCategories() override {return FEnhancedGameItemsEditorModule::GetGameItemsAssetsCategory(); }
	//~ End IAssetTypeActions Interface

private:
	TSharedRef<ISlateStyle> Style;
};
