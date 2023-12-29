
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "StartUserImportJob_Async.h"

#include "aws/cognito-idp/model/StartUserImportJobRequest.h"

UStartUserImportJob_Async* UStartUserImportJob_Async::StartUserImportJob_Async(FString JobID, FString UserPoolID)
{
    UStartUserImportJob_Async* Node = NewObject<UStartUserImportJob_Async>();
    Node->Var_JobID = JobID;
    Node->Var_UserPoolID = UserPoolID;
    return Node;
}

void UStartUserImportJob_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::StartUserImportJobRequest StartUserImportJobRequest;
    StartUserImportJobRequest.SetJobId(TCHAR_TO_UTF8(*Var_JobID));
    StartUserImportJobRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolID));

    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::StartUserImportJobRequest&, const Aws::CognitoIdentityProvider::Model::StartUserImportJobOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(FUserImportJobType(outcome.GetResult().GetUserImportJob()), FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FUserImportJobType(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->StartUserImportJobAsync(StartUserImportJobRequest, AsyncCallback);
}

void UStartUserImportJob_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FUserImportJobType(), Error);
}
