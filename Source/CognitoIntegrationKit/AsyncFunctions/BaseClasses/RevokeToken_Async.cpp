
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "RevokeToken_Async.h"

#include "aws/cognito-idp/model/RevokeTokenRequest.h"

URevokeToken_Async* URevokeToken_Async::RevokeToken_Async(FString ClientId, FString ClientSecret, FString Token)
{
    URevokeToken_Async* Node = NewObject<URevokeToken_Async>();
    Node->Var_ClientId = ClientId;
    Node->Var_ClientSecret = ClientSecret;
    Node->Var_Token = Token;
    return Node;
}

void URevokeToken_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::RevokeTokenRequest Request;
    Request.SetClientId(TCHAR_TO_UTF8(*Var_ClientId));
    Request.SetClientSecret(TCHAR_TO_UTF8(*Var_ClientSecret));
    Request.SetToken(TCHAR_TO_UTF8(*Var_Token));
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::RevokeTokenRequest&, const Aws::CognitoIdentityProvider::Model::RevokeTokenOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->RevokeTokenAsync(Request, AsyncCallback);
}

void URevokeToken_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
