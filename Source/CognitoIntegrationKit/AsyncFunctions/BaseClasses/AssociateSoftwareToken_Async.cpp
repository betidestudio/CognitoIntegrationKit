
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AssociateSoftwareToken_Async.h"

#include "aws/cognito-idp/model/AssociateSoftwareTokenRequest.h"

UAssociateSoftwareToken_Async* UAssociateSoftwareToken_Async::AssociateSoftwareToken_Async()
{
    UAssociateSoftwareToken_Async* Node = NewObject<UAssociateSoftwareToken_Async>();
    return Node;
}

void UAssociateSoftwareToken_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AssociateSoftwareTokenRequest AssociateSoftwareTokenRequest;
    AssociateSoftwareTokenRequest.SetAccessToken(TCHAR_TO_UTF8(*Var_AccessToken));
    AssociateSoftwareTokenRequest.SetSession(TCHAR_TO_UTF8(*Var_Session));
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AssociateSoftwareTokenRequest&, const Aws::CognitoIdentityProvider::Model::AssociateSoftwareTokenOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(FString(outcome.GetResult().GetSecretCode().c_str()), FString(outcome.GetResult().GetRequestId().c_str()),FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FString(), FString(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->AssociateSoftwareTokenAsync(AssociateSoftwareTokenRequest, AsyncCallback);
}

void UAssociateSoftwareToken_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FString(), FString(), Error);
}
