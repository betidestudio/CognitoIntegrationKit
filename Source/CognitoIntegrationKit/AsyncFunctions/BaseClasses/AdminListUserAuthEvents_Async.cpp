
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AdminListUserAuthEvents_Async.h"

#include "aws/cognito-idp/model/AdminListUserAuthEventsRequest.h"

UAdminListUserAuthEvents_Async* UAdminListUserAuthEvents_Async::AdminListUserAuthEvents_Async(int32 MaxResults, FString NextToken, FString Username, FString UserPoolId)
{
    UAdminListUserAuthEvents_Async* Node = NewObject<UAdminListUserAuthEvents_Async>();
    Node->Var_MaxResults = MaxResults;
    Node->Var_NextToken = NextToken;
    Node->Var_Username = Username;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UAdminListUserAuthEvents_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AdminListUserAuthEventsRequest AdminListUserAuthEventsRequest;
    AdminListUserAuthEventsRequest.SetMaxResults(Var_MaxResults);
    AdminListUserAuthEventsRequest.SetNextToken(TCHAR_TO_UTF8(*Var_NextToken));
    AdminListUserAuthEventsRequest.SetUsername(TCHAR_TO_UTF8(*Var_Username));
    AdminListUserAuthEventsRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminListUserAuthEventsRequest&, const Aws::CognitoIdentityProvider::Model::AdminListUserAuthEventsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                TArray<FAuthEventType> AuthEvents;
                for (auto& Item : outcome.GetResult().GetAuthEvents())
                {
                    FAuthEventType AuthEvent(Item);
                    AuthEvents.Add(AuthEvent);
                }
                OnSuccess.Broadcast(AuthEvents, FString(outcome.GetResult().GetNextToken().c_str()), FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(TArray<FAuthEventType>(), "", Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->AdminListUserAuthEventsAsync(AdminListUserAuthEventsRequest, AsyncCallback);
}

void UAdminListUserAuthEvents_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(TArray<FAuthEventType>(), "", Error);
}
