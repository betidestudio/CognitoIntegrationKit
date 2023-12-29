//Copyright (c) 2023 Betide Studio. All Rights Reserved.


#include "CIK_Object.h"

#include "aws/core/Aws.h"
#include "aws/core/auth/AWSCredentials.h"

void UCIK_Object::SetupObject(UObject* WorldContextObject, const FString& ClientID, FSetupCognito Credentials, FConfig Config, FOnCognitoIdentityKitSetupComplete OnSetupComplete)
{
	Aws::SDKOptions options;
	options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Info;
	Aws::InitAPI(options);
	Aws::Auth::AWSCredentials CognitoCredentials;
	CognitoCredentials.SetAWSAccessKeyId(TCHAR_TO_UTF8(*Credentials.AccessKey));
	CognitoCredentials.SetAWSSecretKey(TCHAR_TO_UTF8(*Credentials.SecretKey));
	CognitoCredentials.SetSessionToken(TCHAR_TO_UTF8(*Credentials.SessionToken));
	if(WorldContextObject)
	{
		CognitoClientID = ClientID;
		Var_ClientConfig = new Aws::Client::ClientConfiguration;
		Var_ClientConfig->region = TCHAR_TO_UTF8(Config.Region.GetValue());
		AsyncTask(ENamedThreads::GameThread, [=]()
		{
			Var_CognitoIPClient = new Aws::CognitoIdentityProvider::CognitoIdentityProviderClient(CognitoCredentials, *Var_ClientConfig);
			OnSetupComplete.ExecuteIfBound(true, this);
		});
	}
	else
	{
		OnSetupComplete.ExecuteIfBound(false, nullptr);
	}
}
