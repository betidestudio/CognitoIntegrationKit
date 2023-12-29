using System;
using System.Collections.Generic;
using System.IO;
using UnrealBuildTool;

public class AWSSDK : ModuleRules
{
    // list every library you plan to use here
    private List<string> LibraryNames = new List<string>()
    {
        "aws-c-auth",
        "aws-c-cal",
        "aws-c-common",
        "aws-c-compression",
        "aws-c-event-stream",
        "aws-checksums",
        "aws-c-http",
        "aws-c-io",
        "aws-c-mqtt",
        "aws-cpp-sdk-access-management",
        "aws-cpp-sdk-cognito-identity",
        "aws-cpp-sdk-core",
        "aws-cpp-sdk-iam",
        "aws-cpp-sdk-kinesis",
        "aws-crt-cpp",
        "aws-c-s3",
        "aws-c-sdkutils",
        "aws-cpp-sdk-cognito-idp",
        "aws-cpp-sdk-dynamodb",
        "aws-cpp-sdk-gamelift",
        "aws-cpp-sdk-s3",
        "zlib",
    };

    public AWSSDK(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        // add the header files for reference
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Include"));
        bEnableUndefinedIdentifierWarnings = false;
        PublicDefinitions.Add("USE_IMPORT_EXPORT");
        PublicDefinitions.Add("AWS_CRT_CPP_USE_IMPORT_EXPORT");


        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicDefinitions.Add("USE_WINDOWS_DLL_SEMANTICS");
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            string LibraryPath = Path.Combine(ModuleDirectory, "Binaries", Target.Platform.ToString());
            PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "libs2n.a"));
            PublicIncludePathModuleNames.AddRange(new string[] { "Launch" });
            //AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(ModuleDirectory, "AWSSDK_APL.xml"));
        }
        foreach (string libName in LibraryNames)
        {
            string LibraryPath = Path.Combine(ModuleDirectory, "Binaries", Target.Platform.ToString());
            // add a new section for each platform you plan to compile for (only Win64 is included for this example)
            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, libName + ".lib"));
                RuntimeDependencies.Add("$(PluginDir)/Source/ThirdParty/AWSSDK/Binaries/Win64/" + libName + ".dll");
                PublicDelayLoadDLLs.Add(libName + ".dll");
                
                PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "zlib" + ".lib"));
                // Stage the library along with the target, so it can be loaded at runtime.
                RuntimeDependencies.Add("$(PluginDir)/Source/ThirdParty/AWSSDK/Binaries/Win64/" + "zlib1" + ".dll");
                //RuntimeDependencies.Add("$(BinaryOutputDir)/" + libName + ".dll", Path.Combine(LibraryPath, libName + ".dll"));
                PublicDelayLoadDLLs.Add("zlib1" + ".dll");
            }
            else if (Target.Platform == UnrealTargetPlatform.Mac)
            {
                
            }
            else if (Target.Platform == UnrealTargetPlatform.Linux)
            {
                // add linux libraries
            }
            else if (Target.Platform == UnrealTargetPlatform.Android)
            {
                PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "lib" + libName + ".a"));
            }
        }

        PrivateDependencyModuleNames.AddRange(
        new string[] {
                    "CoreUObject",
                    "Engine",
                    "Slate",
                    "SlateCore",   
        });
    }
}