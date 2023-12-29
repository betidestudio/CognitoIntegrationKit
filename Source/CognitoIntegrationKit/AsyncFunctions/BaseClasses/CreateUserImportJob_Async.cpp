
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "CreateUserImportJob_Async.h"

#include "aws/cognito-idp/model/CreateUserImportJobRequest.h"

UCreateUserImportJob_Async* UCreateUserImportJob_Async::CreateUserImportJob_Async(FString UserPoolId, FString JobName, FString CloudWatchLogsRoleArn)
{
    UCreateUserImportJob_Async* Node = NewObject<UCreateUserImportJob_Async>();
    Node->Var_UserPoolId = UserPoolId;
    Node->Var_JobName = JobName;
    Node->Var_CloudWatchLogsRoleArn = CloudWatchLogsRoleArn;
    return Node;
}

void UCreateUserImportJob_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::CreateUserImportJobRequest CreateUserImportJobRequest;
    CreateUserImportJobRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    CreateUserImportJobRequest.SetJobName(TCHAR_TO_UTF8(*Var_JobName));
    CreateUserImportJobRequest.SetCloudWatchLogsRoleArn(TCHAR_TO_UTF8(*Var_CloudWatchLogsRoleArn));

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::CreateUserImportJobRequest&, const Aws::CognitoIdentityProvider::Model::CreateUserImportJobOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
                OnFailure.Broadcast(FUserImportJobType(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->CreateUserImportJobAsync(CreateUserImportJobRequest, AsyncCallback);
    
}

void UCreateUserImportJob_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FUserImportJobType(), Error);
}
