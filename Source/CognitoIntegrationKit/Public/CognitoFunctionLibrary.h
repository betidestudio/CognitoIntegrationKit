//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CIK_Object.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CognitoFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class COGNITOINTEGRATIONKIT_API UCognitoFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "Cognito Identity Kit", meta = (Keywords = "Cognito Identity Kit", DisplayName = "Setup Cognito Identity Kit", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static void SetupCognitoIdentityKit(UObject* WorldContextObject, const FString& ClientID, FSetupCognito Credentials, FConfig Config,FOnCognitoIdentityKitSetupComplete OnSetupComplete);
	
};
