
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "DeleteIdentityProvider_Async.h"

#include "aws/cognito-idp/model/DeleteIdentityProviderRequest.h"

UDeleteIdentityProvider_Async* UDeleteIdentityProvider_Async::DeleteIdentityProvider_Async(FString ProviderName, FString UserPoolId)
{
    UDeleteIdentityProvider_Async* Node = NewObject<UDeleteIdentityProvider_Async>();
    Node->Var_ProviderName = ProviderName;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UDeleteIdentityProvider_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::DeleteIdentityProviderRequest DeleteIdentityProviderRequest;
    DeleteIdentityProviderRequest.SetProviderName(TCHAR_TO_UTF8(*Var_ProviderName));
    DeleteIdentityProviderRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DeleteIdentityProviderRequest&, const Aws::CognitoIdentityProvider::Model::DeleteIdentityProviderOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->DeleteIdentityProviderAsync(DeleteIdentityProviderRequest, AsyncCallback);
}

void UDeleteIdentityProvider_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
