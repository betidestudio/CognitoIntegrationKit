
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "CreateGroup_Async.h"

#include "aws/cognito-idp/model/CreateGroupRequest.h"

UCreateGroup_Async* UCreateGroup_Async::CreateGroup_Async(FString Description, FString GroupName, int32 Precedence, FString RoleArn, FString UserPoolId)
{
    UCreateGroup_Async* Node = NewObject<UCreateGroup_Async>();
    Node->Var_Description = Description;
    Node->Var_GroupName = GroupName;
    Node->Var_Precedence = Precedence;
    Node->Var_RoleArn = RoleArn;
    return Node;
}

void UCreateGroup_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::CreateGroupRequest CreateGroupRequest;
    CreateGroupRequest.SetDescription(TCHAR_TO_UTF8(*Var_Description));
    CreateGroupRequest.SetGroupName(TCHAR_TO_UTF8(*Var_GroupName));
    CreateGroupRequest.SetPrecedence(Var_Precedence);
    CreateGroupRequest.SetRoleArn(TCHAR_TO_UTF8(*Var_RoleArn));
    CreateGroupRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::CreateGroupRequest&, const Aws::CognitoIdentityProvider::Model::CreateGroupOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(outcome.GetResult().GetGroup(), FCognitoError());
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
    CognitoObject->Var_CognitoIPClient->CreateGroupAsync(CreateGroupRequest, AsyncCallback);
}

void UCreateGroup_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FGroupType(), Error);
}
