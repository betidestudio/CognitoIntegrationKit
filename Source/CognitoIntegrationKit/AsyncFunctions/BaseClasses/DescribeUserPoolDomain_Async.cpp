
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "DescribeUserPoolDomain_Async.h"

#include "aws/cognito-idp/model/DescribeUserPoolDomainRequest.h"

UDescribeUserPoolDomain_Async* UDescribeUserPoolDomain_Async::DescribeUserPoolDomain_Async(FString Domain)
{
    UDescribeUserPoolDomain_Async* Node = NewObject<UDescribeUserPoolDomain_Async>();
    Node->Var_Domain = Domain;
    return Node;
}

void UDescribeUserPoolDomain_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::DescribeUserPoolDomainRequest DescribeUserPoolDomainRequest;
    DescribeUserPoolDomainRequest.SetDomain(TCHAR_TO_UTF8(*Var_Domain));
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DescribeUserPoolDomainRequest&, const Aws::CognitoIdentityProvider::Model::DescribeUserPoolDomainOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(outcome.GetResult().GetDomainDescription(), FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FDomainDescriptionType(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->DescribeUserPoolDomainAsync(DescribeUserPoolDomainRequest, AsyncCallback);    
}

void UDescribeUserPoolDomain_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FDomainDescriptionType(), Error);
}
