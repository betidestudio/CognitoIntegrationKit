
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "ListIdentityProviders_Async.h"

#include "aws/cognito-idp/model/ListIdentityProvidersRequest.h"

UListIdentityProviders_Async* UListIdentityProviders_Async::ListIdentityProviders_Async(int32 MaxResults, FString NextToken, FString UserPoolId )
{
    UListIdentityProviders_Async* Node = NewObject<UListIdentityProviders_Async>();
    Node->Var_MaxResults = MaxResults;
    Node->Var_NextToken = NextToken;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UListIdentityProviders_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::ListIdentityProvidersRequest ListIdentityProvidersRequest;
    ListIdentityProvidersRequest.SetMaxResults(Var_MaxResults);
    ListIdentityProvidersRequest.SetNextToken(TCHAR_TO_UTF8(*Var_NextToken));
    ListIdentityProvidersRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));

    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ListIdentityProvidersRequest&, const Aws::CognitoIdentityProvider::Model::ListIdentityProvidersOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                TArray<FProviderDescription> Providers;
                for (auto& Provider : outcome.GetResult().GetProviders())
                {
                    FProviderDescription Temp = Provider;
                }
                OnSuccess.Broadcast(FString(outcome.GetResult().GetNextToken().c_str()), Providers, FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FString(), TArray<FProviderDescription>(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->ListIdentityProvidersAsync(ListIdentityProvidersRequest, AsyncCallback);
}

void UListIdentityProviders_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FString(), TArray<FProviderDescription>(), Error);
}
