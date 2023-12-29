
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "ListUsersInGroup_Async.h"

#include "aws/cognito-idp/model/ListUsersInGroupRequest.h"

UListUsersInGroup_Async* UListUsersInGroup_Async::ListUsersInGroup_Async(int32 Limit, FString GroupName, FString UserPoolId, FString NextToken)
{
    UListUsersInGroup_Async* Node = NewObject<UListUsersInGroup_Async>();
    Node->Var_GroupName = GroupName;
    Node->Var_Limit = Limit;
    Node->Var_NextToken = NextToken;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UListUsersInGroup_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::ListUsersInGroupRequest ListUsersInGroupRequest;
    ListUsersInGroupRequest.SetGroupName(TCHAR_TO_UTF8(*Var_GroupName));
    ListUsersInGroupRequest.SetLimit(Var_Limit);
    ListUsersInGroupRequest.SetNextToken(TCHAR_TO_UTF8(*Var_NextToken));
    ListUsersInGroupRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));

    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ListUsersInGroupRequest&, const Aws::CognitoIdentityProvider::Model::ListUsersInGroupOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                TArray<FUserType> Users;
                for (int i = 0; i < outcome.GetResult().GetUsers().size(); i++)
                {
                    FUserType User = outcome.GetResult().GetUsers()[i];
                    Users.Add(User);
                }
                OnSuccess.Broadcast(FString(outcome.GetResult().GetNextToken().c_str()), Users, FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FString(outcome.GetResult().GetNextToken().c_str()), TArray<FUserType>(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->ListUsersInGroupAsync(ListUsersInGroupRequest, AsyncCallback);
}

void UListUsersInGroup_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FString(), TArray<FUserType>(), Error);
}

