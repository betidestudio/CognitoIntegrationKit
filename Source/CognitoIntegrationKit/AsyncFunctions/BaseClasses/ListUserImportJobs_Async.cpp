
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "ListUserImportJobs_Async.h"

#include "aws/cognito-idp/model/ListUserImportJobsRequest.h"

UListUserImportJobs_Async* UListUserImportJobs_Async::ListUserImportJobs_Async(int32 MaxResults, FString PaginationToken, FString UserPoolId)
{
    UListUserImportJobs_Async* Node = NewObject<UListUserImportJobs_Async>();
    Node->Var_MaxResults = MaxResults;
    Node->Var_PaginationToken = PaginationToken;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UListUserImportJobs_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::ListUserImportJobsRequest ListUserImportJobsRequest;
    ListUserImportJobsRequest.SetMaxResults(Var_MaxResults);
    ListUserImportJobsRequest.SetPaginationToken(TCHAR_TO_UTF8(*Var_PaginationToken));
    ListUserImportJobsRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));

    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ListUserImportJobsRequest&, const Aws::CognitoIdentityProvider::Model::ListUserImportJobsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                TArray<FUserImportJobType> UserImportJobs;
                for (auto UserImportJob : outcome.GetResult().GetUserImportJobs())
                {
                    FUserImportJobType UserImportJobType = UserImportJob;
                }
                OnSuccess.Broadcast(outcome.GetResult().GetPaginationToken().c_str(), UserImportJobs, FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FString(), TArray<FUserImportJobType>(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->ListUserImportJobsAsync(ListUserImportJobsRequest, AsyncCallback);
}

void UListUserImportJobs_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FString(), TArray<FUserImportJobType>(), Error);
}
