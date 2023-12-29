
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "ResendConfirmationCode_Async.h"

#include "aws/cognito-idp/model/ResendConfirmationCodeRequest.h"

UResendConfirmationCode_Async* UResendConfirmationCode_Async::ResendConfirmationCode_Async(FResentConfirmationCodeRequest Request)
{
    UResendConfirmationCode_Async* Node = NewObject<UResendConfirmationCode_Async>();
    Node->Var_ResendConfirmationCodeRequest = Request;
    return Node;
}

void UResendConfirmationCode_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::ResendConfirmationCodeRequest ResendConfirmationCodeRequest;
    ResendConfirmationCodeRequest.SetClientId(TCHAR_TO_UTF8(*Var_ResendConfirmationCodeRequest.ClientId));
    ResendConfirmationCodeRequest.SetUsername(TCHAR_TO_UTF8(*Var_ResendConfirmationCodeRequest.Username));
    ResendConfirmationCodeRequest.SetSecretHash(TCHAR_TO_UTF8(*Var_ResendConfirmationCodeRequest.SecretHash));
    ResendConfirmationCodeRequest.SetAnalyticsMetadata(Var_ResendConfirmationCodeRequest.AnalyticsMetadata.ToAnalyticsMetadataType());
    for (auto Elem : Var_ResendConfirmationCodeRequest.ClientMetaData)
    {
        ResendConfirmationCodeRequest.AddClientMetadata(TCHAR_TO_UTF8(*Elem.Key), TCHAR_TO_UTF8(*Elem.Value));
    }
    ResendConfirmationCodeRequest.SetUserContextData(Var_ResendConfirmationCodeRequest.UserContextData.ToUserContextDataType());

    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ResendConfirmationCodeRequest&, const Aws::CognitoIdentityProvider::Model::ResendConfirmationCodeOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->ResendConfirmationCodeAsync(ResendConfirmationCodeRequest, AsyncCallback);
}

void UResendConfirmationCode_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FCodeDeliveryDetailsType(), Error);
}
