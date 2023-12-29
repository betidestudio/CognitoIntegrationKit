
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AdminRemoveUserFromGroup_Async.h"

#include "aws/cognito-idp/model/AdminRemoveUserFromGroupRequest.h"

UAdminRemoveUserFromGroup_Async* UAdminRemoveUserFromGroup_Async::AdminRemoveUserFromGroup_Async(FString GroupName, FString Username, FString UserPoolId)
{
    UAdminRemoveUserFromGroup_Async* Node = NewObject<UAdminRemoveUserFromGroup_Async>();
    Node->Var_GroupName = GroupName;
    Node->Var_Username = Username;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UAdminRemoveUserFromGroup_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AdminRemoveUserFromGroupRequest AdminRemoveUserFromGroupRequest;
    AdminRemoveUserFromGroupRequest.SetGroupName(TCHAR_TO_UTF8(*Var_GroupName));
    AdminRemoveUserFromGroupRequest.SetUsername(TCHAR_TO_UTF8(*Var_Username));
    AdminRemoveUserFromGroupRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminRemoveUserFromGroupRequest&, const Aws::CognitoIdentityProvider::Model::AdminRemoveUserFromGroupOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->AdminRemoveUserFromGroupAsync(AdminRemoveUserFromGroupRequest, AsyncCallback);
}

void UAdminRemoveUserFromGroup_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
