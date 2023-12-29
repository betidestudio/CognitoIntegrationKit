//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "CognitoIntegrationKit.h"
#include "aws/core/Aws.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FCognitoIntegrationKitModule"

void FCognitoIntegrationKitModule::StartupModule()
{
#if PLATFORM_WINDOWS
	if(const TSharedPtr<IPlugin> PluginPtr = IPluginManager::Get().FindPlugin("CognitoIntegrationKit"))
	{
		const FString PluginDir = PluginPtr->GetBaseDir();
		const FString BinDir =  FPaths::ConvertRelativePathToFull(FPaths::Combine(PluginDir, TEXT("Source"), TEXT("ThirdParty"), TEXT("AWSSDK"), TEXT("Binaries"), TEXT("Win64")));
		FPlatformProcess::PushDllDirectory(*BinDir);
		TArray<FString> LibFiles;
		IFileManager::Get().FindFiles(LibFiles, *(BinDir / TEXT("*.dll")), true, false);
		for (auto Element : LibFiles)
		{
			const FString FinalPath = FPaths::Combine(BinDir, Element);
			DynamicLibHandles.Add(FPlatformProcess::GetDllHandle(*FinalPath));
		}
		FPlatformProcess::PopDllDirectory(*BinDir);
	}
#endif
}

void FCognitoIntegrationKitModule::ShutdownModule()
{
	Aws::SDKOptions options;
	options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Off;
	Aws::ShutdownAPI(options);
#if PLATFORM_WINDOWS
	for (void* Handle : DynamicLibHandles)
	{
		if (Handle != nullptr)
		{
			FPlatformProcess::FreeDllHandle(Handle);
			Handle = nullptr;
		}
	}
#endif
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCognitoIntegrationKitModule, CognitoIntegrationKit)