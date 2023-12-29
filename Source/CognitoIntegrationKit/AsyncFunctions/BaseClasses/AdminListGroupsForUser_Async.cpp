
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AdminListGroupsForUser_Async.h"

#include "aws/cognito-idp/model/AdminListGroupsForUserRequest.h"

UAdminListGroupsForUser_Async* UAdminListGroupsForUser_Async::AdminListGroupsForUser_Async()
{
    UAdminListGroupsForUser_Async* Node = NewObject<UAdminListGroupsForUser_Async>();
    return Node;
}

void UAdminListGroupsForUser_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AdminListGroupsForUserRequest AdminListGroupsForUserRequest;
    AdminListGroupsForUserRequest.SetLimit(Var_Limit);
    AdminListGroupsForUserRequest.SetNextToken(TCHAR_TO_UTF8(*Var_NextToken));
    AdminListGroupsForUserRequest.SetUsername(TCHAR_TO_UTF8(*Var_Username));
    AdminListGroupsForUserRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminListGroupsForUserRequest&, const Aws::CognitoIdentityProvider::Model::AdminListGroupsForUserOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                TArray<FGroupType> Groups;
                for (auto& Item : outcome.GetResult().GetGroups())
                {
                    FGroupType Group(Item);
                    Groups.Add(Group);
                }
                OnSuccess.Broadcast(Groups, FString(outcome.GetResult().GetNextToken().c_str()), FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(TArray<FGroupType>(),"", Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->AdminListGroupsForUserAsync(AdminListGroupsForUserRequest, AsyncCallback);
}

void UAdminListGroupsForUser_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(TArray<FGroupType>(),"", Error);
}
