
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "SetUserMFAPreference_Async.h"

#include "aws/cognito-idp/model/SetUserMFAPreferenceRequest.h"

USetUserMFAPreference_Async* USetUserMFAPreference_Async::SetUserMFAPreference_Async(FString AccessToken, FSMSMfaSettingsType SMSMfaSettings, FSoftwareTokenMfaSettingsType SoftwareTokenMfaSettings)
{
    USetUserMFAPreference_Async* Node = NewObject<USetUserMFAPreference_Async>();
    Node->Var_AccessToken = AccessToken;
    Node->Var_SMSMfaSettings = SMSMfaSettings;
    Node->Var_SoftwareTokenMfaSettings = SoftwareTokenMfaSettings;
    return Node;
}

void USetUserMFAPreference_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::SetUserMFAPreferenceRequest SetUserMFAPreferenceRequest;
    SetUserMFAPreferenceRequest.SetAccessToken(TCHAR_TO_UTF8(*Var_AccessToken));
    SetUserMFAPreferenceRequest.SetSMSMfaSettings(Var_SMSMfaSettings.ToSMSMfaSettingsType());
    SetUserMFAPreferenceRequest.SetSoftwareTokenMfaSettings(Var_SoftwareTokenMfaSettings.ToSoftwareTokenMfaSettingsType());

    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::SetUserMFAPreferenceRequest&, const Aws::CognitoIdentityProvider::Model::SetUserMFAPreferenceOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->SetUserMFAPreferenceAsync(SetUserMFAPreferenceRequest, AsyncCallback);
}

void USetUserMFAPreference_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
