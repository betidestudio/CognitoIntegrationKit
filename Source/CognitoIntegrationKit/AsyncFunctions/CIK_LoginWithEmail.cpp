//Copyright (c) 2023 Betide Studio. All Rights Reserved.


#include "CIK_LoginWithEmail.h"

#include "CIK_Object.h"
#include "aws/cognito-idp/model/InitiateAuthRequest.h"


UCIK_LoginWithEmail* UCIK_LoginWithEmail::LoginWithEmail(UObject* WorldContextObject, const FString& Username,
                                                            const FString& Email, const FString& Password)
{
	UCIK_LoginWithEmail* SignUpWithEmail = NewObject<UCIK_LoginWithEmail>();
	SignUpWithEmail->Var_Username = Username;
	SignUpWithEmail->Var_Password = Password;
	SignUpWithEmail->Var_WorldContextObject = WorldContextObject;
	return SignUpWithEmail;
}

void UCIK_LoginWithEmail::Activate()
{
	FLoginWithEmailFailureResponse Local_FailureResponse;
	Super::Activate();
	TArray<UCIK_Object*> Objects;
	for (TObjectIterator<UCIK_Object> Itr; Itr; ++Itr)
	{
		Objects.Add(*Itr);
	}
	if(Objects[0])
	{
		if(Objects[0]->CognitoClientID.IsEmpty())
		{
			OnFailure.Broadcast(FLoginWithEmailSuccessResponse(), Local_FailureResponse);
			SetReadyToDestroy();
		}
		else
		{
			ContinueSignUp(Objects[0]);
		}
	}
	else
	{
		Local_FailureResponse.ErrorMessage = "No object found";
		OnFailure.Broadcast(FLoginWithEmailSuccessResponse(),Local_FailureResponse);
		SetReadyToDestroy();
	}

}

void UCIK_LoginWithEmail::ContinueSignUp(UCIK_Object* CognitoObject)
{
	Aws::CognitoIdentityProvider::Model::InitiateAuthRequest InitiateAuthRequest;
	InitiateAuthRequest.SetAuthFlow(Aws::CognitoIdentityProvider::Model::AuthFlowType::USER_PASSWORD_AUTH);
	InitiateAuthRequest.SetClientId(TCHAR_TO_UTF8(*CognitoObject->CognitoClientID));
	Aws::Map<Aws::String, Aws::String> AuthParameters;
	AuthParameters["USERNAME"] = TCHAR_TO_UTF8(*Var_Username);
	AuthParameters["PASSWORD"] = TCHAR_TO_UTF8(*Var_Password);
	InitiateAuthRequest.SetAuthParameters(AuthParameters);
	
	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::InitiateAuthRequest&, const Aws::CognitoIdentityProvider::Model::InitiateAuthOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
	{
		AsyncTask(ENamedThreads::GameThread, [outcome, this]()
		{
			if(outcome.IsSuccess())
			{
				FLoginWithEmailSuccessResponse SuccessResponse;
				SuccessResponse.AccessToken = outcome.GetResult().GetAuthenticationResult().GetAccessToken().c_str();
				SuccessResponse.TokenExpiresIn = outcome.GetResult().GetAuthenticationResult().GetExpiresIn();
				SuccessResponse.IdToken = outcome.GetResult().GetAuthenticationResult().GetIdToken().c_str();
				SuccessResponse.RefreshToken = outcome.GetResult().GetAuthenticationResult().GetRefreshToken().c_str();
				OnSuccess.Broadcast(SuccessResponse, FLoginWithEmailFailureResponse());
			}
			else
			{
				FLoginWithEmailFailureResponse FailureResponse;
				FailureResponse.ErrorMessage = outcome.GetError().GetMessage().c_str();
				FailureResponse.bCanUserRetry = outcome.GetError().ShouldRetry();
				FailureResponse.ExceptionName = outcome.GetError().GetExceptionName().c_str();
				FailureResponse.GetMessageW = outcome.GetError().GetMessage().c_str();
				FailureResponse.GetMessageA = outcome.GetError().GetMessage().c_str();
				OnFailure.Broadcast(FLoginWithEmailSuccessResponse(), FailureResponse);
			}
			SetReadyToDestroy();
		});
	};
	CognitoObject->Var_CognitoIPClient->InitiateAuthAsync(InitiateAuthRequest, AsyncCallback);
}
