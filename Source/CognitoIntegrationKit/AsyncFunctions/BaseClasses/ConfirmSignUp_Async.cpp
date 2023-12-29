
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "ConfirmSignUp_Async.h"

#include "aws/cognito-idp/model/ConfirmSignUpRequest.h"

UConfirmSignUp_Async* UConfirmSignUp_Async::ConfirmSignUp_Async(FConfirmSignUpRequest Request)
{
    UConfirmSignUp_Async* Node = NewObject<UConfirmSignUp_Async>();
    Node->Var_Request = Request;
    return Node;
}

void UConfirmSignUp_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::ConfirmSignUpRequest SignUpRequest;
    SignUpRequest.SetClientId(TCHAR_TO_UTF8(*Var_Request.ClientId));
    SignUpRequest.SetConfirmationCode(TCHAR_TO_UTF8(*Var_Request.ConfirmationCode));
    SignUpRequest.SetForceAliasCreation(Var_Request.bForceAliasCreation);
    SignUpRequest.SetSecretHash(TCHAR_TO_UTF8(*Var_Request.SecretHash));
    SignUpRequest.SetUsername(TCHAR_TO_UTF8(*Var_Request.Username));
    for (auto& Elem : Var_Request.ClientMetadata)
    {
        SignUpRequest.AddClientMetadata(TCHAR_TO_UTF8(*Elem.Key), TCHAR_TO_UTF8(*Elem.Value));
    }
    SignUpRequest.SetAnalyticsMetadata(Var_Request.AnalyticsMetadata.ToAnalyticsMetadataType());
    SignUpRequest.SetUserContextData(Var_Request.UserContextData.ToUserContextDataType());
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ConfirmSignUpRequest&, const Aws::CognitoIdentityProvider::Model::ConfirmSignUpOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->ConfirmSignUpAsync(SignUpRequest, AsyncCallback);
}

void UConfirmSignUp_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
