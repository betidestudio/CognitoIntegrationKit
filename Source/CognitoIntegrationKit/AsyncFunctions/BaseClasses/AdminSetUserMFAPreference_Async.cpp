
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AdminSetUserMFAPreference_Async.h"

#include "aws/cognito-idp/model/AdminSetUserMFAPreferenceRequest.h"

UAdminSetUserMFAPreference_Async* UAdminSetUserMFAPreference_Async::AdminSetUserMFAPreference_Async(FSMSMfaSettingsType MfaSettings, FSoftwareTokenMfaSettingsType SoftwareTokenMfaSettings, FString Username, FString UserPoolId)
{
    UAdminSetUserMFAPreference_Async* Node = NewObject<UAdminSetUserMFAPreference_Async>();
    Node->Var_MfaSettings = MfaSettings;
    Node->Var_SoftwareTokenMfaSettings = SoftwareTokenMfaSettings;
    Node->Var_Username = Username;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UAdminSetUserMFAPreference_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AdminSetUserMFAPreferenceRequest AdminSetUserMFAPreferenceRequest;
    AdminSetUserMFAPreferenceRequest.SetUsername(TCHAR_TO_UTF8(*Var_Username));
    AdminSetUserMFAPreferenceRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    AdminSetUserMFAPreferenceRequest.SetSMSMfaSettings(Var_MfaSettings.ToSMSMfaSettingsType());
    AdminSetUserMFAPreferenceRequest.SetSoftwareTokenMfaSettings(Var_SoftwareTokenMfaSettings.ToSoftwareTokenMfaSettingsType());

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminSetUserMFAPreferenceRequest&, const Aws::CognitoIdentityProvider::Model::AdminSetUserMFAPreferenceOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->AdminSetUserMFAPreferenceAsync(AdminSetUserMFAPreferenceRequest, AsyncCallback);
}

void UAdminSetUserMFAPreference_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
