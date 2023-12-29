
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "SignUp_Async.h"

#include "aws/cognito-idp/model/SignUpRequest.h"

USignUp_Async* USignUp_Async::SignUp_Async(FSignUpRequest SignUpRequest)
{
    USignUp_Async* Node = NewObject<USignUp_Async>();
    Node->Var_SignUpRequest = SignUpRequest;
    return Node;
}

void USignUp_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::SignUpRequest SignUpRequest;
    SignUpRequest.SetAnalyticsMetadata(Var_SignUpRequest.AnalyticsMetadata.ToAnalyticsMetadataType());
    SignUpRequest.SetClientId(TCHAR_TO_UTF8(*Var_SignUpRequest.ClientId));
    for (auto Elem : Var_SignUpRequest.ClientMetadata)
    {
        SignUpRequest.AddClientMetadata(TCHAR_TO_UTF8(*Elem.Key), TCHAR_TO_UTF8(*Elem.Value));
    }
    SignUpRequest.SetPassword(TCHAR_TO_UTF8(*Var_SignUpRequest.Password));
    SignUpRequest.SetSecretHash(TCHAR_TO_UTF8(*Var_SignUpRequest.SecretHash));
    SignUpRequest.SetUserContextData(Var_SignUpRequest.UserContextData.ToUserContextDataType());
    SignUpRequest.SetUsername(TCHAR_TO_UTF8(*Var_SignUpRequest.Username));
    for (auto Elem : Var_SignUpRequest.UserAttributes)
    {
        SignUpRequest.AddUserAttributes(Elem.ToAttributeType());
    }
    for (auto Elem : Var_SignUpRequest.ValidationData)
    {
        SignUpRequest.AddValidationData(Elem.ToAttributeType());
    }
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::SignUpRequest&, const Aws::CognitoIdentityProvider::Model::SignUpOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(outcome.GetResult().GetCodeDeliveryDetails(), outcome.GetResult().GetUserConfirmed(), outcome.GetResult().GetUserSub().c_str(), FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FCodeDeliveryDetailsType(), false, FString(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->SignUpAsync(SignUpRequest, AsyncCallback);
}

void USignUp_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FCodeDeliveryDetailsType(), false, FString(), Error);
}
