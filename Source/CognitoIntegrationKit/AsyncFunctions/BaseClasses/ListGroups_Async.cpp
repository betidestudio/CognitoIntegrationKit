
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "ListGroups_Async.h"

#include "aws/cognito-idp/model/ListGroupsRequest.h"

UListGroups_Async* UListGroups_Async::ListGroups_Async(int32 Limit, FString NextToken, FString UserPoolId)
{
    UListGroups_Async* Node = NewObject<UListGroups_Async>();
    Node->Var_Limit = Limit;
    Node->Var_NextToken = NextToken;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UListGroups_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::ListGroupsRequest ListGroupsRequest;
    ListGroupsRequest.SetLimit(Var_Limit);
    ListGroupsRequest.SetNextToken(TCHAR_TO_UTF8(*Var_NextToken));
    ListGroupsRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));

    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ListGroupsRequest&, const Aws::CognitoIdentityProvider::Model::ListGroupsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                TArray<FGroupType> Groups;
                for (auto& Group : outcome.GetResult().GetGroups())
                {
                    FGroupType GroupType = Group;
                }
                OnSuccess.Broadcast(FString(outcome.GetResult().GetNextToken().c_str()), Groups, FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FString(), TArray<FGroupType>(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->ListGroupsAsync(ListGroupsRequest, AsyncCallback);
    
}

void UListGroups_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FString(), TArray<FGroupType>(), Error);
}
