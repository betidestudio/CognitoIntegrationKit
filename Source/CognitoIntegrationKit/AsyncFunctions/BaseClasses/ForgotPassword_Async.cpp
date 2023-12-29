
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "ForgotPassword_Async.h"

#include "aws/cognito-idp/model/ForgotPasswordRequest.h"

UForgotPassword_Async* UForgotPassword_Async::ForgotPassword_Async(FForgotPassword_Req Request)
{
    UForgotPassword_Async* Node = NewObject<UForgotPassword_Async>();
    Node->Var_ForgotPassword_Req = Request;
    return Node;
}

void UForgotPassword_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::ForgotPasswordRequest ForgotPasswordRequest;
    ForgotPasswordRequest.SetClientId(TCHAR_TO_UTF8(*Var_ForgotPassword_Req.ClientID));
    ForgotPasswordRequest.SetUsername(TCHAR_TO_UTF8(*Var_ForgotPassword_Req.Username));
    ForgotPasswordRequest.SetSecretHash(TCHAR_TO_UTF8(*Var_ForgotPassword_Req.SecretHash));
    ForgotPasswordRequest.SetAnalyticsMetadata(Var_ForgotPassword_Req.AnalyticsMetadata.ToAnalyticsMetadataType());
    for (auto Elem : Var_ForgotPassword_Req.ClientMetadata)
    {
        ForgotPasswordRequest.AddClientMetadata(TCHAR_TO_UTF8(*Elem.Key), TCHAR_TO_UTF8(*Elem.Value));
    }
    ForgotPasswordRequest.SetUserContextData(Var_ForgotPassword_Req.UserContextData.ToUserContextDataType());

    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ForgotPasswordRequest&, const Aws::CognitoIdentityProvider::Model::ForgotPasswordOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(outcome.GetResult().GetCodeDeliveryDetails(), FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FCodeDeliveryDetailsType(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->ForgotPasswordAsync(ForgotPasswordRequest, AsyncCallback);
}

void UForgotPassword_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FCodeDeliveryDetailsType(), Error);
}
