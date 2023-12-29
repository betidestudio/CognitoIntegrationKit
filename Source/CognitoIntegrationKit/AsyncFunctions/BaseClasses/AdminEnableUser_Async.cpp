
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AdminEnableUser_Async.h"

#include "aws/cognito-idp/model/AdminEnableUserRequest.h"

UAdminEnableUser_Async* UAdminEnableUser_Async::AdminEnableUser_Async(FString Username, FString UserPoolId)
{
    UAdminEnableUser_Async* Node = NewObject<UAdminEnableUser_Async>();
    Node->Var_Username = Username;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UAdminEnableUser_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AdminEnableUserRequest AdminEnableUserRequest;
    AdminEnableUserRequest.WithUsername(TCHAR_TO_UTF8(*Var_Username));
    AdminEnableUserRequest.WithUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminEnableUserRequest&, const Aws::CognitoIdentityProvider::Model::AdminEnableUserOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->AdminEnableUserAsync(AdminEnableUserRequest, AsyncCallback);
}

void UAdminEnableUser_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
