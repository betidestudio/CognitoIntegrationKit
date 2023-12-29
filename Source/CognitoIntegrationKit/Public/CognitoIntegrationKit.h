//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Core/Public/HAL/PlatformProcess.h"
#include "Runtime/Core/Public/HAL/FileManager.h"
#include "Modules/ModuleManager.h"

class FCognitoIntegrationKitModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	void* DynamicLibExampleHandle;
	TArray<void*> DynamicLibHandles;

};
