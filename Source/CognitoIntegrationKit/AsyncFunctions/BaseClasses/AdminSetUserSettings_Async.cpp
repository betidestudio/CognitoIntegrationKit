
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AdminSetUserSettings_Async.h"

#include "aws/cognito-idp/model/AdminSetUserSettingsRequest.h"

UAdminSetUserSettings_Async* UAdminSetUserSettings_Async::AdminSetUserSettings_Async(TArray<FMFAOptionType> MFAOptions, FString UserPoolId, FString Username)
{
    UAdminSetUserSettings_Async* Node = NewObject<UAdminSetUserSettings_Async>();
    Node->Var_MFAOptions = MFAOptions;
    Node->Var_UserPoolId = UserPoolId;
    Node->Var_Username = Username;
    return Node;
}

void UAdminSetUserSettings_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AdminSetUserSettingsRequest AdminSetUserSettingsRequest;
    AdminSetUserSettingsRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    AdminSetUserSettingsRequest.SetUsername(TCHAR_TO_UTF8(*Var_Username));
    for (int i = 0; i < Var_MFAOptions.Num(); i++)
    {
        AdminSetUserSettingsRequest.AddMFAOptions(Var_MFAOptions[i].ToMFAOptionType());
    }
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminSetUserSettingsRequest&, const Aws::CognitoIdentityProvider::Model::AdminSetUserSettingsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->AdminSetUserSettingsAsync(AdminSetUserSettingsRequest, AsyncCallback);
}

void UAdminSetUserSettings_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
