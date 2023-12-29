
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "GetGroup_Async.h"

#include "aws/cognito-idp/model/GetGroupRequest.h"

UGetGroup_Async* UGetGroup_Async::GetGroup_Async(FString GroupName, FString UserPoolID)
{
    UGetGroup_Async* Node = NewObject<UGetGroup_Async>();
    Node->Var_GroupName = GroupName;
    Node->Var_UserPoolID = UserPoolID;
    return Node;
}

void UGetGroup_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::GetGroupRequest GetGroupRequest;
    GetGroupRequest.SetGroupName(TCHAR_TO_UTF8(*Var_GroupName));
    GetGroupRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolID));

    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::GetGroupRequest&, const Aws::CognitoIdentityProvider::Model::GetGroupOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->GetGroupAsync(GetGroupRequest, AsyncCallback);
}

void UGetGroup_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FGroupType(), Error);
}
