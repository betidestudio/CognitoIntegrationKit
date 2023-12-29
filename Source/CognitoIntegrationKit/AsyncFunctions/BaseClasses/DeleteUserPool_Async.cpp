
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "DeleteUserPool_Async.h"

#include "aws/cognito-idp/model/DeleteUserPoolRequest.h"

UDeleteUserPool_Async* UDeleteUserPool_Async::DeleteUserPool_Async(FString UserPoolId)
{
    UDeleteUserPool_Async* Node = NewObject<UDeleteUserPool_Async>();
    Node->Var_UserPoolId = UserPoolId;  
    return Node;
}

void UDeleteUserPool_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::DeleteUserPoolRequest DeleteUserPoolRequest;
    DeleteUserPoolRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DeleteUserPoolRequest&, const Aws::CognitoIdentityProvider::Model::DeleteUserPoolOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->DeleteUserPoolAsync(DeleteUserPoolRequest, AsyncCallback);
}

void UDeleteUserPool_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
