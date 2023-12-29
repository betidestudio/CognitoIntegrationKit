//Copyright (c) 2023 Betide Studio. All Rights Reserved.


#include "CognitoFunctionLibrary.h"

#include "CIK_Object.h"

void UCognitoFunctionLibrary::SetupCognitoIdentityKit(UObject* WorldContextObject, const FString& ClientID, FSetupCognito Credentials, FConfig Config, FOnCognitoIdentityKitSetupComplete OnSetupComplete)
{
	UCIK_Object* CogObject = NewObject<UCIK_Object>(WorldContextObject);

	if(CogObject != nullptr)
	{
		CogObject->SetupObject(WorldContextObject, ClientID, Credentials, Config, OnSetupComplete);
	}
	else
	{
		OnSetupComplete.ExecuteIfBound(false, nullptr);
	}
}
