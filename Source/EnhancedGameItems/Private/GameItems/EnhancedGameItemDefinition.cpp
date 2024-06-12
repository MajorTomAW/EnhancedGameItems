//  Copyright © 2024 MajorT. All rights reserved.


#include "GameItems/EnhancedGameItemDefinition.h"

#include "EnhancedGameItemTypes.h"
#include "Misc/DataValidation.h"

UEnhancedGameItemDefinition::UEnhancedGameItemDefinition(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ItemSerialNumber = FGuid();
	ReleaseState = EEnhancedGameItemReleaseState::Unset;
}

bool UEnhancedGameItemDefinition::IsItemValid() const
{
	if (ReleaseState != EEnhancedGameItemReleaseState::Unset)
	{
		return ItemSerialNumber.IsValid();
	}
	return true;
}

#if WITH_EDITOR
EDataValidationResult UEnhancedGameItemDefinition::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult SuperResult = Super::IsDataValid(Context);

	if (!ItemSerialNumber.IsValid() && ReleaseState != EEnhancedGameItemReleaseState::Unset)
	{
		SuperResult = EDataValidationResult::Invalid;
		FString ReleaseText;
		StaticEnum<EEnhancedGameItemReleaseState>()->FindNameStringByValue(ReleaseText, static_cast<int32>(ReleaseState));
		const FString ErrorMessage = FString::Printf(TEXT("Item %s needs to have a valid serial number with current release state: %s"), *GetName(), *ReleaseText);
		Context.AddError(FText::FromString(ErrorMessage));
	}
	else if (ItemSerialNumber.IsValid() && ReleaseState == EEnhancedGameItemReleaseState::Unset)
	{
		SuperResult = EDataValidationResult::Invalid;
		const FString ErrorMessage = FString::Printf(TEXT("Item %s has a valid serial number but no release state. Please invalidate the serial number if u are not planning to release this item!"), *GetName());
		Context.AddError(FText::FromString(ErrorMessage));
	}

	return SuperResult;
}

void UEnhancedGameItemDefinition::GenerateSerialNumber()
{
	if (!ItemSerialNumber.IsValid())
	{
		ItemSerialNumber = FGuid::NewGuid();
	}
}

void UEnhancedGameItemDefinition::InvalidateSerialNumber()
{
	ItemSerialNumber.Invalidate();
}
#endif

FPrimaryAssetId UEnhancedGameItemDefinition::GetPrimaryAssetId() const
{
	if (ReleaseState == EEnhancedGameItemReleaseState::Released)
	{
		return FPrimaryAssetId("GameItem", *GetNameSafe(this));
	}
	return FPrimaryAssetId("UnreleasedItem", *GetNameSafe(this));
}
