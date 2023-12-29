
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "ChangePassword_Async.h"

#include "aws/cognito-idp/model/ChangePasswordRequest.h"

UChangePassword_Async* UChangePassword_Async::ChangePassword_Async(FString AccessToken, FString PreviousPassword, FString ProposedPassword)
{
    UChangePassword_Async* Node = NewObject<UChangePassword_Async>();
    Node->Var_AccessToken = AccessToken;
    Node->Var_PreviousPassword = PreviousPassword;
    Node->Var_ProposedPassword = ProposedPassword;
    return Node;
}

void UChangePassword_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::ChangePasswordRequest ChangePasswordRequest;
    ChangePasswordRequest.SetAccessToken(TCHAR_TO_UTF8(*Var_AccessToken));
    ChangePasswordRequest.SetPreviousPassword(TCHAR_TO_UTF8(*Var_PreviousPassword));
    ChangePasswordRequest.SetProposedPassword(TCHAR_TO_UTF8(*Var_ProposedPassword));

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ChangePasswordRequest&, const Aws::CognitoIdentityProvider::Model::ChangePasswordOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->ChangePasswordAsync(ChangePasswordRequest, AsyncCallback);
}

void UChangePassword_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
