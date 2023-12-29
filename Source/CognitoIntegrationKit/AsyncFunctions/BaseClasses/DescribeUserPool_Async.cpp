
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "DescribeUserPool_Async.h"

#include "aws/cognito-idp/model/DescribeUserPoolRequest.h"

UDescribeUserPool_Async* UDescribeUserPool_Async::DescribeUserPool_Async(FString UserPoolId)
{
    UDescribeUserPool_Async* Node = NewObject<UDescribeUserPool_Async>();
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UDescribeUserPool_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::DescribeUserPoolRequest DescribeUserPoolRequest;
    DescribeUserPoolRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DescribeUserPoolRequest&, const Aws::CognitoIdentityProvider::Model::DescribeUserPoolOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(FUserPoolType(outcome.GetResult().GetUserPool()), FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FUserPoolType(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->DescribeUserPoolAsync(DescribeUserPoolRequest, AsyncCallback);
}

void UDescribeUserPool_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FUserPoolType(), Error);
}
