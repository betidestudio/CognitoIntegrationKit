
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "ListUserPools_Async.h"

#include "aws/cognito-idp/model/ListUserPoolsRequest.h"

UListUserPools_Async* UListUserPools_Async::ListUserPools_Async(int32 MaxResults, FString NextToken)
{
    UListUserPools_Async* Node = NewObject<UListUserPools_Async>();
    Node->Var_MaxResults = MaxResults;
    Node->Var_NextToken = NextToken;
    return Node;
}

void UListUserPools_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::ListUserPoolsRequest ListUserPoolsRequest;
    ListUserPoolsRequest.SetMaxResults(Var_MaxResults);
    ListUserPoolsRequest.SetNextToken(TCHAR_TO_UTF8(*Var_NextToken));

    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ListUserPoolsRequest&, const Aws::CognitoIdentityProvider::Model::ListUserPoolsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                TArray<FUserPoolDescriptionType> UserPools;
                for (auto& UserPool : outcome.GetResult().GetUserPools())
                {
                    FUserPoolDescriptionType UserPoolDescriptionType = UserPool;
                }
                OnSuccess.Broadcast(FString(outcome.GetResult().GetNextToken().c_str()), UserPools, FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FString(), TArray<FUserPoolDescriptionType>(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->ListUserPoolsAsync(ListUserPoolsRequest, AsyncCallback);
}

void UListUserPools_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FString(), TArray<FUserPoolDescriptionType>(), Error);
}
