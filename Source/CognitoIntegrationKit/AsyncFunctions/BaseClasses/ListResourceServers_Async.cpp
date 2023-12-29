
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "ListResourceServers_Async.h"

#include "aws/cognito-idp/model/ListResourceServersRequest.h"

UListResourceServers_Async* UListResourceServers_Async::ListResourceServers_Async(int32 MaxResults, FString NextToken, FString UserPoolId)
{
    UListResourceServers_Async* Node = NewObject<UListResourceServers_Async>();
    Node->Var_MaxResults = MaxResults;
    Node->Var_NextToken = NextToken;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UListResourceServers_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::ListResourceServersRequest ListResourceServersRequest;
    ListResourceServersRequest.SetMaxResults(Var_MaxResults);
    ListResourceServersRequest.SetNextToken(TCHAR_TO_UTF8(*Var_NextToken));
    ListResourceServersRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));

    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ListResourceServersRequest&, const Aws::CognitoIdentityProvider::Model::ListResourceServersOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                TArray<FResourceServerType> ResourceServers;
                for (auto ResourceServer : outcome.GetResult().GetResourceServers())
                {
                    FResourceServerType TempResourceServer = ResourceServer;
                    ResourceServers.Add(TempResourceServer);
                }
                OnSuccess.Broadcast(outcome.GetResult().GetNextToken().c_str(), ResourceServers, FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FString(), TArray<FResourceServerType>(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->ListResourceServersAsync(ListResourceServersRequest, AsyncCallback);
}

void UListResourceServers_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FString(), TArray<FResourceServerType>(), Error);
}
