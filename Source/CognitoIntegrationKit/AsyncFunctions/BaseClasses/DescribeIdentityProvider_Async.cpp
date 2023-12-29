
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "DescribeIdentityProvider_Async.h"

#include "aws/cognito-identity/model/DescribeIdentityRequest.h"
#include "aws/cognito-idp/model/DescribeIdentityProviderRequest.h"

UDescribeIdentityProvider_Async* UDescribeIdentityProvider_Async::DescribeIdentityProvider_Async(FString ProviderName, FString UserPoolId)
{
    UDescribeIdentityProvider_Async* Node = NewObject<UDescribeIdentityProvider_Async>();
    Node->Var_ProviderName = ProviderName;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UDescribeIdentityProvider_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::DescribeIdentityProviderRequest DescribeIdentityProviderRequest;
    DescribeIdentityProviderRequest.SetProviderName(TCHAR_TO_UTF8(*Var_ProviderName));
    DescribeIdentityProviderRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DescribeIdentityProviderRequest&, const Aws::CognitoIdentityProvider::Model::DescribeIdentityProviderOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                FIdentityProviderType IdentityProvider(outcome.GetResult().GetIdentityProvider());
                OnSuccess.Broadcast(IdentityProvider, FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FIdentityProviderType(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->DescribeIdentityProviderAsync(DescribeIdentityProviderRequest, AsyncCallback);
        
}

void UDescribeIdentityProvider_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FIdentityProviderType(), Error);
}
