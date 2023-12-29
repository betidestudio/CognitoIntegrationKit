
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "DescribeUserImportJob_Async.h"

#include "aws/cognito-idp/model/DescribeUserImportJobRequest.h"

UDescribeUserImportJob_Async* UDescribeUserImportJob_Async::DescribeUserImportJob_Async(FString JobId, FString UserPoolId)
{
    UDescribeUserImportJob_Async* Node = NewObject<UDescribeUserImportJob_Async>();
    Node->Var_JobId = JobId;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UDescribeUserImportJob_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::DescribeUserImportJobRequest DescribeUserImportJobRequest;
    DescribeUserImportJobRequest.SetJobId(TCHAR_TO_UTF8(*Var_JobId));
    DescribeUserImportJobRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));

    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DescribeUserImportJobRequest&, const Aws::CognitoIdentityProvider::Model::DescribeUserImportJobOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(outcome.GetResult().GetUserImportJob(), FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FUserImportJobType(),Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->DescribeUserImportJobAsync(DescribeUserImportJobRequest, AsyncCallback);
}

void UDescribeUserImportJob_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FUserImportJobType(),Error);
}
