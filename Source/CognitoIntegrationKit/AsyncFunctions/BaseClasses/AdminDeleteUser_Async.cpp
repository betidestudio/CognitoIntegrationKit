
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AdminDeleteUser_Async.h"

#include "aws/cognito-idp/model/AdminDeleteUserRequest.h"

UAdminDeleteUser_Async* UAdminDeleteUser_Async::AdminDeleteUser_Async(FString UserPoolId, FString Username)
{
    UAdminDeleteUser_Async* Node = NewObject<UAdminDeleteUser_Async>();
    Node->Var_UserPoolId = UserPoolId;
    Node->Var_Username = Username;
    return Node;
}

void UAdminDeleteUser_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AdminDeleteUserRequest AdminDeleteUserRequest;
    AdminDeleteUserRequest.WithUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    AdminDeleteUserRequest.WithUsername(TCHAR_TO_UTF8(*Var_Username));

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminDeleteUserRequest&, const Aws::CognitoIdentityProvider::Model::AdminDeleteUserOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->AdminDeleteUserAsync(AdminDeleteUserRequest, AsyncCallback);
}

void UAdminDeleteUser_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
