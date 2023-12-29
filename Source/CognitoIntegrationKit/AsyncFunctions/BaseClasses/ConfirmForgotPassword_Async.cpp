
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "ConfirmForgotPassword_Async.h"

#include "aws/cognito-idp/model/ConfirmForgotPasswordRequest.h"

UConfirmForgotPassword_Async* UConfirmForgotPassword_Async::ConfirmForgotPassword_Async(FConfirmForgotPasswordReq Request)
{
    UConfirmForgotPassword_Async* Node = NewObject<UConfirmForgotPassword_Async>();
    Node->Var_ConfirmForgotPasswordReq = Request;
    return Node;
}

void UConfirmForgotPassword_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::ConfirmForgotPasswordRequest ConfirmForgotPasswordRequest;
    ConfirmForgotPasswordRequest.SetAnalyticsMetadata(Var_ConfirmForgotPasswordReq.AnalyticsMetadata.ToAnalyticsMetadataType());
    ConfirmForgotPasswordRequest.SetClientId(TCHAR_TO_UTF8(*Var_ConfirmForgotPasswordReq.ClientId));
    ConfirmForgotPasswordRequest.SetConfirmationCode(TCHAR_TO_UTF8(*Var_ConfirmForgotPasswordReq.ConfirmationCode));
    ConfirmForgotPasswordRequest.SetPassword(TCHAR_TO_UTF8(*Var_ConfirmForgotPasswordReq.Password));
    ConfirmForgotPasswordRequest.SetSecretHash(TCHAR_TO_UTF8(*Var_ConfirmForgotPasswordReq.SecretHash));
    ConfirmForgotPasswordRequest.SetUsername(TCHAR_TO_UTF8(*Var_ConfirmForgotPasswordReq.Username));
    for (auto& Elem : Var_ConfirmForgotPasswordReq.ClientMetadata)
    {
        ConfirmForgotPasswordRequest.AddClientMetadata(TCHAR_TO_UTF8(*Elem.Key), TCHAR_TO_UTF8(*Elem.Value));
    }
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ConfirmForgotPasswordRequest&, const Aws::CognitoIdentityProvider::Model::ConfirmForgotPasswordOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->ConfirmForgotPasswordAsync(ConfirmForgotPasswordRequest, AsyncCallback);
}

void UConfirmForgotPassword_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
