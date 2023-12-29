
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AdminDisableUser_Async.h"

#include "aws/cognito-idp/model/AdminDisableUserRequest.h"

UAdminDisableUser_Async* UAdminDisableUser_Async::AdminDisableUser_Async(FString UserPoolId, FString Username)
{
    UAdminDisableUser_Async* Node = NewObject<UAdminDisableUser_Async>();
    Node->Var_UserPoolId = UserPoolId;
    Node->Var_Username = Username;
    return Node;
}

void UAdminDisableUser_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AdminDisableUserRequest AdminDisableUserRequest;
    AdminDisableUserRequest.WithUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    AdminDisableUserRequest.WithUsername(TCHAR_TO_UTF8(*Var_Username));

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminDisableUserRequest&, const Aws::CognitoIdentityProvider::Model::AdminDisableUserOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->AdminDisableUserAsync(AdminDisableUserRequest, AsyncCallback);

}

void UAdminDisableUser_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
