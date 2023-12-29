
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "StopUserImportJob_Async.h"

#include "aws/cognito-idp/model/StopUserImportJobRequest.h"

UStopUserImportJob_Async* UStopUserImportJob_Async::StopUserImportJob_Async(FString JobID, FString UserPoolID)
{
    UStopUserImportJob_Async* Node = NewObject<UStopUserImportJob_Async>();
    Node->Var_JobID = JobID;
    Node->Var_UserPoolID = UserPoolID;
    return Node;
}

void UStopUserImportJob_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::StopUserImportJobRequest StopUserImportJobRequest;
    StopUserImportJobRequest.SetJobId(TCHAR_TO_UTF8(*Var_JobID));
    StopUserImportJobRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolID));

    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::StopUserImportJobRequest&, const Aws::CognitoIdentityProvider::Model::StopUserImportJobOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->StopUserImportJobAsync(StopUserImportJobRequest, AsyncCallback);
}

void UStopUserImportJob_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FUserImportJobType(), Error);
}
