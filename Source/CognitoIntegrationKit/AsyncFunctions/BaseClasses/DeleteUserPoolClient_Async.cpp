
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "DeleteUserPoolClient_Async.h"

#include "aws/cognito-idp/model/DeleteUserPoolClientRequest.h"

UDeleteUserPoolClient_Async* UDeleteUserPoolClient_Async::DeleteUserPoolClient_Async(FString ClientId, FString UserPoolId)
{
    UDeleteUserPoolClient_Async* Node = NewObject<UDeleteUserPoolClient_Async>();
    Node->Var_ClientId = ClientId;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UDeleteUserPoolClient_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::DeleteUserPoolClientRequest DeleteUserPoolClientRequest;
    DeleteUserPoolClientRequest.SetClientId(TCHAR_TO_UTF8(*Var_ClientId));
    DeleteUserPoolClientRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DeleteUserPoolClientRequest&, const Aws::CognitoIdentityProvider::Model::DeleteUserPoolClientOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->DeleteUserPoolClientAsync(DeleteUserPoolClientRequest, AsyncCallback);
}

void UDeleteUserPoolClient_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
