
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "UpdateGroup_Async.h"

#include "aws/cognito-idp/model/UpdateGroupRequest.h"

UUpdateGroup_Async* UUpdateGroup_Async::UpdateGroup_Async(FUpdateGroupReq Request)
{
    UUpdateGroup_Async* Node = NewObject<UUpdateGroup_Async>();
    Node->Var_UpdateGroupReq = Request;
    return Node;
}

void UUpdateGroup_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::UpdateGroupRequest UpdateGroupRequest;
    UpdateGroupRequest.WithGroupName(TCHAR_TO_UTF8(*Var_UpdateGroupReq.GroupName));
    UpdateGroupRequest.WithUserPoolId(TCHAR_TO_UTF8(*Var_UpdateGroupReq.UserPoolId));
    UpdateGroupRequest.WithDescription(TCHAR_TO_UTF8(*Var_UpdateGroupReq.Description));
    UpdateGroupRequest.WithRoleArn(TCHAR_TO_UTF8(*Var_UpdateGroupReq.RoleArn));
    UpdateGroupRequest.WithPrecedence(Var_UpdateGroupReq.Precedence);
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::UpdateGroupRequest&, const Aws::CognitoIdentityProvider::Model::UpdateGroupOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(FGroupType(outcome.GetResult().GetGroup()), FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FGroupType(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->UpdateGroupAsync(UpdateGroupRequest, AsyncCallback);
    
}

void UUpdateGroup_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FGroupType(), Error);
}
