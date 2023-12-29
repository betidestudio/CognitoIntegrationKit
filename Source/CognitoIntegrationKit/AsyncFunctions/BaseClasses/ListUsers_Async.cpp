
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "ListUsers_Async.h"

#include "aws/cognito-idp/model/ListUsersRequest.h"

UListUsers_Async* UListUsers_Async::ListUsers_Async(FListUsersRequest Request)
{
    UListUsers_Async* Node = NewObject<UListUsers_Async>();
    Node->Var_Request = Request;
    return Node;
}

void UListUsers_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::ListUsersRequest ListUsersRequest;
    ListUsersRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_Request.UserPoolId));
    ListUsersRequest.SetFilter(TCHAR_TO_UTF8(*Var_Request.Filter));
    ListUsersRequest.SetLimit(Var_Request.Limit);
    ListUsersRequest.SetPaginationToken(TCHAR_TO_UTF8(*Var_Request.PaginationToken));
    for (int i = 0; i < Var_Request.AttributesToGet.Num(); i++)
    {
        ListUsersRequest.AddAttributesToGet(TCHAR_TO_UTF8(*Var_Request.AttributesToGet[i]));
    }
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ListUsersRequest&, const Aws::CognitoIdentityProvider::Model::ListUsersOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                TArray<FUserType> Users;
                for (int i = 0; i < outcome.GetResult().GetUsers().size(); i++)
                {
                    FUserType User = outcome.GetResult().GetUsers()[i];
                    Users.Add(User);
                }
                OnSuccess.Broadcast(FString(outcome.GetResult().GetPaginationToken().c_str()), Users, FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FString(outcome.GetResult().GetPaginationToken().c_str()), TArray<FUserType>(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->ListUsersAsync(ListUsersRequest, AsyncCallback);
}

void UListUsers_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FString(), TArray<FUserType>(), Error);
}
