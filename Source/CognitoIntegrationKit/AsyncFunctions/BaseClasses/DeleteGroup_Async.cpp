
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "DeleteGroup_Async.h"

#include "aws/cognito-idp/model/DeleteGroupRequest.h"

UDeleteGroup_Async* UDeleteGroup_Async::DeleteGroup_Async(FString GroupName, FString UserPoolId)
{
    UDeleteGroup_Async* Node = NewObject<UDeleteGroup_Async>();
    Node->Var_GroupName = GroupName;
    Node->UserPoolId = UserPoolId;
    return Node;
}

void UDeleteGroup_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::DeleteGroupRequest DeleteGroupRequest;
    DeleteGroupRequest.SetGroupName(TCHAR_TO_UTF8(*Var_GroupName));
    DeleteGroupRequest.SetUserPoolId(TCHAR_TO_UTF8(*UserPoolId));
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DeleteGroupRequest&, const Aws::CognitoIdentityProvider::Model::DeleteGroupOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->DeleteGroupAsync(DeleteGroupRequest, AsyncCallback);
}

void UDeleteGroup_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
