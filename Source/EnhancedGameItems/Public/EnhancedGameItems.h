// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"


DECLARE_LOG_CATEGORY_EXTERN(LogEnhancedGameItems, Log, All);

#if PLATFORM_DESKTOP
#define EQUIPMENT_LOG(Verbosity, Format, ...) \
{ \
UE_LOG(LogEnhancedGameItems, Verbosity, Format, ##__VA_ARGS__); \
}
#endif

class FEnhancedGameItemsModule : public IModuleInterface
{
public:
	//~ Begin IModuleInterface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	//~ End IModuleInterface
};
