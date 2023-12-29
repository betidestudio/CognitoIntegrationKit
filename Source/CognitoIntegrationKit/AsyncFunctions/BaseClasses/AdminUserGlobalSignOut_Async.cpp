
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AdminUserGlobalSignOut_Async.h"

#include "aws/cognito-idp/model/AdminUserGlobalSignOutRequest.h"

UAdminUserGlobalSignOut_Async* UAdminUserGlobalSignOut_Async::AdminUserGlobalSignOut_Async(FString UserPoolId, FString Username)
{
    UAdminUserGlobalSignOut_Async* Node = NewObject<UAdminUserGlobalSignOut_Async>();
    Node->Var_UserPoolId = UserPoolId;
    Node->Var_Username = Username;
    return Node;
}

void UAdminUserGlobalSignOut_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AdminUserGlobalSignOutRequest AdminUserGlobalSignOutRequest;
    AdminUserGlobalSignOutRequest.WithUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    AdminUserGlobalSignOutRequest.WithUsername(TCHAR_TO_UTF8(*Var_Username));

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminUserGlobalSignOutRequest&, const Aws::CognitoIdentityProvider::Model::AdminUserGlobalSignOutOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->AdminUserGlobalSignOutAsync(AdminUserGlobalSignOutRequest, AsyncCallback);
}

void UAdminUserGlobalSignOut_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
