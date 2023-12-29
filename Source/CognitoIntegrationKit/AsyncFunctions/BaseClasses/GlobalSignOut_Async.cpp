
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "GlobalSignOut_Async.h"

#include "aws/cognito-idp/model/GlobalSignOutRequest.h"

UGlobalSignOut_Async* UGlobalSignOut_Async::GlobalSignOut_Async(FString AccessToken)
{
    UGlobalSignOut_Async* Node = NewObject<UGlobalSignOut_Async>();
    Node->Var_AccessToken = AccessToken;
    return Node;
}

void UGlobalSignOut_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::GlobalSignOutRequest GlobalSignOutRequest;
    GlobalSignOutRequest.SetAccessToken(TCHAR_TO_UTF8(*Var_AccessToken));

    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::GlobalSignOutRequest&, const Aws::CognitoIdentityProvider::Model::GlobalSignOutOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->GlobalSignOutAsync(GlobalSignOutRequest, AsyncCallback);
}

void UGlobalSignOut_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
