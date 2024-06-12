//  Copyright © 2024 MajorT. All rights reserved.


#include "EnhancedGameItemsActions.h"

#include "EditorSettings/EnhancedGameItemsDeveloperSettings.h"
#include "GameItems/EnhancedGameItemDefinition.h"

#define LOCTEXT_NAMESPACE "FEnhancedGameItemsEditorModule"

FColor GetDefaultItemColor()
{
	const UEnhancedGameItemsDeveloperSettings* DevSettings = GetDefault<UEnhancedGameItemsDeveloperSettings>();
	if (!DevSettings)
	{
		return FColor::FromHex("26601e");
	}

	return DevSettings->DefaultItemStyle.Color.ToFColor(DevSettings->DefaultItemStyle.bSRGB);
}

FEnhancedGameItemsActions::FEnhancedGameItemsActions(const TSharedRef<ISlateStyle>& InStyle)
	: Style(InStyle)
{
}

FText FEnhancedGameItemsActions::GetName() const
{
	return LOCTEXT("EnhancedGameItemsActions", "Game Item Definition");
}

bool FEnhancedGameItemsActions::CanFilter()
{
	return true;
}

UClass* FEnhancedGameItemsActions::GetSupportedClass() const
{
	return UEnhancedGameItemDefinition::StaticClass();
}

FText FEnhancedGameItemsActions::GetAssetDescription(const FAssetData& AssetData) const
{
	if (UEnhancedGameItemDefinition* GameItem = Cast<UEnhancedGameItemDefinition>(AssetData.GetAsset()))
	{
		return GameItem->ItemDescription.IsEmpty() ? LOCTEXT("EnhancedGameItemsActions", "Game Item Definition") : GameItem->ItemDescription;
	}

	return LOCTEXT("EnhancedGameItemsActions", "Game Item Definition");
}

FColor FEnhancedGameItemsActions::GetTypeColor() const
{
	return GetDefaultItemColor();
}

FText FEnhancedGameItemsActions::GetDisplayNameFromAssetData(const FAssetData& AssetData) const
{
	const UEnhancedGameItemsDeveloperSettings* DevSettings = GetDefault<UEnhancedGameItemsDeveloperSettings>();
	TArray<FString> FilterWords;

	if (DevSettings)
	{
		FilterWords.Append(DevSettings->FilterKeywords);
	}
	
	FString Left, Right, Result;
	AssetData.AssetClassPath.ToString().Split(".", &Left, &Right);
	
	for (const FString& FilterWord : FilterWords)
	{
		Right = Right.Replace(*FilterWord, TEXT(""));
	}

	for (int32 i = 0; i < Right.Len(); ++i)
	{
		if (FChar::IsUpper(Right[i]) && i != 0)
		{
			Result.AppendChar(' ');
		}
		Result.AppendChar(Right[i]);
	}
	
	return FText::FromString(Result);
}

#undef LOCTEXT_NAMESPACE