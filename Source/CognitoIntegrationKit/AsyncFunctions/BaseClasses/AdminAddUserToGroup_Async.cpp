
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AdminAddUserToGroup_Async.h"

#include "aws/cognito-idp/model/AdminAddUserToGroupRequest.h"

UAdminAddUserToGroup_Async* UAdminAddUserToGroup_Async::AdminAddUserToGroup_Async(FString GroupName, FString Username, FString UserPoolId)
{
    UAdminAddUserToGroup_Async* Node = NewObject<UAdminAddUserToGroup_Async>();
    Node->Var_GroupName = GroupName;
    Node->Var_Username = Username;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UAdminAddUserToGroup_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AdminAddUserToGroupRequest AdminAddUserToGroupRequest;
    AdminAddUserToGroupRequest.SetGroupName(TCHAR_TO_UTF8(*Var_GroupName));
    AdminAddUserToGroupRequest.SetUsername(TCHAR_TO_UTF8(*Var_Username));
    AdminAddUserToGroupRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminAddUserToGroupRequest&, const Aws::CognitoIdentityProvider::Model::AdminAddUserToGroupOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if(outcome.IsSuccess())
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
    CognitoObject->Var_CognitoIPClient->AdminAddUserToGroupAsync(AdminAddUserToGroupRequest, AsyncCallback);
}

void UAdminAddUserToGroup_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
