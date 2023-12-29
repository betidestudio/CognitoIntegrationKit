
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "DescribeUserPoolClient_Async.h"

#include "aws/cognito-idp/model/DescribeUserPoolClientRequest.h"

UDescribeUserPoolClient_Async* UDescribeUserPoolClient_Async::DescribeUserPoolClient_Async(FString ClientId, FString UserPoolId)
{
    UDescribeUserPoolClient_Async* Node = NewObject<UDescribeUserPoolClient_Async>();
    Node->Var_ClientId = ClientId;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UDescribeUserPoolClient_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::DescribeUserPoolClientRequest DescribeUserPoolClientRequest;
    DescribeUserPoolClientRequest.SetClientId(TCHAR_TO_UTF8(*Var_ClientId));
    DescribeUserPoolClientRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DescribeUserPoolClientRequest&, const Aws::CognitoIdentityProvider::Model::DescribeUserPoolClientOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(outcome.GetResult().GetUserPoolClient(), FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FUserPoolClientType(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->DescribeUserPoolClientAsync(DescribeUserPoolClientRequest, AsyncCallback);
}

void UDescribeUserPoolClient_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FUserPoolClientType(), Error);
}
