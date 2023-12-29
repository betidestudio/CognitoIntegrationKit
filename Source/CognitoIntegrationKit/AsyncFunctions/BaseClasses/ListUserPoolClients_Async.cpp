
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "ListUserPoolClients_Async.h"

#include "aws/cognito-idp/model/ListUserPoolClientsRequest.h"

UListUserPoolClients_Async* UListUserPoolClients_Async::ListUserPoolClients_Async(int32 MaxResults, FString NextToken, FString UserPoolId)
{
    UListUserPoolClients_Async* Node = NewObject<UListUserPoolClients_Async>();
    Node->Var_MaxResults = MaxResults;
    Node->Var_NextToken = NextToken;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UListUserPoolClients_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::ListUserPoolClientsRequest ListUserPoolClientsRequest;
    ListUserPoolClientsRequest.SetMaxResults(Var_MaxResults);
    ListUserPoolClientsRequest.SetNextToken(TCHAR_TO_UTF8(*Var_NextToken));
    ListUserPoolClientsRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ListUserPoolClientsRequest&, const Aws::CognitoIdentityProvider::Model::ListUserPoolClientsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                TArray<FUserPoolClientDescription> UserPoolClients;
                for (auto UserPoolClient : outcome.GetResult().GetUserPoolClients())
                {
                    FUserPoolClientDescription UserPoolClientDescription = UserPoolClient;
                }
                OnSuccess.Broadcast(FString(outcome.GetResult().GetNextToken().c_str()), UserPoolClients, FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FString(outcome.GetResult().GetNextToken().c_str()), TArray<FUserPoolClientDescription>(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->ListUserPoolClientsAsync(ListUserPoolClientsRequest, AsyncCallback);
}

void UListUserPoolClients_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FString(), TArray<FUserPoolClientDescription>(), Error);
}
