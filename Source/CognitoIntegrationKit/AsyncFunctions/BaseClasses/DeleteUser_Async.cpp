
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "DeleteUser_Async.h"

#include "aws/cognito-idp/model/DeleteUserRequest.h"

UDeleteUser_Async* UDeleteUser_Async::DeleteUser_Async(FString AccessToken)
{
    UDeleteUser_Async* Node = NewObject<UDeleteUser_Async>();
    Node->Var_AccessToken = AccessToken;
    return Node;
}

void UDeleteUser_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::DeleteUserRequest DeleteUserRequest;
    DeleteUserRequest.SetAccessToken(TCHAR_TO_UTF8(*Var_AccessToken));

    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DeleteUserRequest&, const Aws::CognitoIdentityProvider::Model::DeleteUserOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->DeleteUserAsync(DeleteUserRequest, AsyncCallback);
}

void UDeleteUser_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
